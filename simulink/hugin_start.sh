# Script to start logging data on platform HUGIN
# Place file in ~/
rm main.mat& # remove previous logfile
../usr/hugin/hugin& Â# Start hugin program that samples sensors
./main.elf& # start simulink RT program.
