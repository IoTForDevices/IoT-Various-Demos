# Building an IoT Plug and Play enabled MXChip device
This demo is useful for device builders that want to support IoT Plug and Play to extend their potential customer base and to allow IoT Solution developers to concentrate on building a solution rather then connecting individual devices to an IoT Hub / IoT Central application.
## Prerequisites
In this demo we focus on developing on a laptop that runs Windows 10, version 1909 or later. In order to develop for MXChip devices, you must have the following tools installed:
- Follow [these steps](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-arduino-iot-devkit-az3166-get-started#prepare-the-development-environment) to setup the Arduino Development Environment and Visual Studio Code. We will develop using Visual Studio Code, but the Arduino IDE is needed to provides the necessary toolchain for compiling and uploading Arduino code. It is important to install the Arduino IDE with the **Windows Installer**. Do not install the IDE from the App Store, because that version cannot integrate with Visual Studio Code.

# Possible Steps for IoT Plug and Play Workshop for Device Builders
1) Create Interfaces and a Device Capability Model for your device ([Guidance](https://docs.microsoft.com/en-us/azure/iot-pnp/tutorial-pnp-visual-studio-code#model-your-device))
   - Create an interface for some Telemetry Data (e.g. Temperature and Humidity)
   - Create an interface to define a Property (e.g. Measurement Interval)
   - Create an interface to define a Command (.e.g. Toggle LED)
1) Publish your model ([Guidance](https://docs.microsoft.com/en-us/azure/iot-pnp/tutorial-pnp-visual-studio-code#publish-the-model)) 
1) Generate code for the Capability Model you just created ([Guidance](https://docs.microsoft.com/en-us/azure/iot-pnp/tutorial-pnp-visual-studio-code#generate-code))
1) Test if you can connect your device to an IoT Hub.

**NOTE:** In a real solution, the connection string should be provisioned to the device, preferably in an automated way. For this workshop, you can hard-code the connection string in the source code (name of the .ino file). 

To verify the behavior of your device, you can for instance use [Device Explorer](https://github.com/Azure/azure-iot-sdk-csharp/tree/master/tools/DeviceExplorer) to verify that telemetry data is send to the device, to see the Device Twin with the property you defined and you can execute the command you defined from inside Device Explorer as well.