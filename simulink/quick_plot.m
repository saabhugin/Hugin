%%
load main.mat
%%
figure
ax1=subplot(3,1,1)
stairs(yout_rt.time, yout_rt.signals(1).values(1,:))
legend('acc\_x')
ax2=subplot(3,1,2)
stairs(yout_rt.time, yout_rt.signals(1).values(2,:))
legend('acc\_y')
ax3=subplot(3,1,3)
stairs(yout_rt.time, yout_rt.signals(1).values(3,:))
legend('acc\_z')
linkaxes([ax1 ax2 ax3],'x')

figure
ax1=subplot(3,1,1)
stairs(yout_rt.time, yout_rt.signals(2).values(1,:))
legend('gyro\_x')
ax2=subplot(3,1,2)
stairs(yout_rt.time, yout_rt.signals(2).values(2,:))
legend('gyro\_y')
ax3=subplot(3,1,3)
stairs(yout_rt.time, yout_rt.signals(2).values(3,:))
legend('gyro\_z')
linkaxes([ax1 ax2 ax3],'x')

figure
ax1=subplot(3,1,1)
stairs(yout_rt.time, yout_rt.signals(3).values(1,:))
legend('mag\_x')
ax2=subplot(3,1,2)
stairs(yout_rt.time, yout_rt.signals(3).values(2,:))
legend('Mag\_y')
ax3=subplot(3,1,3)
stairs(yout_rt.time, yout_rt.signals(3).values(3,:))
legend('Mag\_z')
linkaxes([ax1 ax2 ax3],'x')