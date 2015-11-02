#!/bin/bash
#
# HUGIN - button_setup.sh
# Date created: 2015-11-01
#
# Setup file for the button script. 
# Sets port66 as input to read if button is  pressed.
# Sets port67 as output, to provide 3.3v supply
# Creates directory logfiles if it does not exists. 
# 
# INIT GPIO port  66 (P8_07)
if [ ! -d "/sys/class/gpio/gpio66" ]
then
        echo 66 > /sys/class/gpio/export
        echo in > /sys/class/gpio/gpio66/direction
        echo 1 > /sys/class/gpio/gpio66/active_low
        echo "Port 66 set to input."
        sleep 1
fi
#
# INIT GPIO port 67 (P8_08)
if [ ! -d "/sys/class/gpio/gpio67" ]
then
        echo 67 >/sys/class/gpio/export
        echo out > /sys/class/gpio/gpio67/direction
        echo 1 > /sys/class/gpio/gpio67/value
        echo "Port 67 set to output"
        sleep 1
fi
#
# If log file directory does not exist create it
if [ ! -d "../logfiles" ]
then
        mkdir ../logfiles
        echo "Logfiles directory created"
        sleep 1
fi
#


