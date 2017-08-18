clear; clc; close all;

addpath ../../../MATLAB/Flygprov_170816

load 4007.mat

%% Extract the data from yout_rt
time = yout_rt.time;
acc= squeeze(yout_rt.signals(1).values);
gyr = squeeze(yout_rt.signals(2).values);
euler = squeeze(yout_rt.signals(3).values);

%% Accelerometer plot
figure('Name','Accelerometer')
ax1=subplot(3,1,1);
stairs(time, acc(1,:))
ylabel('acceleration [g]')
xlabel('time [s]')
legend('x')
ax2=subplot(3,1,2);
stairs(time, acc(2,:))
ylabel('acceleration [g]')
xlabel('time [s]')
legend('y')
ax3=subplot(3,1,3);
stairs(time, acc(3,:))
ylabel('acceleration [g]')
xlabel('time [s]')
legend('z')
linkaxes([ax1 ax2 ax3],'xy')
axis([min(time) max(time) 1.1*min(min(acc(:,:))) 1.1*max(max(acc(:,:)))])

saveas(gcf, 'accel' ,'png')

%% Gyro plot new hugin
figure('Name','Gyro')
ax1=subplot(3,1,1);
stairs(time, 180/pi()*gyr(1,:))
ylabel('rate [degrees/s]')
xlabel('time [s]')
legend('p')
ax2=subplot(3,1,2);
stairs(time, 180/pi()*gyr(2,:))
ylabel('rate [degree/s]')
xlabel('time [s]')
legend('q')
ax3=subplot(3,1,3);
stairs(time, 180/pi()*gyr(3,:))
ylabel('rate [degrees/s]')
xlabel('time [s]')
legend('r')
linkaxes([ax1 ax2 ax3],'xy')
axis([min(time) max(time) 1.1*180/pi()*min(min(gyr(:,:))) 1.1*180/pi()*max(max(gyr(:,:)))])

saveas(gcf, 'gyro' ,'png')

%% Euler angles plot
figure('Name','Euler angles')
ax1=subplot(3,1,1);
stairs(time, 180/pi()*euler(1,:))
ylabel('angle [degrees]')
xlabel('time [s]')
legend('yaw')
ax2=subplot(3,1,2);
stairs(time, 180/pi()*euler(2,:))
ylabel('angle [degrees]')
xlabel('time [s]')
legend('pitch')
ax3=subplot(3,1,3);
stairs(time, 180/pi()*euler(3,:))
ylabel('angle [degrees]')
xlabel('time [s]')
legend('roll')

saveas(gcf, 'euler' ,'png')

%% Extract the data from yout_rt
rc= squeeze(yout_rt.signals(7).values);
ext_ctrl = squeeze(yout_rt.signals(8).values);
motor_u = squeeze(yout_rt.signals(10).values);
thrust = (ext_ctrl(1,:) + ext_ctrl(2,:) + ext_ctrl(3,:) + ext_ctrl(4,:))/4; 
u_roll = (ext_ctrl(1,:) - ext_ctrl(2,:) - ext_ctrl(3,:) + ext_ctrl(4,:))/4; 
u_pitch = (ext_ctrl(1,:) + ext_ctrl(2,:) - ext_ctrl(3,:) - ext_ctrl(4,:))/4; 
u_yaw = (-ext_ctrl(1,:) + ext_ctrl(2,:) -ext_ctrl(3,:) +ext_ctrl(4,:))/4; 
%%ACC = fft(iddata(acc', [], 0.02));

%% SBUS commands 
figure('Name', 'SBUS Signals')
ax1=subplot(2,1,1);
plot(time,rc(1:4,:))
title('SBUS -  RC command')
ax2=subplot(2,1,2);
plot(time,rc(5:13,:))
title('SBUS - Extra commands')
linkaxes([ax1 ax2], 'x')

%% Motor signals from Simulink
figure('Name', 'Motor signal')
plot(time, motor_u)

%% PWM reading from ATMega
figure('Name', 'PWM reading')
plot(time, ext_ctrl) 

%%
figure
plot(time, motor_u(3,:))
hold on
plot(time, ext_ctrl)
legend('Throttle RC command', 'Motor 1', 'Motor 2', 'Motor 3', 'Motor 4', 'Location', 'Northwest')


%% Control signals
figure('Name', 'Control Signals')
ax1=subplot(2,2,1);
plot(time, thrust)
title('Collective')
ax2=subplot(2,2,2);
plot(time, u_roll)
title('u_{roll}')
ax3=subplot(2,2,3);
plot(time, u_pitch)
title('u_{pitch}')
ax4=subplot(2,2,4);
plot(time, u_yaw)
title('u_{yaw}')
linkaxes([ax1 ax2 ax3 ax4],'x')

%% Input-Output data
%%figure
%%plot(ACC)

%% Extra plots
samples = 1:3500;

% roll - p
figure('Name', 'SBUS Signals')
ax1=subplot(2,1,1);
plot(time(samples),rc(1:1,samples))
title('SBUS -  RC command')
legend('roll');

ax2=subplot(2,1,2);
stairs(time(samples), 180/pi()*gyr(1,samples))
ylabel('rate [degrees/s]')
xlabel('time [s]')
title('IMU')
legend('p')

linkaxes([ax1 ax2],'x')
axis([min(time(samples)) max(time(samples)) 1.1*180/pi()*min(min(gyr(1,samples))) 1.1*180/pi()*max(max(gyr(1,samples)))])

saveas(gcf, 'roll_p' ,'png')

% pitch - q 
figure('Name', 'SBUS Signals')
ax1=subplot(2,1,1);
plot(time(samples),rc(2:2,samples))
title('SBUS -  RC command')
legend('pitch')

ax2=subplot(2,1,2);
stairs(time(samples), 180/pi()*gyr(2,samples))
ylabel('rate [degrees/s]')
xlabel('time [s]')
title('IMU')
legend('q')

linkaxes([ax1 ax2],'x')
axis([min(time(samples)) max(time(samples)) 1.1*180/pi()*min(min(gyr(2,samples))) 1.1*180/pi()*max(max(gyr(2,samples)))])

saveas(gcf, 'pitch_q' ,'png')

% yaw - r 
figure('Name', 'SBUS Signals')
ax1=subplot(2,1,1);
plot(time(samples),-rc(4:4,samples))
title('SBUS -  RC command')
legend('yaw')

ax2=subplot(2,1,2);
stairs(time(samples), 180/pi()*gyr(3,samples))
ylabel('rate [degrees/s]')
xlabel('time [s]')
title('IMU')
legend('r')

linkaxes([ax1 ax2],'x')
axis([min(time(samples)) max(time(samples)) 1.1*180/pi()*min(min(gyr(3,samples))) 1.1*180/pi()*max(max(gyr(3,samples)))])

saveas(gcf, 'yaw_r' ,'png')

% thrust - accelerometer z-axis 
figure('Name', 'SBUS Signals')
ax1=subplot(2,1,1);
plot(time(samples),rc(3:3,samples))
title('SBUS -  RC command')
legend('thrust')

ax2=subplot(2,1,2);
stairs(time(samples), acc(3,samples))
ylabel('acceleration [g]')
xlabel('time [s]')
title('IMU')
legend('acceleration z-axis')

linkaxes([ax1 ax2],'x')
axis([min(time(samples)) max(time(samples)) 1.5*min(min(acc(3,samples))) 1.5*max(max(acc(3,samples)))])

saveas(gcf, 'thrust_accelzaxis' ,'png')