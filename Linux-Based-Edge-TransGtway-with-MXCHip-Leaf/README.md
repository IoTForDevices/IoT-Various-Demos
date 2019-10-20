# Azure IoT Edge Device (RPi) as Transparent Gateway with connected MXChip IoT DevKit Leaf Device
This demo allows you to show how to connect leaf devices to a transparent gateway device using Azure IoT Edge. You can use a Rasberry Pi 3B+ as gateway, but this has also been tested with an Azure IoT Edge device running Ubuntu 18.04 LTS. More backgound information on using an Azure IoT Edge as a Gateway (transparent, protocol translation, identity translation) can be [found here](https://docs.microsoft.com/en-us/azure/iot-edge/iot-edge-as-gateway).

## Pre-requisites
Here you will find detailed instruction to install [Azure IoT Edge on a RP3 running Raspbian Buster](../Generic-prerequisites/Raspbian-Buster-IoTEdge-RP3/README.md).
Generic instructions for running this on [Linux (or even a Linux VM) can be found here](https://docs.microsoft.com/en-us/azure/iot-edge/quickstart-linux).

**NOTE:** Setting up the demo environment will take time, especially if you have to install an OS on your Edge device as well. You probably need at least two hours to properly setup this demo, prior to delivery during showtime.

## Overview of modules in this demo
The complete demo consists of this description and a number of software modules that are needed to build the complete demo. Most of the software modules only have to be build once. The are separately described (just click the links for detailed descriptions).
- [ASAEdgeTiltJob](./ASAEdgeTiltJob/README.md): This is a Visual Studio 2019 solution that will create a C# UDF for an Azure Stream Analytics Edge job
- [MXChipTiltMonitor](./MXChipTiltMonitor/README.md): This is the firmware for an [MXChip IoT DevKit](https://www.seeedstudio.com/AZ3166-IOT-Developer-Kit.html) that is responsible for generating accelerometer data.
- [TransGtway-EdgeSolution](./TransGtway-EdgeSolution/README.md): This is the deployment template to deploy the ASAEdgeTiltJob to an Edge device, configured as transparent gateway. It also contains route information to route telemetry data from a leaf device into the ASAEdgeTiltJob.

## Generate certificates with Linux
A good description on doing this can be found in [this document](https://docs.microsoft.com/en-us/azure/iot-edge/how-to-create-transparent-gateway#generate-certificates-with-linux) (for my personal use: WSL on work laptop has generated keys in the ~/IoTEdgeCerts folder).

To copy the generated certificates from a development machine to the target device, you can use the following commands from a WSL shell:
```Bash
    scp <root-folder-for-cert-creation>/certs/iot-edge-device-ca-MyEdgeDeviceCA-full-chain.cert.pem pi@<remote-host>:<CERTDIR>/certs/
    scp <root-folder-for-cert-creation>/private/iot-edge-device-ca-MyEdgeDeviceCA.key.pem pi@<remote-host>:<CERTDIR>/private/
    scp <root-folder-for-cert-creation>/certs/azure-iot-test-only.root.ca.cert.pem pi@<remote-host>:<CERTDIR>/certs
```

To avoid having to deal with DNS issues, it might make sense to use the IP address of the Edge Device for connection of leaf devices instead of its host name. In that case, you must also make sure to use the IP address as name for **MyEdgeDeviceCA** and modify the hostname entry in /etc/iotedge/config.yaml as well to have the IP number as hostname. This will generate an error when you execute **sudo iotedge check** but that error can be ignored.

On the Edge device you now must add the certificates to the certificate section of the IoT Edge security daemon file that can be found here: ```/etc/iotedge/config.yaml```

Sample hostname contents of the IoT Edge security daemon file:

```YAML
# Edge device hostname
###############################################################################                                         #
# Configures the environment variable 'IOTEDGE_GATEWAYHOSTNAME' injected into                                           # modules. Regardless of case the hostname is specified below, a lower case
# value is used to configure the Edge Hub server hostname as well as the                                                # environment variable specified above.                                                                                 #                                                                                                                       # It is important to note that when connecting downstream devices to the                                                # Edge Hub that the lower case value of this hostname be used in the
# 'GatewayHostName' field of the device's connection string URI.                                                        ###############################################################################
                                                                                                                        #hostname: "pi3-iotedge-gtway"
hostname: "192.168.2.29"
```

Inside the same IoT Edge security deamon file you need to add the genererated certificates (in the sample I am using the same IP address, reflected by the certificate name).

```YAML
# Certificate settings
###############################################################################
#
# Configures the certificates required to operate the IoT Edge
# runtime as a gateway which enables external leaf devices to securely
# communicate with the Edge Hub. If not specified, the required certificates
# are auto generated for quick start scenarios which are not intended for
# production environments.
#
# Settings:
#     device_ca_cert   - path to the device ca certificate and its chain
#     device_ca_pk     - path to the device ca private key file
#     trusted_ca_certs 
#                        certificates required for Edge module communication
#
###############################################################################

certificates:
  device_ca_cert: "<CERTDIR>/certs/iot-edge-device-ca-192.168.2.29-full-chain.cert.pem"
  device_ca_pk: "<CERTDIR>/private/iot-edge-device-ca-192.168.2.29.key.pem"
  trusted_ca_certs: "<CERTDIR>/certs/azure-iot-test-only.root.ca.cert.pem"
```

To be able to use the Azure IoT Edge runtime for transparent gateway use, no additional modules are necessary, but both the edgeAgent and the edgeHub must be running. Initially, only the edgeAgent will be running. You can use the Azure Portal to force the edgeHub to start running as well by simply defining a route to send all received input immediately, without transformation, to the IoT Hub as follows:

1) In the Azure portal, navigate to your IoT hub.
1) Go to **IoT Edge** and select your IoT Edge device that you want to use as a gateway.
1) Select **Set Modules**.
1) Select **Next**.
1) In the **Specify routes** page, you should have a default route that sends all messages from all modules to IoT Hub. If not, add the following code then select **Next**.
```JSON
{
    "routes": {
        "route": "FROM /* INTO $upstream"
    }
}
```
6) In the Review template page, select **Submit**.

Now you can verify if both the edgeAgent and the edgeHub are running on your Iot Edge device by using the following command: ```sudo iotedge list```. If you still only see the edgeAgent, restart the IoT Edge runtime by: ```sudo iotedge restart```.

## Using the MXChip IoT DevKit as leaf device
The easiest way to set this up is by using the **Get Started** sample that is part of the **IoT Device Workbench Examples**.

1) Select an existing IoT Hub and create a new device, for instance by typing **Azure IoT Hub: Create Device** in Visual Studio Code's command palette.
1) Give the device an appropriate name
1) Right click on the just created device and select **Copy Device Connection String** to copy the connection string to the clipboard.
1) Put the MXChip IoT DevKit into **Configuration Mode** by holding button **A** while pushing and releasing the **Reset** button.
1) Open the command palette and select **Azure IoT Device Workbench: Configure Device Settings**
1) Select to an **Input IoT Hub Device Connection String** and paste the contents of the clipboard.
1) Append the GatewayHostName property with the hostname or IP address of the gateway device to the end of the connection string. The final string should look like this (taking the same IP address as earlier in this document):

 ```Hostname=yourIoTHub.azure-devices.net;DeviceId=yourDevice;SharedAccessKey=XXXYYYZZZ=;GatewayHostName=192.168.2.29```

1) Press enter to set this into the MXChip IoT DevKit
1) Add a new **edgeCert** variable at the beginning of the GetStarted.ino file, and copy the content of the **"<CERTDIR>/certs/azure-iot-test-only.root.ca.cert.pem"** in it. Make sure to remove all newlines from the copied certificate.
```C
static const  char edgeCert [] =
"-----BEGIN CERTIFICATE-----\r\n"
"Your CA string"            // No newlines in this, just one long string
"-----END CERTIFICATE-----\r\n";
```
10) Register the CA certificate when setting up the client by adding:
```C
DevKitMQTTClient_SetOption("TrustedCerts", edgeCert);
```

right after this statement that is already part of the sample code:

```C
DevKitMQTTClient_SetOption(OPTION_MINI_SOLUTION_NAME, "DevKit-GetStarted");
```

Now you should be good to go. Just boot the MXChip IoT DevKit and make sure that the Edge Device is running as well. You will see messages arriving at the IoT Hub.
![ScreenShot](Images/LeafDeviceSendingMsgsThroughEdgeToIoTHub.png)
At the same time you will see in the IoT Edge logfiles that it passes those messages through.
![ScreenShot](Images/MessagePassingThroughEdgeGatway.png)

**Possible Issues:** This should all work smoothly (even with an Edge Device and the leaf device both connected only via WiFi. although of course with some latency). The only critical things are to make sure that both edgeAgent and edgeHub modules are running on the Edge Device and that the GatewayHostName is consistent (easiest to use IP addresses to stay away from potential DNS challenges and make sure to have all on the same subnet)

## Anomaly detection with MXChip DevKit as leaf device and local ASA on transparent Azure IoT Edge Gateway
This is basically the same demo as the [Tilt Monitor using Raspberry Pi with SenseHat](../Tilt-Monitor-RPi-based/README.md). This time accelerometer data is provided by the MXChip DevKit. Here are the step-by-step instructions.

### Prepare the Leaf Device
1) Select an existing IoT Hub and create a new device, for instance by typing **Azure IoT Hub: Create Device** in Visual Studio Code's command palette.
1) Give the device an appropriate name
1) Right click on the just created device and select **Copy Device Connection String** to copy the connection string to the clipboard.
1) Put the MXChip IoT DevKit into **Configuration Mode** by holding button **A** while pushing and releasing the **Reset** button.
1) Open the command palette and select **Azure IoT Device Workbench: Configure Device Settings**
1) Select to an **Input IoT Hub Device Connection String** and paste the contents of the clipboard.
1) Append the GatewayHostName property with the hostname or IP address of the gateway device to the end of the connection string. The final string should look like this (taking the same IP address as earlier in this document):

 ```Hostname=yourIoTHub.azure-devices.net;DeviceId=yourDevice;SharedAccessKey=XXXYYYZZZ=;GatewayHostName=192.168.2.29```

### Install ASA Module on Azure IoT Edge Device
Here, we assume that you have a Linux based device available, running Ubuntu 18.04 LTS. The Edge Device should already be connected to an IoT Hub.
1. Open the TransGtway-EdgeSolution (that is available in a subfolder of this document) in Visual Studio Code.
1. Inside Visual Studio Code, find your Edge Device in the AZURE IOT HUB explorer and right-click it.
1. In the popup menu, select **Create Deployment for Single Device** and select the **deployment.amd64.json** template that can be found in the **config** folder. This will deploy the ASA Edge Tilt Job to the Edge Device. Verify that the module is deployed to the Edge Device.

### Install Firmware and start MXChip IoT DevKit
1) Install the MXChipTiltMonitor firmware on the MXChip DevKit. The firmware can be found in the Repo.

The MXChip DevKit IoT should now connect to the specified IoT Hub through your transparent gateway. Since you want to run anomaly detection locally on the gateway, you need to make sure to provide routing information to send telemetry data to the ASA job that will be running on your gateway device.

### Start the ASA Job to send anomaly data to PowerBI
For now, just take the pre-defined TiltDemoPowerBI-ASA job in the Arrow-AI-Roadshow-RG. At a later moment, we will add a way to create the job from within Visual Studio Code (currently the ASA plugin doesn't support PowerBI as output).



>To experiment further with this to increase accuracy, use the following:

>Take [this link to try this](https://docs.microsoft.com/en-us/azure/iot-edge/how-to-create-transparent-gateway#route-messages-from-downstream-devices). Should be possible to use exactly this routing info and feed that to ASA from MXChip if we get similar telemetry readings.

>- Take the Raspberry Pi first as a leaf device
>- Next step take MXChip

>>>>>>> TransGtway-Descr
