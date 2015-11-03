#!/bin/sh
#
# Script for listening for button pressed.
# Connect button between port P8_8 and P8_7 GPIO 67 and 66 respectively.
# And P8_07 with P8_30 via pulldown resistor.
#
# GPIO67 provides the button with 3.3V, if 3.3V source is available elsewhere
# GPIO67 is not needed.
# GPIO89 provides ground, connected via pulldown resistor to GPIO66.
#
# GPIO66 is input which reads if button is pressed.
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
# Setup ports and directory
# INIT GPIO port  66 (P8_07)
if [ ! -d "/sys/class/gpio/gpio66" ]
then
        echo 66 > /sys/class/gpio/export
        echo in > /sys/class/gpio/gpio66/direction
        echo "Port 66 set to input."
fi
#
# INIT GPIO port 67 (P8_08)
if [ ! -d "/sys/class/gpio/gpio67" ]
then
        echo 67 >/sys/class/gpio/export
        echo out > /sys/class/gpio/gpio67/direction
        echo 1 > /sys/class/gpio/gpio67/value
        echo "Port 67 set to output"
fi
#
# INIT GPIO port 89 (P8_30)
if [ ! -d "/sys/class/gpio/gpio89" ]
then
	echo 89 > /sys/class/gpio/export
	echo out > /sys/class/gpio/gpio89/direction
	echo 0 > /sys/class/gpio/gpio89/value
	echo "Port 89 set to output"
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
	c=$(cat /sys/class/gpio/gpio66/value)
	# echo "Button = $c"
	if [ $c -eq 1 ] # If pressed
	then
	# Start hugin programs for logging
		/usr/hugin/hugin&
		/root/main.elf
		#When main.elf ends, change filename
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
		killall hugin #Kill hugin process for a reboot next log
		echo 1 > /sys/class/gpio/gpio30/value # Light the Blue LED
	fi
	sleep 0.1
done

exit 0
