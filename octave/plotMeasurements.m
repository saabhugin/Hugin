%%
clear; clc; close all;
addpath logfiles
load 1062.mat

%% Extract the data from yout_rt
time = yout_rt.time;
acc= squeeze(yout_rt.signals(1).values);
gyr = squeeze(yout_rt.signals(2).values);
euler = squeeze(yout_rt.signals(3).values);

%% Accelerometer plot
figure('Name','Accelerometer')
ax1=subplot(3,1,1);
stairs(time, acc(1,:))
legend('x')
ax2=subplot(3,1,2);
stairs(time, acc(2,:))
legend('y')
ax3=subplot(3,1,3);
stairs(time, acc(3,:))
legend('z')
linkaxes([ax1 ax2 ax3],'xy')
axis([min(time) max(time) 1.1*min(min(acc(:,:))) 1.1*max(max(acc(:,:)))])

%% Gyro plot
figure('Name','Gyro')
ax1=subplot(3,1,1);
stairs(time, 180/pi()*gyr(1,:))
legend('p')
ax2=subplot(3,1,2);
stairs(time, 180/pi()*gyr(2,:))
legend('q')
ax3=subplot(3,1,3);
stairs(time, 180/pi()*gyr(3,:))
legend('r')
linkaxes([ax1 ax2 ax3],'xy')
axis([min(time) max(time) 1.1*180/pi()*min(min(gyr(:,:))) 1.1*180/pi()*max(max(gyr(:,:)))])

%% Euler angles plot
figure('Name','Euler angles')
ax1=subplot(3,1,1);
stairs(time, 180/pi()*euler(1,:))
legend('yaw')
ax2=subplot(3,1,2);
stairs(time, 180/pi()*euler(2,:))
legend('pitch')
ax3=subplot(3,1,3);
stairs(time, 180/pi()*euler(3,:))
legend('roll')

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

