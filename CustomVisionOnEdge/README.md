# Custom Vision on Azure IoT Edge

This demo can be executed on a physical device (as small as a Raspberry Pi) or on a virtual device, for instance an Ubuntu IoT Edge Azure VM.

The demo literally follows the [following sample](https://azure.microsoft.com/en-us/resources/samples/custom-vision-service-iot-edge-raspberry-pi/). Just build for the right environment and you should be good to go.

If you are running the demo on a virtual device, it makes sense to show the video stream that we are using to recognize apples and banana's. Also, the interesting messages are when banana's are tilted out for apples. At that moment you will see some uncertainty in the model.

## Showing the video stream from the container
- In an Azure VM, you have to open inbound port 5012
- Browse to the "URI of the Edge device":5012 to see the video stream

**TODO:** Need better sample video + trained model to make an impression.