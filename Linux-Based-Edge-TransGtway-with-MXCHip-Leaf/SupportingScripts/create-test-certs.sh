#!/bin/bash
# This script can be used to create new test certificates to deploy to an Azure IoT Edge device
# The script is expected to be run on WSL with a cloned iotedge git repo

# Set Environment Variables (default names for CA_CERTIFICATION_NAME and EDGE_DEVICE)
IOTEDGE_REPO_DIR=~/Source/Repo/iotedge/tools/CACertificates/
WRKDIR=~/IoTEdgeCerts/
CERT_DIR=~/IoTEdgeCerts
CA_CERTIFICATE_NAME="MyEdgeDeviceCA"
EDGE_DEVICE=maarten@maarten-up-apl01

#Check if the user wants to override one or more of the default values
OPTS=`getopt -n 'parse-options' -o c:r: --long certificate-name:,remote-device: -- "$@"`
eval set -- "$OPTS"

#extract options and their arguments into variables
while true ; do
    case "$1" in
        -c | --certificate-name ) CA_CERTIFICATE_NAME="$2"; shift 2 ;;
        -r | --remote-device    ) EDGE_DEVICE="$2"; shift 2 ;;
        --) shift; break ;;
        *) break;;
    esac
done

# Check if a working folder to store certificates already exists. If so, remove it and create a new one.
if [ -d $WRKDIR ]
    then
        rm -r -f $WRKDIR
fi

mkdir $WRKDIR

cd $WRKDIR

# Copy the test certificate generation tools to the work folder
cp $IOTEDGE_REPO_DIR/*.cnf .
cp $IOTEDGE_REPO_DIR/certGen.sh .

# Generate the test certificates
./certGen.sh create_root_and_intermediate
./certGen.sh create_edge_device_ca_certificate $CA_CERTIFICATE_NAME

# Check on the edge device if a destination directory already exists. If so, remove it
if ssh $EDGE_DEVICE '[ -d $CERT_DIR ]'
    then
        ssh $EDGE_DEVICE rm -r -f $CERT_DIR
fi

ssh $EDGE_DEVICE mkdir $CERT_DIR
ssh $EDGE_DEVICE mkdir $CERT_DIR/certs
ssh $EDGE_DEVICE mkdir $CERT_DIR/private

# Copy the test certificates to the edge device
scp certs/iot-edge-device-ca-MyEdgeDeviceCA-full-chain.cert.pem $EDGE_DEVICE:$CERT_DIR/certs/
scp private/iot-edge-device-ca-MyEdgeDeviceCA.key.pem $EDGE_DEVICE:$CERT_DIR/private/
scp certs/azure-iot-test-only.root.ca.cert.pem $EDGE_DEVICE:$CERT_DIR/certs/

echo "Make sure to add the $WRKDIR/certs/azure-iot-test-only.root.ca.cert.pem into the MXChip firmware."

