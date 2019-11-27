#!/bin/bash
# This script can be used to create new test certificates to deploy to an Azure IoT Edge device
# The script is expected to be run on WSL with a cloned iotedge git repo

IOTEDGE_REPO_DIR=~/Source/Repo/iotedge/tools/CACertificates/
WRKDIR=~/IoTEdgeCerts/
CA_CERTIFICATE_NAME="MyEdgeDeviceCA"
EDGE_DEVICE=maarten@192.168.2.19
CERT_DIR=~/IoTEdgeCerts

if [ -d $WRKDIR ]
    then
        rm -r -f $WRKDIR
        mkdir $WRKDIR
fi

cd $WRKDIR

# Copy the test certificate generation tools to the work folder
cp $IOTEDGE_REPO_DIR/*.cnf .
cp $IOTEDGE_REPO_DIR/certGen.sh .

# Generate the test certificates
./certGen.sh create_root_and_intermediate
./certGen.sh create_edge_device_ca_certificate $CA_CERTIFICATE_NAME

# Copy the test certificates to the edge device
scp certs/iot-edge-device-ca-MyEdgeDeviceCA-full-chain.cert.pem $EDGE_DEVICE:CERT_DIR/certs/
scp private/iot-edge-device-ca-MyEdgeDeviceCA.key.pem $EDGE_DEVICE:CERT_DIR/private/
scp certs/azure-iot-test-only.root.ca.cert.pem $EDGE_DEVICE:CERT_DIR/certs

echo "Make sure to add the $WRKDIR/certs/azure-iot-test-only.root.ca.cert.pem into the MXChip firmware."

