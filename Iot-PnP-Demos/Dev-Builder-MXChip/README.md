# Building an IoT Plug and Play enabled MXChip device
This demo is useful for device builders that want to support IoT Plug and Play to extend their potential customer base and to allow IoT Solution developers to concentrate on building a solution rather then connecting individual devices to an IoT Hub / IoT Central application.
## Prerequisites
In this demo we focus on developing on a laptop that runs Windows 10, version 1909 or later. In order to develop for MXChip devices, you must have the following tools installed:
- Follow [these steps](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-arduino-iot-devkit-az3166-get-started#prepare-the-development-environment) to setup the Arduino Development Environment and Visual Studio Code. We will develop using Visual Studio Code, but the Arduino IDE is needed to provides the necessary toolchain for compiling and uploading Arduino code. It is important to install the Arduino IDE with the **Windows Installer**. Do not install the IDE from the App Store, because that version cannot integrate with Visual Studio Code. Setting up the development environment will take approximately 30 minutes (depending on the hardware and network connection of your development machine).
- Install the **Azure IoT Tools** extension inside Visual Studio Code. After installing this extension, you will get warnings that Docker cannot be found. Even though you can omit these warnings (since we are not building containerized workloads in this lab), you can also install Docker to suppress these errors. If you decide to install Docker, you also need to enable Hyper-V (the Docker installer will prompt you for that).
- To verify that the development tools are installed correctly, you can take the [following steps](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-arduino-iot-devkit-az3166-get-started#build-your-first-project). If you are able to download and execute the code on a MXChip DevKit, you have successfully installed the development tools.
- To get a feeling for IoT Plug and Play, you should clone the [MXChip Plug and Play sample](https://github.com/Azure-Samples/mxchip-iot-devkit-pnp) and build + deploy the sample code that is available in the **Devices** folder of the repository.
## To build your own IoT Plug and Play enabled device
You now have installed all development tools to create applications that can run on MXChip devices. In the next steps you are going to develop an IoT hardware product (using the MXChip device) that supports [IoT Plug and Play](https://docs.microsoft.com/en-us/azure/iot-pnp/overview-iot-plug-and-play#develop-an-iot-device-application). In order to build an IoT Plug and Play supported device, you need to install some additional tools:
- Download and install the latest release of [Azure IoT explorer](https://github.com/Azure/azure-iot-explorer/releases) from the tool's repository page, by selecting the **.msi file** under **Assets** for the most recent update.

**NOTE:** If you get a lot of debug messages in VSCode's output Window, you probably have installed the Arduino IDE version 1.8.10. You can disable these messages by adding `-DDEBUG=false` to the `C:\Program Files (x86)\Arduino\arduino_debug.l4j.ini` file.

**Additional NOTE:** If you are running into issues when refreshing Arduino Board Manager Packages, try to install a newer version of the Arduino IDE. This is seemingly caused by some old certificates for Java Libraries that are considered insecure, resulting in the Java Libraries not loading.

To build an IoT Plug and Play version of AZ3166 firmware, make sure to select the **MXChip - Microsoft Azure IoT Developer Kit** by Microsoft Developer Version **1.9.11-preview** through the Arduino Board Manager.

# Possible Steps for IoT Plug and Play Workshop for Device Builders (Connect to IoTHub)
1) Create Interfaces and a Device Capability Model for your device ([Guidance](https://docs.microsoft.com/en-us/azure/iot-pnp/tutorial-pnp-visual-studio-code#model-your-device))
   - Create an interface for some Telemetry Data (e.g. Temperature and Humidity)
   - Create an interface to define a Property (e.g. Measurement Interval)
   - Create an interface to define a Command (.e.g. Toggle LED)
1) Publish your model ([Guidance](https://docs.microsoft.com/en-us/azure/iot-pnp/tutorial-pnp-visual-studio-code#publish-the-model)). This step is important if you want to make use of the Azure IoT Explorer to verify behavior of your device. 
1) Generate code for the Capability Model you just created ([Guidance](https://docs.microsoft.com/en-us/azure/iot-pnp/tutorial-pnp-visual-studio-code#generate-code)). Don't forget to update the generate code to do something meaningful with the device. You don't have to provide low level MXChip code, but you can call functions that are defined in header file **IoT_DevKit_HW.h**. 
1) Test if you can connect your device to an IoT Hub. For this exercise it is OK to hard code the device connection string. However, a better solution is to use the IoT Workbench to set the connection string in the HSM of the MXChip device.

**About Connection Strings:** In a real solution, the connection string should be provisioned to the device, preferably in an automated way.

To verify the behavior of your device, you can for instance use [Device Explorer](https://github.com/Azure/azure-iot-sdk-csharp/tree/master/tools/DeviceExplorer) to verify that telemetry data is send to the device, to see the Device Twin with the property you defined and you can execute the command you defined from inside Device Explorer as well. If you have published your Device Capability Model earlier, it is easier to make use of the Azure IoT Explorer to verify the behavior of your device.

Because we are making use of generated device code, be careful to modify it, because each time you generate the device code, your modifications will be lost. Therefor it is important to think good about the interfaces you expose for your device. Typically, you don't have to regenerate device code when you don't modify your interfaces. When you modify device code, try to do so in well defined locations in the generated source files and always keep store a backup of your modified code.

One meaningfull modification might be to change the telemetry measurement interval. Currently this is a hard coded value, as you can see in the following code snippet, copied from the file **pnp_device.c**.

``` C
void pnp_device_run()
{
    tickcounter_ms_t nowTick;
    tickcounter_get_current_ms(tickcounter, &nowTick);

    if (nowTick - lastTickSend >= DEFAULT_SEND_TELEMETRY_INTERVAL_MS)
    {
        LogInfo("Send telemetry data to IoT Hub");

        EnvironmentalSensorInterface_Telemetry_SendAll();

        tickcounter_get_current_ms(tickcounter, &lastTickSend);
    }
    else
    {
        // Just check data from IoT Hub
        DigitalTwinClientHelper_Check();
    }
}
```

Since we defined a writeable property interval, you now can modify this generated source code and make use of the defined propety to be able to change the interval between two telemetry readings. You can change the property from inside the [Azure IoT Explorer](https://github.com/Azure/azure-iot-explorer/releases).