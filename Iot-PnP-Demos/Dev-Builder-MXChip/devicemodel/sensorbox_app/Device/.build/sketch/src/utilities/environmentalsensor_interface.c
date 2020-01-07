/************************************************************************************************
 * This code was automatically generated by Digital Twin Code Generator tool 0.6.7.
 * Changes to this file may cause incorrect behavior and will be lost if the code is regenerated.
 *
 * Generated Date: 20/01/04
 ***********************************************************************************************/

#include "environmentalsensor_interface.h"

#define MAX_MESSAGE_SIZE 256

//
// Callback function declarations and DigitalTwin writable (from service side) properties for this interface
//

static void EnvironmentalSensorInterface_Property_IntervalCallback(const DIGITALTWIN_CLIENT_PROPERTY_UPDATE* dtClientPropertyUpdate, void* userInterfaceContext);

//
//  Callback function declarations and DigitalTwin command names for this interface.
//

static void EnvironmentalSensorInterface_Command_ToggleCallback(const DIGITALTWIN_CLIENT_COMMAND_REQUEST* commandRequest, DIGITALTWIN_CLIENT_COMMAND_RESPONSE* commandResponse, void* userInterfaceContext);

//
// Application state associated with this interface.
// It contains the DIGITALTWIN_INTERFACE_CLIENT_HANDLE used for responses in callbacks along with properties set
// and representations of the property update and command callbacks invoked on given interface
//
typedef struct ENVIRONMENTALSENSOR_INTERFACE_STATE_TAG
{
    DIGITALTWIN_INTERFACE_CLIENT_HANDLE interfaceClientHandle;

    int interval;

} ENVIRONMENTALSENSOR_INTERFACE_STATE;

static ENVIRONMENTALSENSOR_INTERFACE_STATE appState;

// Callback function to process the command "toggle".
void EnvironmentalSensorInterface_Command_ToggleCallback(const DIGITALTWIN_CLIENT_COMMAND_REQUEST* commandRequest, DIGITALTWIN_CLIENT_COMMAND_RESPONSE* commandResponse, void* userInterfaceContext)
{
    ENVIRONMENTALSENSOR_INTERFACE_STATE* interfaceState = (ENVIRONMENTALSENSOR_INTERFACE_STATE*)userInterfaceContext;
    LogInfo("ENVIRONMENTALSENSOR_INTERFACE: toggle command invoked.");
    LogInfo("ENVIRONMENTALSENSOR_INTERFACE: toggle request payload=<%.*s>, context=<%p>", (int)commandRequest->requestDataLen, commandRequest->requestData, interfaceState);

    // Invoke device command here
    unsigned int statusCode = 200;

    char responsePayload[MAX_MESSAGE_SIZE];

    char* response;

    DIGITALTWIN_COMMAND_RESULT commandResult = EnvironmentalSensor_Command_Toggle(&response, &statusCode);

    // Serialize command response payload

    if (commandResult == DIGITALTWIN_COMMAND_OK &&
        EnvironmentalSensor_SerializeToggleCommandResponse(response, responsePayload, MAX_MESSAGE_SIZE))
    {
        DigitalTwinClientHelper_SetCommandResponse(commandResponse, (const unsigned char*)responsePayload, statusCode);

    }
    else
    {
        LogError("Failed to execute toggle command");
        const unsigned char errorResponse[] = "\"Failed to execute toggle command\"";
        DigitalTwinClientHelper_SetCommandResponse(commandResponse, errorResponse, statusCode);
    }

}

// DigitalTwinSample_ProcessCommandUpdate receives commands from the server.  This implementation acts as a simple dispatcher
// to the functions to perform the actual processing.
void EnvironmentalSensorInterface_ProcessCommandUpdate(const DIGITALTWIN_CLIENT_COMMAND_REQUEST* dtCommandRequest, DIGITALTWIN_CLIENT_COMMAND_RESPONSE* dtCommandResponse, void* userInterfaceContext)
{
    if (strcmp(dtCommandRequest->commandName, EnvironmentalSensorInterface_ToggleCommand) == 0)
    {
        EnvironmentalSensorInterface_Command_ToggleCallback(dtCommandRequest, dtCommandResponse, userInterfaceContext);
        return;
    }

    // If the command is not implemented by this interface, by convention we return a 501 error to server.
    LogError("ENVIRONMENTALSENSOR_INTERFACE: Command name <%s> is not associated with this interface", dtCommandRequest->commandName);
    const unsigned char commandNotImplementedResponse[] = "\"Requested command not implemented on this interface\"";
    (void)DigitalTwinClientHelper_SetCommandResponse(dtCommandResponse, commandNotImplementedResponse, 501);
}

// EnvironmentalSensorInterface_PropertyCallback is invoked when a property is updated (or failed) going to server.
// ALL property callbacks will be routed to this function and just have the userContextCallback set to the propertyName.
// Product code will potentially have context stored in this userContextCallback.
static void EnvironmentalSensorInterface_PropertyCallback(DIGITALTWIN_CLIENT_RESULT digitalTwinReportedStatus, void* userContextCallback)
{
    if (digitalTwinReportedStatus == DIGITALTWIN_CLIENT_OK)
    {
        ReportProperty_Succeeded_Callback("EnvironmentalSensor", (const char*)userContextCallback);
        LogInfo("ENVIRONMENTALSENSOR_INTERFACE: Updating property=<%s> succeeded", (const char*)userContextCallback);
    }
    else
    {
        ReportProperty_Error_Callback("EnvironmentalSensor", (const char*)userContextCallback);
        LogError("ENVIRONMENTALSENSOR_INTERFACE: Updating property=<%s> failed, error=<%s>", (const char*)userContextCallback, MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, digitalTwinReportedStatus));
    }
}

// Processes a property update, which the server initiated, for 'interval' property.
static void EnvironmentalSensorInterface_Property_IntervalCallback(const DIGITALTWIN_CLIENT_PROPERTY_UPDATE* dtClientPropertyUpdate, void* userInterfaceContext)
{
    ENVIRONMENTALSENSOR_INTERFACE_STATE* interfaceState = (ENVIRONMENTALSENSOR_INTERFACE_STATE*)userInterfaceContext;

    LogInfo("ENVIRONMENTALSENSOR_INTERFACE: interval property invoked...");
    LogInfo("ENVIRONMENTALSENSOR_INTERFACE: interval data=<%.*s>", (int)dtClientPropertyUpdate->propertyDesiredLen, dtClientPropertyUpdate->propertyDesired);

    DIGITALTWIN_CLIENT_PROPERTY_RESPONSE propertyResponse;

    // Version of this structure for C SDK.
    propertyResponse.version = DIGITALTWIN_CLIENT_PROPERTY_RESPONSE_VERSION_1;
    propertyResponse.responseVersion = dtClientPropertyUpdate->desiredVersion;

    // Parse string value and set updated property
    JSON_Value * jsonValue = json_parse_string((const char*)dtClientPropertyUpdate->propertyDesired);

    double newValue = json_value_get_number(jsonValue);

    bool isTypeValid = (json_value_get_type(jsonValue) == JSONNumber && newValue == (int)newValue);

    if (isTypeValid)
    {
        interfaceState->interval = (int)newValue;

        LogInfo("ENVIRONMENTALSENSOR_INTERFACE: Updating interval property with new value <%s> ...", dtClientPropertyUpdate->propertyDesired);
        bool updateResult = EnvironmentalSensor_Property_IntervalCallback(interfaceState->interval);
 
        if (updateResult)
        {
            propertyResponse.statusCode = 200;
            propertyResponse.statusDescription = "interval property is updated successfully";
        }
        else
        {
            LogError("ENVIRONMENTALSENSOR_INTERFACE: failed to update writable property interval...");

            propertyResponse.statusCode = 500;
            propertyResponse.statusDescription = "failed to update writable property";
        }
    }
    else
    {
        LogError("ENVIRONMENTALSENSOR_INTERFACE: Invalid desired value for interval, value should be Integer");
        propertyResponse.statusCode = 500;
        propertyResponse.statusDescription = "Invalid desired value for interval, value should be Integer";
    }
    json_value_free(jsonValue);

    // DigitalTwin_InterfaceClient_ReportPropertyAsync takes the DIGITALTWIN_CLIENT_PROPERTY_RESPONSE and returns information back to service.
    DIGITALTWIN_CLIENT_RESULT result = DigitalTwin_InterfaceClient_ReportPropertyAsync(appState.interfaceClientHandle, EnvironmentalSensorInterface_IntervalProperty, 
        dtClientPropertyUpdate->propertyDesired, dtClientPropertyUpdate->propertyDesiredLen, &propertyResponse,
        EnvironmentalSensorInterface_PropertyCallback, EnvironmentalSensorInterface_IntervalProperty);
    if (result != DIGITALTWIN_CLIENT_OK)
    {
        LogError("ENVIRONMENTALSENSOR_INTERFACE: DigitalTwin_InterfaceClient_ReportPropertyAsync for interval failed, error=<%s>", MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, result));
    }
    else
    {
        LogInfo("ENVIRONMENTALSENSOR_INTERFACE: Successfully queued property update for interval");
    }
}

// EnvironmentalSensorInterface_ProcessPropertyUpdate receives updated properties from the server.  This implementation
// acts as a simple dispatcher to the functions to perform the actual processing.
static void EnvironmentalSensorInterface_ProcessPropertyUpdate(const DIGITALTWIN_CLIENT_PROPERTY_UPDATE* dtClientPropertyUpdate, void* userInterfaceContext)
{
    if (strcmp(dtClientPropertyUpdate->propertyName, EnvironmentalSensorInterface_IntervalProperty) == 0)
    {
        EnvironmentalSensorInterface_Property_IntervalCallback(dtClientPropertyUpdate, userInterfaceContext);
        return;
    }

    // If the property is not implemented by this interface, presently we only record a log message but do not have a mechanism to report back to the service
    LogError("ENVIRONMENTALSENSOR_INTERFACE: Property name <%s> is not associated with this interface", dtClientPropertyUpdate->propertyName);
}

// EnvironmentalSensorInterface_TelemetryCallback is invoked when a DigitalTwin telemetry message is either successfully delivered to the service or else fails.
static void EnvironmentalSensorInterface_TelemetryCallback(DIGITALTWIN_CLIENT_RESULT digitalTwinTelemetryStatus, void* userContextCallback)
{
    (void)userContextCallback;
    if (digitalTwinTelemetryStatus == DIGITALTWIN_CLIENT_OK)
    {
        SendTelemetry_Succeeded_Callback("EnvironmentalSensor");
        LogInfo("ENVIRONMENTALSENSOR_INTERFACE: DigitalTwin successfully delivered telemetry message.");
    }
    else
    {
        SendTelemetry_Error_Callback("EnvironmentalSensor");
        LogError("ENVIRONMENTALSENSOR_INTERFACE: DigitalTwin failed to deliver telemetry message, error=<%s> ", MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, digitalTwinTelemetryStatus));
    }
}

DIGITALTWIN_CLIENT_RESULT EnvironmentalSensorInterface_Telemetry_SendAll()
{
    if (appState.interfaceClientHandle == NULL)
    {
        LogError("ENVIRONMENTALSENSOR_INTERFACE: interfaceClientHandle is required to be initialized before sending telemetries");
    }

    DIGITALTWIN_CLIENT_RESULT result;

    char combinedMessage[MAX_MESSAGE_SIZE];
    char telemetryValue[MAX_MESSAGE_SIZE];

    // Send multiple telemetries in a single message
    sprintf(combinedMessage, "{");

    EnvironmentalSensor_SerializeTemperatureTelemetry(telemetryValue, MAX_MESSAGE_SIZE);

    sprintf(combinedMessage + strlen(combinedMessage), "\"%s\":%s,", EnvironmentalSensorInterface_TemperatureTelemetry, telemetryValue);

    EnvironmentalSensor_SerializeHumidityTelemetry(telemetryValue, MAX_MESSAGE_SIZE);

    sprintf(combinedMessage + strlen(combinedMessage), "\"%s\":%s", EnvironmentalSensorInterface_HumidityTelemetry, telemetryValue);

    sprintf(combinedMessage + strlen(combinedMessage), "}");

    if ((result = DigitalTwin_InterfaceClient_SendTelemetryAsync(appState.interfaceClientHandle, (unsigned char*)combinedMessage, strlen(combinedMessage),
        EnvironmentalSensorInterface_TelemetryCallback, NULL)) != DIGITALTWIN_CLIENT_OK)
    {
        LogError("ENVIRONMENTALSENSOR_INTERFACE: DigitalTwin_InterfaceClient_SendTelemetryAsync failed for sending telemetry.");
    }

    return result;
}

// EnvironmentalSensorInterface_InterfaceRegisteredCallback is invoked when this interface
// is successfully or unsuccessfully registered with the service, and also when the interface is deleted.
static void EnvironmentalSensorInterface_InterfaceRegisteredCallback(DIGITALTWIN_CLIENT_RESULT dtInterfaceStatus, void* userInterfaceContext)
{
    LogInfo("EnvironmentalSensorInterface_InterfaceRegisteredCallback with status=<%s>, userContext=<%p>", MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, dtInterfaceStatus), userInterfaceContext);
    if (dtInterfaceStatus == DIGITALTWIN_CLIENT_OK)
    {
        // Once the interface is registered, send our reported properties to the service.  
        // It *IS* safe to invoke most DigitalTwin API calls from a callback thread like this, though it 
        // is NOT safe to create/destroy/register interfaces now.
        LogInfo("ENVIRONMENTALSENSOR_INTERFACE: Interface successfully registered.");
    }
    else if (dtInterfaceStatus == DIGITALTWIN_CLIENT_ERROR_INTERFACE_UNREGISTERING)
    {
        // Once an interface is marked as unregistered, it cannot be used for any DigitalTwin SDK calls.
        LogInfo("ENVIRONMENTALSENSOR_INTERFACE: Interface received unregistering callback.");
    }
    else
    {
        LogError("ENVIRONMENTALSENSOR_INTERFACE: Interface received failed, status=<%s>.", MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, dtInterfaceStatus));
    }
}

//
// Create DigitalTwin interface client handle
//
DIGITALTWIN_INTERFACE_CLIENT_HANDLE EnvironmentalSensorInterface_Create()
{
    DIGITALTWIN_INTERFACE_CLIENT_HANDLE interfaceHandle;
    DIGITALTWIN_CLIENT_RESULT result;

    memset(&appState, 0, sizeof(ENVIRONMENTALSENSOR_INTERFACE_STATE));

    if ((result = DigitalTwin_InterfaceClient_Create(EnvironmentalSensorInterfaceId,  EnvironmentalSensorInterfaceInstanceName, EnvironmentalSensorInterface_InterfaceRegisteredCallback, (void*)&appState, &interfaceHandle)) != DIGITALTWIN_CLIENT_OK)
    {
        LogError("ENVIRONMENTALSENSOR_INTERFACE: Unable to allocate interface client handle for interfaceId=<%s>, interfaceInstanceName=<%s>, error=<%s>", EnvironmentalSensorInterfaceId, EnvironmentalSensorInterfaceInstanceName, MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, result));
        interfaceHandle = NULL;
    }

    else if ((result = DigitalTwin_InterfaceClient_SetPropertiesUpdatedCallback(interfaceHandle, EnvironmentalSensorInterface_ProcessPropertyUpdate, (void*)&appState)) != DIGITALTWIN_CLIENT_OK)
    {
        LogError("ENVIRONMENTALSENSOR_INTERFACE: DigitalTwin_InterfaceClient_SetPropertiesUpdatedCallback failed. error=<%s>", MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, result));
        EnvironmentalSensorInterface_Close(interfaceHandle);
        interfaceHandle = NULL;
    }

    else if ((result = DigitalTwin_InterfaceClient_SetCommandsCallback(interfaceHandle, EnvironmentalSensorInterface_ProcessCommandUpdate, (void*)&appState)) != DIGITALTWIN_CLIENT_OK)
    {
        LogError("ENVIRONMENTALSENSOR_INTERFACE: DigitalTwin_InterfaceClient_SetCommandsCallbacks failed. error=<%s>", MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, result));
        EnvironmentalSensorInterface_Close(interfaceHandle);
        interfaceHandle = NULL;
    }

    else
    {
        LogInfo("ENVIRONMENTALSENSOR_INTERFACE: Created DIGITALTWIN_INTERFACE_CLIENT_HANDLE successfully for interfaceId=<%s>, interfaceInstanceName=<%s>, handle=<%p>", EnvironmentalSensorInterfaceId, EnvironmentalSensorInterfaceInstanceName, interfaceHandle);
        appState.interfaceClientHandle = interfaceHandle;
    }

    return interfaceHandle;
}

void EnvironmentalSensorInterface_Close(DIGITALTWIN_INTERFACE_CLIENT_HANDLE digitalTwinInterfaceClientHandle)
{
    // On shutdown, in general the first call made should be to DigitalTwin_InterfaceClient_Destroy.
    // This will block if there are any active callbacks in this interface, and then
    // mark the underlying handle such that no future callbacks shall come to it.
    DigitalTwin_InterfaceClient_Destroy(digitalTwinInterfaceClientHandle);

    // After DigitalTwin_InterfaceClient_Destroy returns, it is safe to assume
    // no more callbacks shall arrive for this interface and it is OK to free
    // resources callbacks otherwise may have needed.

}