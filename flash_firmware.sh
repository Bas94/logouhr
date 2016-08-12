cd esptool
sudo python esptool.py -p $1 write_flash 0x00 ../esp8266-firmware/build.nodemcu/esp8266-firmware.bin
