# Supporting Scripts to simplify setting up the Demo
## Create-test-certs.sh
This script can be used to generate test certificates to be used to securily connect leaf devices to a transparent gateway. The script also copies the generated certificates to the target device (transparent gateway). The folder in which the certificates are copied are defined at the beginning of the script and correspond with the settings in the IoT Edge security daemon file.

**Prerequisites to run the script:**
The development machine and the target device need to be able to communicate over ssh using key-based authentication. This actually allows the scp command to execute without asking passwords each time it is executed. [This document on OpenSSH](https://help.ubuntu.com/community/SSH/OpenSSH/Keys) gives more details on how to set this up.

