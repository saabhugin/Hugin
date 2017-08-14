#!/bin/sh
#
# /root/scripts/button.sh

# Script for listening for button pressed.
# P8_14 = GPIO26 = pinVcc
# P8_16 = GPIO46 = pinGnd
# P8_18 = GPIO65 = pinIn
#
# pinVcc provides the button with 3.3V.
# pinGnd provides ground, connected via pulldown resistor to pinIn.
#
# pinIn is input which reads if button is pressed.
# If pressed, the value goes high.
#
# When button is pressed, the hugin main program starts.
# After the hugin logging is completed, the main.mat file is renamed.
# The new name is the next following free name in series according to the
# value in "ftnumber". 
#
# After the new name is given to the log file, the program waits for another
# pressed button. The button is sampled every 1 second.
#

# For reconfiguration of the pins used for the button, change the following parameters:
pinIn=65
pinGnd=46
pinVcc=26


# Setup ports and directory
# INIT GPIO port 75 (P8_42)
if [ ! -d "/sys/class/gpio/gpio$pinIn" ]
then
        echo $pinIn > /sys/class/gpio/export
        echo in > /sys/class/gpio/gpio$pinIn/direction
        echo "Port $pinIn set to input."
fi
#
# INIT GPIO port for Vcc
if [ ! -d "/sys/class/gpio/gpio$pinVcc" ]
then
        echo $pinVcc >/sys/class/gpio/export
        echo out > /sys/class/gpio/gpio$pinVcc/direction
        echo 1 > /sys/class/gpio/gpio$pinVcc/value
        echo "Port $pinVcc set to output"
fi
#
# INIT GPIO port for ground
if [ ! -d "/sys/class/gpio/gpio$pinGnd" ]
then
	echo $pinGnd > /sys/class/gpio/export
	echo out > /sys/class/gpio/gpio$pinGnd/direction
	echo 0 > /sys/class/gpio/gpio$pinGnd/value
	echo "Port $pinGnd set to output"
fi
#
# If log file directory does not exist create it
if [ ! -d "../logfiles" ]
then
        mkdir /root/logfiles
        echo "Logfiles directory created"
fi
#
# Main  loop for checking if button is pressed
while true
do
	#Check if button pressed
	c=$(cat /sys/class/gpio/gpio$pinIn/value)
	echo "Button = $c"
	if [ $c -eq 1 ] # If pressed
	then
	# Start hugin programs for logging
		/usr/hugin/hugin&
		sleep  20s
		# let hugin program start properly. IMU calibration takes about 15s.
		/root/main.elf
		# When main.elf ends, kill hugin process and change filename 
		# after a short break
		#
		killall hugin #Kill hugin process for a reboot next log
		echo 0 > /sys/class/gpio/gpio30/value # turn off the blue LED
		# The sleep time is used to ensure the logfile is saved correctly
		sleep 5s
		#
		#
		#Search till new filename is found.
		if [ -f "/root/scripts/ftnumber" ]
		then
			name=$(cat /root/scripts/ftnumber)
		else
			name=1001 # If no ftnumber is found
		fi
		# Search for first new unique test number
		while true
		do
			if [ ! -f "/root/logfiles/$name.mat" ]
			then
				mv "$PWD/main.mat" "/root/logfiles/$name.mat"
				echo $((name+1)) > /root/scripts/ftnumber
				echo "$name.mat created"
				break
			else
				echo "$name.mat exists"
				name=$((name+1))
			fi
		done
		echo "Main.elf ended\nPush the button to start another data log!\n"
		echo 1 > /sys/class/gpio/gpio30/value # Light the Blue LED
	fi
	sleep 0.1
done

exit 0
