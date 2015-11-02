#!/bin/sh
#
# This shell command is to be run att startup of HUGIN beagle bone black.
# Its purpouse is to startup the nessecary programs for automatic loging etc.
# The file is started using Cron, a built-in tool for task management in debian
# For this script file to be started, the following lines needs to be added to
# Cron for a new BeagleBone. Copy startup.sh to root.
#
# Open a terminal on your beaglebone and type
# 	sudo crontab -e
# This opens an editor for Cron, add the following to the file
# @reboot ./startup.sh &
#
# NOTE: If changes are done on a windows machine. Run the following commands
# after the file is copied to the BBB:
# 	sed s/{ctrl+v}{ctrl+m}// startup.sh > filename.tmp && mv filename.tmp startup.sh
# Where ctrl+v means pressing ctrl and v simultaneously
# and also
#	chmod 755 startup.sh

# At the moment, it  sets the GPIO port 30 (pin 11) as output to light the blue
# LED on Hugin to indicate that the BeagleBone is started and connection is possible. 

# --------   LIGHT LED  -----------
echo "Starting the LED lightning program"
cd /sys/class/gpio
# Set pin 11 (GPIO 30) as GPIO-port
echo "Directory changed. Creating GPIO port"
echo 30 > export
# Set direction of the GPIO
echo "GPIO-port set. Changing direction to out."
echo out > gpio30/direction
# Set value to high
echo "Port set to output. Lighting LED: Now."
echo 1 > gpio30/value
# Change directory back to root.
cd ~/
# ---------------------------------
#./button.sh
