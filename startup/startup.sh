#!/bin/bash
:'
source /home/pi/access_mdp/startup/gpio.sh

# Export pins so that we can use them
exportPin 4
exportPin 6
exportPin 26

# Set pins as outputs
setOutput 4
setOutput 6
setOutput 26

setState 4 "0"
setState 6 "0"


setState 26 "1"
sleep 20
sudo qmicli -d /dev/cdc-wdm0 --dms-set-operating-mode='online'
sudo ip link set wwan0 down
echo 'Y' | sudo tee /sys/class/net/wwan0/qmi/raw_ip
sudo ip link set wwan0 up
setState 26 "0"

sudo qmicli -p -d /dev/cdc-wdm0 --device-open-net='net-raw-ip|net-no-qos-header' --wds-start-network="apn='claro.pe',ip-type=4" --client-no-release-cid
setState 26 "1"
sleep 5

sudo udhcpc -i wwan0
#
#while true
#do
#	setState 26 "1"
#	sleep 0.5
#	setState 26 "0"
#	sleep 0.5
#done
'
source /root/.bashrc
./home/pi/access_mdp/build/main
