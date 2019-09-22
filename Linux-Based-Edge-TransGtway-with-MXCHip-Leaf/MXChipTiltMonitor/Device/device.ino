#include "AZ3166WiFi.h"
#include "AzureIotHub.h"
#include "DevKitMQTTClient.h"

#include "myconfig.h"
#include "utility.h"
#include "SystemTickCounter.h"

static const char edgeCert [] =
"-----BEGIN CERTIFICATE-----\r\n"
"MIIFjTCCA3WgAwIBAgIUHYHcb3mi+sT1ACwjjNjePZwfo7swDQYJKoZIhvcNAQELBQAwKjEoMCYGA1UEAwwfQXp1cmVfSW9UX0h1Yl9DQV9DZXJ0X1Rlc3RfT25seTAeFw0xOTA5MjAxMzEzNDFaFw0xOTEwMjAxMzEzNDFaMCoxKDAmBgNVBAMMH0F6dXJlX0lvVF9IdWJfQ0FfQ2VydF9UZXN0X09ubHkwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQDfGfpqx29uDhJmlwXyQQGEUTy4Am87jpwBZV/mIJ5biiyx+7vtHhEnImhqddMOtcXqciklSLesbmhTd0IQJPWiJfPkDuSX6/8osWgWU5Esr4Yr6W7UT6R7CXpCDUVPnNaODsAVxhxoL4bgudxDwwNrw3MnPPTx7SAa07NG68oM8yV3YdwmcC2b9N1qD+1g+iTf38Abg7rxV4g6qLsmQoLsTes4Vz757P+obhfaU97ASMsrbO6QAejkN1h7y8VUZm6akAaxDo96C5MGyGwzRBoeYorF8+KtoB4kImFHI0QnkYyORkYYuuqpzdQx/9BAD7Bd/dr1X0ND7DHGrPgDa9rVXplweXq6Hn0LWejJCNxt7/L38tDvv+X8spUdQWmqhmutCZuKNqikSCtwf9RM5REWAjCehDKOA7iwneatt9T1GK68LKvsF+z0vr3HGAp/1GlkSn91FMxJ7AZpIALo7g59TLScjLI19fpXnjeOQbZ9eE4nx2cDxdEssQz+HpApPFtbx4Lxp6SCt17/Ns1oRy87QeZd/DXquBPO0J3gVdakPF+kCe3WbBrIopOzzSpCOnvxPknVZitwNddMvhMlc3P+gAKn6Yszo5WYOALYuxRubfzLEzGSNfVLExd/ONEfaHMt5tPZ5YQhske/S85h7EFAJB/66hDrQjPc5mwVBpqKxQIDAQABo4GqMIGnMB0GA1UdDgQWBBTMxmr1MUg8R/6/TWwCIbqphfljoTBlBgNVHSMEXjBcgBTMxmr1MUg8R/6/TWwCIbqphfljoaEupCwwKjEoMCYGA1UEAwwfQXp1cmVfSW9UX0h1Yl9DQV9DZXJ0X1Rlc3RfT25seYIUHYHcb3mi+sT1ACwjjNjePZwfo7swDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAYYwDQYJKoZIhvcNAQELBQADggIBAIkxatYN44jH3rcxLfKh9PVly0Wy1Tpvr9DtyX6wCmUH01VEtRlouajEHp/BvsyfcNbvo0popSc5O/T/xNSl0tpKipuJ/Q9bXfhbhYxuwrDtFH+pB8UpYuwWiJeSOXn8YLx+qQw/CcO/CYMjQ3QKPXjD/zwl8a9UAIAlWYn5iEgEl2QmZ6PEUn71jQBL9m7LlfmFBApt7RrtnjdLUxzblb3DgYaKF/OTdiZpwcLFf7BKJzWjKYqY0pB/zEslCjB3oKL5c9Pu0yTTindYQQsQll1gZL8MNNC5Yx5er9naMANku4BtA8bgCaDc2/H2+vFJKYm1mcFiB1vnmO31dGSFRfjGtfSNLYhH/4/ROR8OiNH3CfXq65M7PfGuVx9clwNYUWgKtAIiHNh8sjxA11+65g9zO/ssEsFJcVPXWGMON8Z1jgmcF1/mVNdPM+pPdeDwL97uSEGo549hETSzRxgxqs/QVXjMFKgRGsqqeon1gGRD5fmi6RQo/X/lVNySCdUZfL1PwlBpyG/ACbt88u725+UjLtayXDknhWw0AcIIc6Vbo3e8TVdYVzwJGp6Yae5Wsw0HHaXubgMj/IixeeQmK7XZTBSWITJbkApjDBbXiJAxxBMHYvBm8qPr3zWWMYe4KrwjkAFt5FTm9UZu9hqaMevAJT4ossb2chHQWkkpbyJQ"
"-----END CERTIFICATE-----\r\n";

static bool hasWifi = false;
int messageCount = 1;
int sentMessageCount = 0;
static bool messageSending = true;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities
static void InitWifi()
{
  Screen.print(2, "Connecting...");
  
  if (WiFi.begin() == WL_CONNECTED)
  {
    IPAddress ip = WiFi.localIP();
    Screen.print(1, ip.get_address());
    hasWifi = true;
    Screen.print(2, "Running... \r\n");
  }
  else
  {
    hasWifi = false;
    Screen.print(1, "No Wi-Fi\r\n ");
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// IoTHub callback functions
static void SendConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result)
{
  if (result == IOTHUB_CLIENT_CONFIRMATION_OK)
  {
    blinkSendConfirmation();
    sentMessageCount++;
  }

  Screen.print(1, "> IoT Hub");
  char line1[20];
  sprintf(line1, "Count: %d/%d",sentMessageCount, messageCount); 
  Screen.print(2, line1);

  messageCount++;
}

static void MessageCallback(const char* payLoad, int size)
{
  blinkLED();
  Screen.print(1, payLoad, true);
}

static int  DeviceMethodCallback(const char *methodName, const unsigned char *payload, int size, unsigned char **response, int *response_size)
{
  LogInfo("Try to invoke method %s", methodName);
  const char *responseMessage = "\"Successfully invoke device method\"";
  int result = 200;

  if (strcmp(methodName, "start") == 0)
  {
    LogInfo("Start sending telemetry data from leaf device");
    messageSending = true;
  }
  else if (strcmp(methodName, "stop") == 0)
  {
    LogInfo("Stop sending telemetry data from leaf device");
    messageSending = false;
  }
  else if (strcmp(methodName, "delay") == 0)
  {
    LogInfo("Setting different delay on leaf device");

    char *temp = (char *)malloc(size + 1);
    if (temp == NULL)
    {
      result = 500;
    }
    else
    {
      memcpy(temp, payload, size);
      temp[size] = '\0';
      parseDelayCommandPayload(temp);
      free(temp);
    }
  }
  else
  {
    LogInfo("No method %s found", methodName);
    responseMessage = "\"No method found\"";
    result = 404;
  }

  *response_size = strlen(responseMessage) + 1;
  *response = (unsigned char *)strdup(responseMessage);

  return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Arduino sketch
void setup() {
  Screen.init();
  Screen.print(0, "IoT DevKit");
  Screen.print(2, "Initializing...");
  
  Screen.print(3, " > Serial");
  Serial.begin(115200);

  // Initialize the WiFi module
  Screen.print(3, " > WiFi");
  hasWifi = false;
  InitWifi();
  if (!hasWifi)
  {
    Screen.print(3, "No WiFi!");
    return;
  }

  LogTrace("HappyPathSetup", NULL);

  Screen.print(3, " > Sensors");
  SensorInit();

  Screen.print(3, " > IoT Hub");
  DevKitMQTTClient_SetOption(OPTION_MINI_SOLUTION_NAME, "DevKit-GetStarted");
  DevKitMQTTClient_SetOption("TrustedCerts", edgeCert);
  DevKitMQTTClient_Init(true);

  DevKitMQTTClient_SetSendConfirmationCallback(SendConfirmationCallback);
  DevKitMQTTClient_SetMessageCallback(MessageCallback);
  DevKitMQTTClient_SetDeviceMethodCallback(DeviceMethodCallback);
}

void loop() {
  if (hasWifi)
  {
    if (messageSending)
    {
      // Send telemetry data
      char messagePayload[MESSAGE_MAX_LEN];

      if (readMessage(messagePayload)) {
        // LogInfo("%s", messagePayload);
        EVENT_INSTANCE* message = DevKitMQTTClient_Event_Generate(messagePayload, MESSAGE);
        DevKitMQTTClient_SendEventInstance(message);
      }
    }
    else
    {
      DevKitMQTTClient_Check();
    }
  }
  delay(1000);
}
