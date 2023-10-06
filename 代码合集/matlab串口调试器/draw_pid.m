function  draw_pid(data)

plot(1:length(data),data,'r');
hold on
pid=-data+data(1);
% plot(1:length(data),pid,'b--');

plot(1:length(data),zeros(1,length(data)),'g--');
grid on;
end

