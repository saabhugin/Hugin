clear; clc; close all;
addpath logfiles
load main.mat
version = "new";

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


if (version == "org")
%% Gyro plot original hugin
figure('Name','Gyro')
ax1=subplot(3,1,1);
stairs(time, gyr(1,:))
legend('p')
ax2=subplot(3,1,2);
stairs(time, gyr(2,:))
legend('q')
ax3=subplot(3,1,3);
stairs(time, gyr(3,:))
legend('r')
linkaxes([ax1 ax2 ax3],'xy')
%axis([min(time) max(time) 1.1*180/pi()*min(min(gyr(:,:))) 1.1*180/pi()*max(max(gyr(:,:)))])

%% Magnotometer plot
figure('Name','Magnetometer')
ax1=subplot(3,1,1);
stairs(time, euler(1,:))
legend('x')
ax2=subplot(3,1,2);
stairs(time, euler(2,:))
legend('y')
ax3=subplot(3,1,3);
stairs(time, euler(3,:))
legend('z')
end

if (version == "new")
%% Gyro plot new hugin
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

end
