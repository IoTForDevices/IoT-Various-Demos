# Create IoT Hub and Device Provision Service and link them together
These steps can be executed from the Azure Portal or from an Azure CLI. You can either create a new IoT Hub or use an existing IoT Hub.

### Prerequisites:
1. S1 IoT Hub created
1. DPS created but not linked to IoT Hub
1. Have cloned or copied the azure-iot-sdk-c repository to your development machine

## Demo Steps:
1. Link the Device Provisioning Service to the IoT Hub
   - On the DPS Overview Blade, select **Linked IoT Hubs** and click the + Add button at the top.
1. Provide Subscription, IoT Hub and Access Policy information to link DPS to an IoT Hub.

### To Generate test certificates:

1. Create a new folder to store your keys in. All files will be created as children of this folder.
1. Copy *.cnf and *.sh from C:\Source\Repo\azure-iot-sdk-c\tools\CACertificates
1. Start Bash.
1. cd to the directory you want to create the keys in. All files will be created as children of this directory.
   - You can navigate to a Windows folder using /mnt/c/Source/Keys/< sample device >
1. chmod 700 ./certGen.sh
1. Run ./certGen.sh create_root_and_intermediate
1. Run ./certGen.sh create_device_certificate mydevice

### To add a single device enrollment:

1. On the Device Provisioning Service summary blade, select Manage enrollments. Select Individual Enrollments tab and click the Add individual enrollment button at the top. 
1. Under the Add Enrollment panel, enter the following information:
   - Select X.509 as the identity attestation Mechanism.
   - Under the Primary certificate .pem or .cer file, click Select a file to select the certificate file {certificate-name}_cert.pem created in the previous steps. 

### To create a simulated device that uses the key:

1. In the Azure portal, select the Overview blade for your Device Provisioning service and note down the Global Device Endpoint and ID Scope values.
1. Copy **package.json** and **register_x509.js** from folder: **C:\Source\Repo\azure-iot-sdk-node\provisioning\device\samples**
1. Copy the generated certificate and key into the same folder
1. Edit the register_x509.js file. Save the file after making the following changes:
   - Replace provisioning host with the Global Device Endpoint noted earlier.
   - Replace id scope with the Id Scope noted earlier. 
   - Replace registration id with the Registration Id you created the x.509 certificate for (this is the device name).
   - Replace cert filename and key filename with the files you copied in Step 2 above.
1. Open a command prompt in the sample folder and install all packages by entering **npm install** 
1. Execute the script and verify the device was provisioned successfully.
node register_x509.js
1. In the portal, navigate to the IoT hub linked to your provisioning service and open the IoT Devices blade. On successful provisioning of the simulated X.509 device to the hub, its device ID appears on the IoT Devices blade, with STATUS as enabled. 


### To add an enrollment group:

1. Add a root CA certificate to the DPS Service (generate keys identical to described previously)
1. Generate verification code in the DPS Service
1. Create a verification certificate and upload that to the DPS service
1. Create a new enrollment group
   - Either use the CA Certificate or upload a new intermediate certificate
1. Create a new device certificate
1. Create individual enrollment (just like the previous sample, but use a cat'd key file as public key for the device).
