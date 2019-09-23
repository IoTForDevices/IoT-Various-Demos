# Demo of Anomaly Detection Stream Analytics running on an Azure IoT Edge Device (RPi)

This demo allows you to show anomaly detection on the Edge using an Azure Stream Analytics Job that is executing on a Rasberry Pi 3B+. The device also contains a Sensor Hat for detecting tilt and providing visual feedback. The Tilt Monitor also uses a Power BI dashboard to show anomalies.

Some background on Anomaly Detection using ASA can be found in [this document](https://azure.microsoft.com/en-us/blog/anomaly-detection-using-built-in-machine-learning-models-in-azure-stream-analytics/).

## Pre-requisites

Here you will find detailed instruction to install [Azure IoT Edge on a RP3 running Raspbian Buster](../Generic-prerequisites/Raspbian-Buster-IoTEdge-RP3/README.md).

TODO - Description + Source code for python project on pi
TODO - Description + Source code (code behind for ASA) + ASA Query
TODO - Description + Source code for ASA Power BI
TODO - Link to Power BI
TODO - All routing information needs to be fixed



FROM /messages/* WHERE NOT IS_DEFINED($connectionModuleId) INTO $upstream


    "alertsToCloud": "FROM /messages/modules/avg-temp-asa-job/* INTO $upstream",
    "telemetryToAsa": "FROM /messages/* WHERE NOT IS_DEFINED($connectionModuleId) INTO BrokeredEndpoint(\"/modules/avg-temp-asa-job/inputs/temperature\")"


