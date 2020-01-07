# 1 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
//
// Core header files for C and IoTHub layer
//
# 5 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2
# 6 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2
# 7 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2
# 8 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2
# 9 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2
# 10 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2
# 11 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2
# 12 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2
# 13 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2

// IoT Central requires DPS.  Include required header and constants
# 16 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2
# 17 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2
# 18 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2
# 19 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 2

static bool iotHubConnected = false;

// State of DPS registration process.  We cannot proceed with DPS until we get into the state APP_DPS_REGISTRATION_SUCCEEDED.
typedef enum APP_DPS_REGISTRATION_STATUS_TAG
{
    APP_DPS_REGISTRATION_PENDING,
    APP_DPS_REGISTRATION_SUCCEEDED,
    APP_DPS_REGISTRATION_FAILED
} APP_DPS_REGISTRATION_STATUS;

const SECURE_DEVICE_TYPE secureDeviceTypeForProvisioning = SECURE_DEVICE_TYPE_SYMMETRIC_KEY;
const IOTHUB_SECURITY_TYPE secureDeviceTypeForIotHub = IOTHUB_SECURITY_TYPE_SYMMETRIC_KEY;

// DPSEndpoint=[DPS global endpoint];IdScope=[ID Scope];DeviceId=[Device ID];SymmetricKey=[symmetric key]
static const char *IOTHUBDPS_ENDPOINT = "DPSEndpoint";
static const char *IOTHUBDPS_IDSCOPE = "IdScope";
static const char *IOTHUBDPS_DEVICEID = "DeviceId";
static const char *IOTHUBDPS_SYMMETRICKEY = "SymmetricKey";

// The Device Provisioning Service (DPS) endpoint, learn more from https://docs.microsoft.com/en-us/azure/iot-dps/tutorial-set-up-device#create-the-device-registration-software.
static char *globalDpsEndpoint = 
# 40 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                                __null
# 40 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                                    ;
// The Device Provisioning Service (DPS) ID Scope.
static char *dpsIdScope = 
# 42 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                         __null
# 42 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                             ;
// The symmetric key, learn more from https://docs.microsoft.com/en-us/azure/iot-dps/concepts-symmetric-key-attestation.
static char *sasKey = 
# 44 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                     __null
# 44 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                         ;
// The Device Id, learn more from https://docs.microsoft.com/en-us/azure/iot-dps/use-hsm-with-sdk.
static char *deviceId = 
# 46 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                       __null
# 46 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                           ;

// TODO: Fill in DIGITALTWIN_DEVICE_CAPABILITY_MODEL_INLINE_DATA if want to make deivce self-describing.


static const char *digitalTwinSample_CustomProvisioningData = "{"
                                                              "\"__iot:interfaces\":"
                                                              "{"
                                                              "\"CapabilityModelId\": \"urn:mxchip:mxchip_iot_devkit:1\" ,"
                                                              "\"CapabilityModel\": \"" "{}" "\""
                                                              "}"
                                                              "}";

// Amount in ms to sleep between querying state from DPS registration loop
static const int dpsRegistrationPollSleep = 100;

// Maximum amount of times we'll poll for DPS registration being ready, 1 min.
static const int dpsRegistrationMaxPolls = (60 * 1000 / dpsRegistrationPollSleep);

// State of DigitalTwin registration process.  We cannot proceed with DigitalTwin until we get into the state APP_DIGITALTWIN_REGISTRATION_SUCCEEDED.
typedef enum APP_DIGITALTWIN_REGISTRATION_STATUS_TAG
{
    APP_DIGITALTWIN_REGISTRATION_PENDING,
    APP_DIGITALTWIN_REGISTRATION_SUCCEEDED,
    APP_DIGITALTWIN_REGISTRATION_FAILED
} APP_DIGITALTWIN_REGISTRATION_STATUS;



static char *dpsIotHubUri;
static char *dpsDeviceId;

static bool parseDPSConnectionString(const char *connection_string)
{
    if (connection_string == 
# 80 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                            __null
# 80 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                                )
    {
        do{ { (void)(0 && printf("connection_string is NULL")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 82 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 82 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 82, 0x01, "connection_string is NULL"); } }; }while((void)0,0);
        return false;
    }
    MAP_HANDLE connection_string_values_map;
    if ((connection_string_values_map = connectionstringparser_parse_from_char(connection_string)) == 
# 86 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                                                                                                     __null
# 86 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                                                                                                         )
    {
        do{ { (void)(0 && printf("Tokenizing failed on connectionString")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 88 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 88 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 88, 0x01, "Tokenizing failed on connectionString"); } }; }while((void)0,0);
        return false;
    }
    const char *_globalDpsEndpoint = Map_GetValueFromKey(connection_string_values_map, IOTHUBDPS_ENDPOINT);
    const char *_dpsIdScope = Map_GetValueFromKey(connection_string_values_map, IOTHUBDPS_IDSCOPE);
    const char *_sasKey = Map_GetValueFromKey(connection_string_values_map, IOTHUBDPS_SYMMETRICKEY);
    const char *_deviceId = Map_GetValueFromKey(connection_string_values_map, IOTHUBDPS_DEVICEID);
    if (_globalDpsEndpoint)
    {
        mallocAndStrcpy_s(&globalDpsEndpoint, _globalDpsEndpoint);
    }
    else
    {
        do{ { (void)(0 && printf("Couldn't find %s in connection string", IOTHUBDPS_ENDPOINT)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 101 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 101 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 101, 0x01, "Couldn't find %s in connection string", IOTHUBDPS_ENDPOINT); } }; }while((void)0,0);
    }
    if (_dpsIdScope)
    {
        mallocAndStrcpy_s(&dpsIdScope, _dpsIdScope);
    }
    else
    {
        do{ { (void)(0 && printf("Couldn't find %s in connection string", IOTHUBDPS_IDSCOPE)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 109 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 109 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 109, 0x01, "Couldn't find %s in connection string", IOTHUBDPS_IDSCOPE); } }; }while((void)0,0);
    }
    if (_sasKey)
    {
        mallocAndStrcpy_s(&sasKey, _sasKey);
    }
    else
    {
        do{ { (void)(0 && printf("Couldn't find %s in connection string", IOTHUBDPS_SYMMETRICKEY)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 117 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 117 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 117, 0x01, "Couldn't find %s in connection string", IOTHUBDPS_SYMMETRICKEY); } }; }while((void)0,0);
    }
    if (_deviceId)
    {
        mallocAndStrcpy_s(&deviceId, _deviceId);
    }
    else
    {
        do{ { (void)(0 && printf("Couldn't find %s in connection string", IOTHUBDPS_DEVICEID)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 125 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 125 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 125, 0x01, "Couldn't find %s in connection string", IOTHUBDPS_DEVICEID); } }; }while((void)0,0);
    }
    Map_Destroy(connection_string_values_map);

    if (globalDpsEndpoint == 
# 129 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                            __null 
# 129 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                                 || dpsIdScope == 
# 129 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                                                  __null 
# 129 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                                                       || sasKey == 
# 129 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                                                                    __null 
# 129 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                                                                         || deviceId == 
# 129 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                                                                                        __null
# 129 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                                                                                            )
    {
        return false;
    }
    return true;
}

static void provisioningRegisterCallback(PROV_DEVICE_RESULT register_result, const char *iothub_uri, const char *device_id, void *user_context)
{
    APP_DPS_REGISTRATION_STATUS *appDpsRegistrationStatus = (APP_DPS_REGISTRATION_STATUS *)user_context;

    if (register_result != PROV_DEVICE_RESULT_OK)
    {
        do{ { (void)(0 && printf("DPS Provisioning callback called with error state %d", register_result)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 142 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 142 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 142, 0x01, "DPS Provisioning callback called with error state %d", register_result); } }; }while((void)0,0);
        *appDpsRegistrationStatus = APP_DPS_REGISTRATION_FAILED;
    }
    else
    {
        if ((mallocAndStrcpy_s(&dpsIotHubUri, iothub_uri) != 0) ||
            (mallocAndStrcpy_s(&dpsDeviceId, device_id) != 0))
        {
            do{ { (void)(0 && printf("Unable to copy provisioning information")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 150 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
           __null
# 150 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
           ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 150, 0x01, "Unable to copy provisioning information"); } }; }while((void)0,0);
            *appDpsRegistrationStatus = APP_DPS_REGISTRATION_FAILED;
        }
        else
        {
            do{{ (void)(0 && printf("Provisioning callback indicates success.  iothubUri=%s, deviceId=%s", dpsIotHubUri, dpsDeviceId)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 155 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
           __null
# 155 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
           ) l(AZ_LOG_INFO, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 155, 0x01, "Provisioning callback indicates success.  iothubUri=%s, deviceId=%s", dpsIotHubUri, dpsDeviceId); } }; }while((void)0,0);
            *appDpsRegistrationStatus = APP_DPS_REGISTRATION_SUCCEEDED;
        }
    }
}

static bool registerDevice(bool traceOn)
{
    PROV_DEVICE_RESULT provDeviceResult;
    PROV_DEVICE_LL_HANDLE provDeviceLLHandle = 
# 164 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                                              __null
# 164 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                                                  ;
    bool result = false;

    APP_DPS_REGISTRATION_STATUS appDpsRegistrationStatus = APP_DPS_REGISTRATION_PENDING;

    if (IoTHub_Init() != 0)
    {
        do{ { (void)(0 && printf("IoTHub_Init failed")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 171 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 171 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 171, 0x01, "IoTHub_Init failed"); } }; }while((void)0,0);
        return false;
    }

    const char *connectionString = getIoTHubConnectionString();
    if (!parseDPSConnectionString(connectionString))
    {
        return false;
    }

    if (prov_dev_set_symmetric_key_info(deviceId, sasKey) != 0)
    {
        do{ { (void)(0 && printf("prov_dev_set_symmetric_key_info failed.")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 183 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 183 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 183, 0x01, "prov_dev_set_symmetric_key_info failed."); } }; }while((void)0,0);
    }
    else if (prov_dev_security_init(secureDeviceTypeForProvisioning) != 0)
    {
        do{ { (void)(0 && printf("prov_dev_security_init failed")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 187 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 187 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 187, 0x01, "prov_dev_security_init failed"); } }; }while((void)0,0);
    }
    else if ((provDeviceLLHandle = Prov_Device_LL_Create(globalDpsEndpoint, dpsIdScope, Prov_Device_MQTT_Protocol)) == 
# 189 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                                                                                                                      __null
# 189 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                                                                                                                          )
    {
        do{ { (void)(0 && printf("failed calling Prov_Device_Create")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 191 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 191 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 191, 0x01, "failed calling Prov_Device_Create"); } }; }while((void)0,0);
    }
    else if ((provDeviceResult = Prov_Device_LL_SetOption(provDeviceLLHandle, PROV_OPTION_LOG_TRACE, &traceOn)) != PROV_DEVICE_RESULT_OK)
    {
        do{ { (void)(0 && printf("Setting provisioning tracing on failed, error=%d", provDeviceResult)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 195 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 195 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 195, 0x01, "Setting provisioning tracing on failed, error=%d", provDeviceResult); } }; }while((void)0,0);
    }
    else if ((provDeviceResult = Prov_Device_LL_SetOption(provDeviceLLHandle, "TrustedCerts", certificates)) != PROV_DEVICE_RESULT_OK)
    {
        do{ { (void)(0 && printf("Setting provisioning TrustedCerts failed, error=%d", provDeviceResult)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 199 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 199 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 199, 0x01, "Setting provisioning TrustedCerts failed, error=%d", provDeviceResult); } }; }while((void)0,0);
    }
    else if ((provDeviceResult = Prov_Device_LL_Set_Provisioning_Payload(provDeviceLLHandle, digitalTwinSample_CustomProvisioningData)) != PROV_DEVICE_RESULT_OK)
    {
        do{ { (void)(0 && printf("Failed setting provisioning data, error=%d", provDeviceResult)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 203 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 203 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 203, 0x01, "Failed setting provisioning data, error=%d", provDeviceResult); } }; }while((void)0,0);
    }
    else if ((provDeviceResult = Prov_Device_LL_Register_Device(provDeviceLLHandle, provisioningRegisterCallback, &appDpsRegistrationStatus, 
# 205 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                                                                                                                                            __null
# 205 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                                                                                                                                                , 
# 205 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                                                                                                                                                  __null
# 205 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                                                                                                                                                      )) != PROV_DEVICE_RESULT_OK)
    {
        do{ { (void)(0 && printf("Prov_Device_Register_Device failed, error=%d", provDeviceResult)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 207 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
       __null
# 207 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 207, 0x01, "Prov_Device_Register_Device failed, error=%d", provDeviceResult); } }; }while((void)0,0);
    }
    else
    {
        // Pulling the registration status
        for (int i = 0; (i < dpsRegistrationMaxPolls) && (appDpsRegistrationStatus == APP_DPS_REGISTRATION_PENDING); i++)
        {
            ThreadAPI_Sleep(dpsRegistrationPollSleep);
            Prov_Device_LL_DoWork(provDeviceLLHandle);
        }

        if (appDpsRegistrationStatus == APP_DPS_REGISTRATION_SUCCEEDED)
        {
            do{{ (void)(0 && printf("DPS successfully registered.  Continuing on to creation of IoTHub device client handle.")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 220 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
           __null
# 220 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
           ) l(AZ_LOG_INFO, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 220, 0x01, "DPS successfully registered.  Continuing on to creation of IoTHub device client handle."); } }; }while((void)0,0);
            result = true;
        }
        else if (appDpsRegistrationStatus == APP_DPS_REGISTRATION_PENDING)
        {
            do{ { (void)(0 && printf("Timed out attempting to register DPS device")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 225 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
           __null
# 225 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
           ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 225, 0x01, "Timed out attempting to register DPS device"); } }; }while((void)0,0);
        }
        else
        {
            do{ { (void)(0 && printf("Error registering device for DPS")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 229 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
           __null
# 229 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
           ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino", __func__, 229, 0x01, "Error registering device for DPS"); } }; }while((void)0,0);
        }
    }

    if (provDeviceLLHandle != 
# 233 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino" 3 4
                             __null
# 233 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip-IoTCentral\\central_app\\devkit_device\\Device\\main.ino"
                                 )
    {
        Prov_Device_LL_Destroy(provDeviceLLHandle);
    }
    IoTHub_Deinit();

    return result;
}

void setup()
{
    char buff[512];

    // Initialize the board
    int ret = initIoTDevKit(1);
    if (ret != 0)
    {
        if (ret == -100)
        {
            Screen.print(1, "No Wi-Fi.\r\n \r\n ");
        }
        else
        {
            Screen.print(1, "Internal error!\r\nCheck log for\r\n more detail.");
        }
        return;
    }
    else
    {
        IPAddress ip = WiFi.localIP();
        snprintf(buff, sizeof(buff), "%s\r\nWiFi Connected\r\n%s", WiFi.SSID(), ip.get_address());
        Screen.print(1, buff);
    }

    // Initialize device model application
    if (registerDevice(false))
    {
        Screen.print(1, "Connecting\r\n IoT Hub...");

        buff[0] = 0;
        if (secureDeviceTypeForProvisioning == SECURE_DEVICE_TYPE_SYMMETRIC_KEY)
        {
            snprintf(buff, sizeof(buff),
                     "HostName=%s;DeviceId=%s;SharedAccessKey=%s",
                     dpsIotHubUri,
                     dpsDeviceId,
                     sasKey);
        }
        else if (secureDeviceTypeForProvisioning == SECURE_DEVICE_TYPE_X509)
        {
            snprintf(buff, sizeof(buff),
                     "HostName=%s;DeviceId=%s;UseProvisioning=true",
                     dpsIotHubUri,
                     dpsDeviceId);
        }

        if (pnp_device_initialize(buff, certificates) != 0)
        {
            digitalWrite(LED_AZURE, 0);
            Screen.print(1, "Error: \r\nIoT Hub is not\r\navailable.");
            iotHubConnected = false;
        }
        else
        {
            digitalWrite(LED_AZURE, 1);
            Screen.print(1, "PnP Enabled\r\nRunning...");
            iotHubConnected = true;
        }
    }
    else
    {
        digitalWrite(LED_AZURE, 0);
        Screen.print(1, "Error: \r\nRegistering\r\ndevice failed.\r\n");
        iotHubConnected = false;
    }
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (iotHubConnected)
    {
        pnp_device_run();
    }

    invokeDevKitPeripheral();
    delay(500);
}
