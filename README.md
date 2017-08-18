# Hugin
Hugin is a user friendly, rapid prototyping solution built for the Beaglebone Black. Different systems such as controllers and filters can be implemented in the Simulink/MATLAB environment and easily be compiled and uploaded to the Beaglebone Black. Via the UDP socket protocoll, models created in Simulink can communicate and share data with programs running on the Linux system. 

## Installing
To install the Hugin software, upload the .c-files to your Beaglebone Black and compile them. 
Use the main.slx model to get started prototyping in Simulink.

## Running
Simulink models are compiled and transfered using the Build-function in Simulink. 
Start the main program and the compiled main model program from the Linux console.

## Retreiving data
Data is stored onboard. WinSCP can be a good choice for file transfer.

The data is recored and, if the software is inialized with the `hugin_start.sh` shell script, the files will be automatically renamed to minimize risk of overwriting results.
