#!/bin/bash

GADGET_NAME=audio0

mkdir -p /sys/kernel/config/usb_gadget/${GADGET_NAME}
cd /sys/kernel/config/usb_gadget/${GADGET_NAME}

echo 0x1d6b > idVendor
echo 0x0104 > idProduct

mkdir strings/0x409
echo "012345679" > strings/0x409/serialnumber
echo "Linux Foundation" > strings/0x409/manufacturer
echo "Multifunction Composite Gadget" > strings/0x409/product

mkdir -p configs/c.1/strings/0x409
echo "Audio Gadget" > configs/c.1/strings/0x409/configuration
echo 120 > configs/c.1/MaxPower

mkdir -p functions/uac1.0
ln -s functions/uac1.0 configs/c.1/

ls /sys/class/udc > UDC

