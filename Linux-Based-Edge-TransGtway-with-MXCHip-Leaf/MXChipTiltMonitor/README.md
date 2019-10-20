# MXChipTiltMonitor Explained

The MXChip firmware is self explainatory. We take readings from the accelerometer and send them in burst measurements of 1 second to the connected gateway. The firmware supports the following commands (since we are connected through a transparent gateway, they can be send directly from the IoT Hub), in future also from an IoT Central application.
## Supported Commands:
- **start** - Start sending telemetry data
- **stop** - Stop sending telemetry data
- **delay** - Sets a delay (in msec) between different accelerometer readings

## To be implemented in future versions
- Sending raw accelerometer data without calculating pitch and roll (can increase throughput) with a module on the Edge device doing pitch and roll calculation.

More information about calculating pitch and roll on Arduino compatible devices can be [found here](https://theccontinuum.com/2012/09/24/arduino-imu-pitch-roll-from-accelerometer/).