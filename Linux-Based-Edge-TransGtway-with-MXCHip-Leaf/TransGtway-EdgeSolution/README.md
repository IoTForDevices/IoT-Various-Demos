# Transparent Gateway Edge Solution Explained

It is relatively easy to implement a Transparent Gateway. More backgound information on using an Azure IoT Edge as a Gateway (transparent, protocol translation, identity translation) can be found here.

 The most important steps to connect a leaf device are described in the [parent README.md](../README.md) file of this Demo. The most critical things are the correct installation of a certificate and solving DNS issues / using the right IP address.

There is some additional functionality that has to be provided. The most important is a deployment manifest containing routing information to at least pass all telemetry from the leaf device to the IoT Hub.

If additional data transformation is needed on the Edge, additional routing information is most likely needed. This part of the demo show the deployment manifest to connect an MXChip, to send all telemetry data from the leaf device to a local Azure Stream Analytics Job and onwards from the ASA Job to the IoT Hub.