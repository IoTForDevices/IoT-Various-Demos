# 1 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
# 2 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2
# 3 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2
# 4 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2
# 5 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2
# 6 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2
# 7 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2
# 8 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2
# 9 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2
# 10 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2
# 11 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2

// IoT Central requires DPS.  Include required header and constants
# 14 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2
# 15 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2
# 16 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2
# 17 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 2


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
# 39 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                                __null
# 39 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                                    ;
// The Device Provisioning Service (DPS) ID Scope.
static char *dpsIdScope = 
# 41 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                         __null
# 41 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                             ;
// The symmetric key, learn more from https://docs.microsoft.com/en-us/azure/iot-dps/concepts-symmetric-key-attestation.
static char *sasKey = 
# 43 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                     __null
# 43 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                         ;
// The Registration ID, learn more from https://docs.microsoft.com/en-us/azure/iot-dps/use-hsm-with-sdk.
static char *deviceId = 
# 45 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                       __null
# 45 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                           ;

// TODO: Fill in DIGITALTWIN_DEVICE_CAPABILITY_MODEL_INLINE_DATA if want to make deivce self-describing.


static const char *digitalTwinSample_CustomProvisioningData = "{"
                                                              "\"__iot:interfaces\":"
                                                              "{"
                                                              "\"CapabilityModelId\": \"urn:DotNETForDevices:SensorboxModel:1\" ,"
                                                              "\"CapabilityModel\": \"" "{}" "\""
                                                              "}"
                                                              "}";

// Amount in ms to sleep between querying state from DPS registration loop
static const int dpsRegistrationPollSleep = 100;

// Maximum amount of times we'll poll for DPS registration being ready, 1 min.
static const int dpsRegistrationMaxPolls = (60 * 1000 / dpsRegistrationPollSleep);



static char *dpsIotHubUri;
static char *dpsDeviceId;

static bool parseDPSConnectionString(const char *connection_string)
{
    if (connection_string == 
# 71 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                            __null
# 71 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                                )
    {
        do{ { (void)(0 && printf("connection_string is NULL")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 73 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 73 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 73, 0x01, "connection_string is NULL"); } }; }while((void)0,0);
        return false;
    }
    MAP_HANDLE connection_string_values_map;
    if ((connection_string_values_map = connectionstringparser_parse_from_char(connection_string)) == 
# 77 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                                                                                                     __null
# 77 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                                                                                                         )
    {
        do{ { (void)(0 && printf("Tokenizing failed on connectionString")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 79 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 79 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 79, 0x01, "Tokenizing failed on connectionString"); } }; }while((void)0,0);
        return false;
    }

    const char *_globalDpsEndpoint = Map_GetValueFromKey(connection_string_values_map, IOTHUBDPS_ENDPOINT);
    const char *_dpsIdScope = Map_GetValueFromKey(connection_string_values_map, IOTHUBDPS_IDSCOPE);
    const char *_sasKey = Map_GetValueFromKey(connection_string_values_map, IOTHUBDPS_SYMMETRICKEY);
    const char *_deviceId = Map_GetValueFromKey(connection_string_values_map, IOTHUBDPS_DEVICEID);

    if (_globalDpsEndpoint)
    {
        do{{ (void)(0 && printf("_globalDpsEndpoint = %s", _globalDpsEndpoint)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 90 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 90 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_INFO, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 90, 0x01, "_globalDpsEndpoint = %s", _globalDpsEndpoint); } }; }while((void)0,0);
        mallocAndStrcpy_s(&globalDpsEndpoint, _globalDpsEndpoint);
    }
    else
    {
        do{ { (void)(0 && printf("Couldn't find %s in connection string", IOTHUBDPS_ENDPOINT)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 95 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 95 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 95, 0x01, "Couldn't find %s in connection string", IOTHUBDPS_ENDPOINT); } }; }while((void)0,0);
    }
    if (_dpsIdScope)
    {
        do{{ (void)(0 && printf("_dpsIdScope = %s", _dpsIdScope)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 99 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 99 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_INFO, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 99, 0x01, "_dpsIdScope = %s", _dpsIdScope); } }; }while((void)0,0);
        mallocAndStrcpy_s(&dpsIdScope, _dpsIdScope);
    }
    else
    {
        do{ { (void)(0 && printf("Couldn't find %s in connection string", IOTHUBDPS_IDSCOPE)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 104 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 104 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 104, 0x01, "Couldn't find %s in connection string", IOTHUBDPS_IDSCOPE); } }; }while((void)0,0);
    }
    if (_sasKey)
    {
        do{{ (void)(0 && printf("_sasKey = %s", _sasKey)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 108 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 108 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_INFO, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 108, 0x01, "_sasKey = %s", _sasKey); } }; }while((void)0,0);
        mallocAndStrcpy_s(&sasKey, _sasKey);
    }
    else
    {
        do{ { (void)(0 && printf("Couldn't find %s in connection string", IOTHUBDPS_SYMMETRICKEY)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 113 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 113 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 113, 0x01, "Couldn't find %s in connection string", IOTHUBDPS_SYMMETRICKEY); } }; }while((void)0,0);
    }
    if (_deviceId)
    {
        do{{ (void)(0 && printf("_deviceId = %s", _deviceId)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 117 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 117 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_INFO, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 117, 0x01, "_deviceId = %s", _deviceId); } }; }while((void)0,0);
        mallocAndStrcpy_s(&deviceId, _deviceId);
    }
    else
    {
        do{ { (void)(0 && printf("Couldn't find %s in connection string", IOTHUBDPS_DEVICEID)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 122 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 122 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 122, 0x01, "Couldn't find %s in connection string", IOTHUBDPS_DEVICEID); } }; }while((void)0,0);
    }
    Map_Destroy(connection_string_values_map);

    if (globalDpsEndpoint == 
# 126 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                            __null 
# 126 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                                 || dpsIdScope == 
# 126 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                                                  __null 
# 126 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                                                       || sasKey == 
# 126 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                                                                    __null 
# 126 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                                                                         || deviceId == 
# 126 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                                                                                        __null
# 126 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
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
# 139 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 139 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 139, 0x01, "DPS Provisioning callback called with error state %d", register_result); } }; }while((void)0,0);
        *appDpsRegistrationStatus = APP_DPS_REGISTRATION_FAILED;
    }
    else
    {
        if ((mallocAndStrcpy_s(&dpsIotHubUri, iothub_uri) != 0) ||
            (mallocAndStrcpy_s(&dpsDeviceId, device_id) != 0))
        {
            do{ { (void)(0 && printf("Unable to copy provisioning information")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 147 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
           __null
# 147 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
           ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 147, 0x01, "Unable to copy provisioning information"); } }; }while((void)0,0);
            *appDpsRegistrationStatus = APP_DPS_REGISTRATION_FAILED;
        }
        else
        {
            do{{ (void)(0 && printf("Provisioning callback indicates success.  iothubUri=%s, deviceId=%s", dpsIotHubUri, dpsDeviceId)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 152 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
           __null
# 152 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
           ) l(AZ_LOG_INFO, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 152, 0x01, "Provisioning callback indicates success.  iothubUri=%s, deviceId=%s", dpsIotHubUri, dpsDeviceId); } }; }while((void)0,0);
            *appDpsRegistrationStatus = APP_DPS_REGISTRATION_SUCCEEDED;
        }
    }
}

static bool registerDevice(bool traceOn)
{
    PROV_DEVICE_RESULT provDeviceResult;
    PROV_DEVICE_LL_HANDLE provDeviceLLHandle = 
# 161 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                                              __null
# 161 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                                                  ;
    bool result = false;

    APP_DPS_REGISTRATION_STATUS appDpsRegistrationStatus = APP_DPS_REGISTRATION_PENDING;

    if (IoTHub_Init() != 0)
    {
        do{ { (void)(0 && printf("IoTHub_Init failed")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 168 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 168 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 168, 0x01, "IoTHub_Init failed"); } }; }while((void)0,0);
        return false;
    }

    if (prov_dev_set_symmetric_key_info(deviceId, sasKey) != 0)
    {
        do{ { (void)(0 && printf("prov_dev_set_symmetric_key_info failed.")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 174 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 174 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 174, 0x01, "prov_dev_set_symmetric_key_info failed."); } }; }while((void)0,0);
    }
    else if (prov_dev_security_init(secureDeviceTypeForProvisioning) != 0)
    {
        do{ { (void)(0 && printf("prov_dev_security_init failed")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 178 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 178 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 178, 0x01, "prov_dev_security_init failed"); } }; }while((void)0,0);
    }
    else if ((provDeviceLLHandle = Prov_Device_LL_Create(globalDpsEndpoint, dpsIdScope, Prov_Device_MQTT_Protocol)) == 
# 180 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                                                                                                                      __null
# 180 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                                                                                                                          )
    {
        do{ { (void)(0 && printf("failed calling Prov_Device_Create")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 182 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 182 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 182, 0x01, "failed calling Prov_Device_Create"); } }; }while((void)0,0);
    }
    else if ((provDeviceResult = Prov_Device_LL_SetOption(provDeviceLLHandle, PROV_OPTION_LOG_TRACE, &traceOn)) != PROV_DEVICE_RESULT_OK)
    {
        do{ { (void)(0 && printf("Setting provisioning tracing on failed, error=%d", provDeviceResult)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 186 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 186 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 186, 0x01, "Setting provisioning tracing on failed, error=%d", provDeviceResult); } }; }while((void)0,0);
    }
    else if ((provDeviceResult = Prov_Device_LL_SetOption(provDeviceLLHandle, "TrustedCerts", certificates)) != PROV_DEVICE_RESULT_OK)
    {
        do{ { (void)(0 && printf("Setting provisioning TrustedCerts failed, error=%d", provDeviceResult)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 190 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 190 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 190, 0x01, "Setting provisioning TrustedCerts failed, error=%d", provDeviceResult); } }; }while((void)0,0);
    }
    else if ((provDeviceResult = Prov_Device_LL_Set_Provisioning_Payload(provDeviceLLHandle, digitalTwinSample_CustomProvisioningData)) != PROV_DEVICE_RESULT_OK)
    {
        do{ { (void)(0 && printf("Failed setting provisioning data, error=%d", provDeviceResult)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 194 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 194 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 194, 0x01, "Failed setting provisioning data, error=%d", provDeviceResult); } }; }while((void)0,0);
    }
    else if ((provDeviceResult = Prov_Device_LL_Register_Device(provDeviceLLHandle, provisioningRegisterCallback, &appDpsRegistrationStatus, 
# 196 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                                                                                                                                            __null
# 196 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                                                                                                                                                , 
# 196 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                                                                                                                                                  __null
# 196 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                                                                                                                                                      )) != PROV_DEVICE_RESULT_OK)
    {
        do{ { (void)(0 && printf("Prov_Device_Register_Device failed, error=%d", provDeviceResult)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 198 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 198 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 198, 0x01, "Prov_Device_Register_Device failed, error=%d", provDeviceResult); } }; }while((void)0,0);
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
# 211 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
           __null
# 211 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
           ) l(AZ_LOG_INFO, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 211, 0x01, "DPS successfully registered.  Continuing on to creation of IoTHub device client handle."); } }; }while((void)0,0);
            result = true;
        }
        else if (appDpsRegistrationStatus == APP_DPS_REGISTRATION_PENDING)
        {
            do{ { (void)(0 && printf("Timed out attempting to register DPS device")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 216 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
           __null
# 216 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
           ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 216, 0x01, "Timed out attempting to register DPS device"); } }; }while((void)0,0);
        }
        else
        {
            do{ { (void)(0 && printf("Error registering device for DPS")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 220 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
           __null
# 220 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
           ) l(AZ_LOG_ERROR, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 220, 0x01, "Error registering device for DPS"); } }; }while((void)0,0);
        }
    }

    if (provDeviceLLHandle != 
# 224 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
                             __null
# 224 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
                                 )
    {
        Prov_Device_LL_Destroy(provDeviceLLHandle);
    }
    IoTHub_Deinit();

    return result;
}

static bool registerDeviceRetry(bool traceOn, int retryNumber, int retryInterval)
{
    char buff[32];
    Screen.print(1, "Registering...\r\n  ");
    for (int i = 0; i < retryNumber; i++)
    {
        if (registerDevice(traceOn))
        {
            return true;
        }
        delay(retryInterval);
        snprintf(buff, sizeof(buff), " retry %d", i + 1);
        Screen.print(2, buff);
    }
    return false;
}

static void connectIoTService(void)
{
    char buff[512];
    iotHubConnected = false;
    digitalWrite(LED_AZURE, 0);

    // Initialize device model application
    if (registerDeviceRetry(false, 10, 10000))
    {
        Screen.print(1, "Connecting\r\n Azure IoT...");

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

        do{{ (void)(0 && printf(buff)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 278 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino" 3 4
       __null
# 278 "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino"
       ) l(AZ_LOG_INFO, "c:\\Source\\Repo\\IoT-Various-Demos\\Iot-PnP-Demos\\Dev-Builder-MXChip\\devicemodel\\sensorbox_app\\Device\\main.ino", __func__, 278, 0x01, buff); } }; }while((void)0,0);

        if (pnp_device_initialize(buff, certificates) != 0)
        {
            Screen.print(1, "Error: \r\nAzure IoT is not\r\navailable.");
        }
        else
        {
            digitalWrite(LED_AZURE, 1);
            iotHubConnected = true;
            screen_main();
        }
    }
    else
    {
        Screen.print(1, "Error: \r\nRegistering\r\ndevice failed.\r\n");
    }
}

void setup()
{
    char buff[64];

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

    const char *connectionString = getIoTHubConnectionString();
    if (!parseDPSConnectionString(connectionString))
    {
        Screen.print(0, "Setting error\r\nPlease re-config\r\nthe device\r\nin AP mode.");
        return;
    }

    connectIoTService();
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (iotHubConnected)
    {
        pnp_device_run();
    }
    else
    {
        connectIoTService();
    }


    invokeDevKitPeripheral();
    delay(500);
}
