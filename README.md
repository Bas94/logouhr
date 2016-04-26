# logouhr
Will eventually contain all relevant code/design files and docuentation for the logouhr project.

# dependency install
To install all needed dependencies you can run the install-`dependencies.sh`. It will clone all needed reposetories like arduino SDK and esptool to flash the esp.
You have to call it from the root directory of this reposetory.

# flashing the chip
Run the `flash_firmware.sh` with the correct output device to flash the firmware. 
You can use this script if you have connected your esp via USB-UART converter. The call should look like this:
```
flash_firmware.sh /dev/ttyUSB0
```
