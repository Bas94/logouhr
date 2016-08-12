#! /bin/bash

git clone --recursive https://github.com/thunderace/Esp8266-Arduino-Makefile.git dependencies
cd dependencies
git checkout 88493e7ba55b9ea4178b86b9b6e6b9f1f7034eed
./install-x86_64-pc-linux-gnu.sh
cd libraries
git clone https://github.com/adafruit/Adafruit_NeoPixel.git
cd Adafruit_NeoPixel
git checkout v1.0.6
cd ../../..
git clone https://github.com/themadinventor/esptool.git
