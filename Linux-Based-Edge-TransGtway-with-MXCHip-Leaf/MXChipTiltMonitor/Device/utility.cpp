#include "Arduino.h"
#include "AzureIotHub.h"

#include "LSM6DSLSensor.h"
#include "RGB_LED.h"

#include "parson.h"
#include "myconfig.h"

#define RGB_LED_BRIGHTNESS 32

DevI2C *i2c;
LSM6DSLSensor *acc_gyro;

static RGB_LED rgbLed;
const float alpha = 0.5;
static int delayTime = 100;

void blinkLED()
{
    rgbLed.turnOff();
    rgbLed.setColor(RGB_LED_BRIGHTNESS, 0, 0);
    delay(500);
    rgbLed.turnOff();
}

void blinkSendConfirmation()
{
    rgbLed.turnOff();
    rgbLed.setColor(0, 0, RGB_LED_BRIGHTNESS);
    delay(500);
    rgbLed.turnOff();
}

void parseDelayCommandPayload(const char *message)
{
    JSON_Value *root_value;
    root_value = json_parse_string(message);
    if (json_value_get_type(root_value) != JSONObject)
    {
        if (root_value != NULL)
        {
            json_value_free(root_value);
        }
        LogError("parse %s failed", message);
        return;
    }
    JSON_Object *root_object = json_value_get_object(root_value);

    delayTime = json_object_get_number(root_object, "delay");
    json_value_free(root_value);
}

void SensorInit()
{
    i2c = new DevI2C(D14, D15);

    acc_gyro = new LSM6DSLSensor(*i2c, D4, D5);
    acc_gyro->init(NULL);
    acc_gyro->enableAccelerator();
    acc_gyro->enableGyroscope();
}

bool readMessage(char *payLoadBuffer)
{
    uint64_t measure_time_ms;

    int axes[3];
    float pitch, roll;
    float xReading, yReading, zReading;
    float fXg, fYg, fZg = 0;

    bool success;
    bool bufferFull = false;
    char *serialized_string = NULL;
    int nrReadings = 0;
    int msec = 0;

    sprintf(payLoadBuffer, "[");

    time_t rawtime;
    struct tm * timeinfo;
    char readingBuffer[80];
    time (&rawtime);
    timeinfo = gmtime (&rawtime);

    measure_time_ms = SystemTickCounterRead() + 1000;

    while (SystemTickCounterRead() < measure_time_ms && ! bufferFull) {
        success = (acc_gyro->getXAxes(axes) == 0);

        if (success) {
            xReading = (float)axes[0];
            yReading = (float)axes[1];
            zReading = (float)axes[2];

            fXg = xReading * alpha + (fXg * (1.0 - alpha));
            fYg = yReading * alpha + (fYg * (1.0 - alpha));
            fZg = zReading * alpha + (fZg * (1.0 - alpha));

            roll  = (atan2(-fYg, fZg) * 180.0) / M_PI;
            pitch = (atan2(fXg, sqrt(fYg * fYg + fZg * fZg)) * 180.0) / M_PI;

            // roll  = (atan2(-yReading, zReading) * 180.0) / M_PI;
            // pitch = (atan2(xReading, sqrt(yReading * yReading + zReading * zReading)) * 180.0) / M_PI;

            sprintf(readingBuffer, "{\"time\": \"%04d-%02d-%02dT%02d:%02d:%02d.%03dZ\", \"roll\": %f, \"pitch\": %f}, ", timeinfo->tm_year + 1900, 
                timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, msec, roll, pitch);  

            if (strlen(payLoadBuffer) + strlen(readingBuffer) < MESSAGE_MAX_LEN) {
                strcat(payLoadBuffer, readingBuffer);
                nrReadings += 1;
            } else {
                bufferFull = true;
            }
        }
        delay(delayTime);
        msec += delayTime;
    }
    int bufferLen = strlen(payLoadBuffer);
    payLoadBuffer[bufferLen - 2] = ']';
    payLoadBuffer[bufferLen - 1] = '\0';

    LogInfo("Measurements done - nrReadings = %d, bufferLen = %d", nrReadings, bufferLen);

    return success;
}

#if (DEVKIT_SDK_VERSION >= 10602)
void __sys_setup(void)
{
    // Enable Web Server for system configuration when system enter AP mode
    EnableSystemWeb(WEB_SETTING_IOT_DEVICE_CONN_STRING);
}
#endif