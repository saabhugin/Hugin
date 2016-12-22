%%
load main.mat

%% 
% IMU
figure
ax1=subplot(3,1,1);
stairs(yout_rt.time, yout_rt.signals(1).values(1,:))
legend('acc\_x')
ax2=subplot(3,1,2);
stairs(yout_rt.time, yout_rt.signals(1).values(2,:))
legend('acc\_y')
ax3=subplot(3,1,3);
stairs(yout_rt.time, yout_rt.signals(1).values(3,:))
legend('acc\_z')
linkaxes([ax1 ax2 ax3],'x')

figure
ax1=subplot(3,1,1);
stairs(yout_rt.time, yout_rt.signals(2).values(1,:))
legend('gyro\_x')
ax2=subplot(3,1,2);
stairs(yout_rt.time, yout_rt.signals(2).values(2,:))
legend('gyro\_y')
ax3=subplot(3,1,3);
stairs(yout_rt.time, yout_rt.signals(2).values(3,:))
legend('gyro\_z')
linkaxes([ax1 ax2 ax3],'x')

figure
ax1=subplot(3,1,1);
stairs(yout_rt.time, yout_rt.signals(3).values(1,:))
legend('mag\_x')
ax2=subplot(3,1,2);
stairs(yout_rt.time, yout_rt.signals(3).values(2,:))
legend('Mag\_y')
ax3=subplot(3,1,3);
stairs(yout_rt.time, yout_rt.signals(3).values(3,:))
legend('Mag\_z')
linkaxes([ax1 ax2 ax3],'x')

%%
% SBus
figure
ax1=subplot(4,1,1);
stairs(yout_rt.time, yout_rt.signals(7).values(1,:))
legend('roll cmd')
ax2=subplot(4,1,2);
stairs(yout_rt.time, yout_rt.signals(7).values(2,:))
legend('pitch cmd')
ax3=subplot(4,1,3);
stairs(yout_rt.time, yout_rt.signals(7).values(3,:))
legend('throttle cmd')
ax4=subplot(4,1,4);
stairs(yout_rt.time, yout_rt.signals(7).values(4,:))
legend('yaw cmd')
linkaxes([ax1 ax2 ax3 ax4],'x')


%%
% PWM readings
figure
title('PWM readings');
ax1=subplot(4,1,1);
stairs(yout_rt.time, yout_rt.signals(8).values(1,:))
legend('ch1')
ax2=subplot(4,1,2);
stairs(yout_rt.time, yout_rt.signals(8).values(2,:))
legend('ch2')
ax3=subplot(4,1,3);
stairs(yout_rt.time, yout_rt.signals(8).values(3,:))
legend('ch3')
ax4=subplot(4,1,4);
stairs(yout_rt.time, yout_rt.signals(8).values(4,:))
legend('ch4')
linkaxes([ax1 ax2 ax3 ax4],'x')

%%
% SBus and PWM readings
figure
ax1=subplot(4,1,1);
title('SBus and PWM readings');
hold on;
stairs(yout_rt.time, yout_rt.signals(7).values(1,:))
stairs(yout_rt.time, yout_rt.signals(8).values(1,:))
legend('ch1_{SBus}', 'ch1_{PWM}')
ax2=subplot(4,1,2);
hold on;
stairs(yout_rt.time, yout_rt.signals(7).values(2,:))
stairs(yout_rt.time, yout_rt.signals(8).values(2,:))
legend('ch2_{SBus}', 'ch2_{PWM}')
ax3=subplot(4,1,3);
hold on;
stairs(yout_rt.time, yout_rt.signals(7).values(3,:))
stairs(yout_rt.time, yout_rt.signals(8).values(3,:))
legend('ch3_{SBus}', 'ch3_{PWM}')
ax4=subplot(4,1,4);
hold on;
stairs(yout_rt.time, yout_rt.signals(7).values(4,:))
stairs(yout_rt.time, yout_rt.signals(8).values(4,:))
legend('ch4_{SBus}', 'ch4_{PWM}')
linkaxes([ax1 ax2 ax3 ax4],'x')

