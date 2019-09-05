# Demo of Anomaly Detection Stream Analytics running on an Azure IoT Edge Device (RPi)

This demo allows you to show anomaly detection on the Edge using an Azure Stream Analytics Job that is executing on an Rasberry Pi 3B+. The device also contains a Sensor Hat for detecting tilt and providing visual feedback. The Tilt Monitor also uses a Power BI dashboard to show anomalies.

Some background on Anomaly Detection using ASA can be found in [this document](https://azure.microsoft.com/en-us/blog/anomaly-detection-using-built-in-machine-learning-models-in-azure-stream-analytics/).

## Pre-requisites

Have this ready before showing the demo (allow for at least 60 minutes of preparation time):

### Install the latest version of Raspbian to a Raspberry Pi
If you already have a Raspberry Pi running Rasbpian Strech or Raspbian Buster you can skip these steps.

1) Download the latest [Raspbian Lite Image](https://downloads.raspberrypi.org/raspbian_lite_latest)
1) Burn the image to an SD card, easiest by using [Etcher](https://www.balena.io/etcher/)
1) Enable SSH by creating a file containing one single space in the root of the SD card. The file should be called **ssh** 
1) Add network information by creating a file called **wpa_supplicant.conf** in the root of the SD card with the following content:
```Bash
    country=NL  # Change to your own country code
	ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
	update_config=1
	network={
	    ssid="NETWORK-NAME"
	    psk="NETWORK-PASSWORD"
	}
```
5) Boot the Raspberry Pi
1) Remotely login to the Raspberry Pi:
```Bash
    ssh pi@<ip-address>, password=raspberry
```
6) Change the Hostname and Password using
```Bash
    sudo raspi-config
```
7) Get the latest updates to the OS using
```Bash
    sudo apt-get update -y
    sudo apt-get upgrade -y
```

A complete, expanded version of this can be found [here](https://desertbot.io/blog/headless-raspberry-pi-3-bplus-ssh-wifi-setup).

### Install Docker and Azure IoT Edge on Raspbian Buster

Currently, Moby doesn't install on Raspbian Buster, so instead we are going to use Docker-CE (which is fine for non-production devices).

1) Download the latest versions of **containerd.&#8203;io**, **docker-ce-cli** and **docker-ce** from [this location](https://download.docker.com/linux/debian/dists/buster/pool/stable/armhf). The way to do this is to copy the link to the latest version listed and download them on the Raspberry Pi using **wget *link***
1) Install the debian packages in the same order you downloaded them, add the current user to the docker group and reboot
```Bash
	sudo dpkg -i containerd.io*
	sudo dpkg -i docker-ce-cli*
	sudo dpkg -i docker-ce*
	sudo usermod -aG docker $USER
	sudo reboot
```
3) Since Raspbian Buster does not ship with the required libssl1.0.2 library, we need to manually install this before installing the IoT Edge Runtime:
```Bash
	sudo apt-get install libssl1.0.2
```
4) Install the IoT Edge Runtime:
```Bash
	curl https://packages.microsoft.com/config/debian/stretch/multiarchprod.list > ./microsoft-prod.list && \
	sudo cp ./microsoft-prod.list /etc/apt/sources.list.d/ && \
	curl https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > microsoft.gpg && \
	sudo cp ./microsoft.gpg /etc/apt/trusted.gpg.d/ && \
	sudo apt-get update && \
	sudo apt-get -y install iotedge
```
5) Add the IoT Edge Connection String and restart Azure IoT Edge
```Bash
	sudo nano /etc/iotedge/config.yaml
	sudo systemctl restart iotedge
 ```
 