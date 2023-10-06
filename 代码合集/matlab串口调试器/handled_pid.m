clear
warning off
%% 手动PID调参

%% 串口初始化

instrreset;
global s;
s=serial('com3','baudrate',115200) ;
 %fopen(s) ; %Open Com Port

global num_data ;
%% 中央控制台
num_data=2050;  %采集PID曲线数据点的数量
pid=[

0.04
5
0
-2

    ];

%% 操作函数
disp('PID参数：')
disp(pid')
tic
pid_curve_data=pid_work(pid);
toc

function data=pid_work(x)
global s;
 fopen(s) ; %Open Com Port

start_order=pid_order(1,x);%启动命令
stop_order=pid_order(0,x); %停止命令

for i=1:5
    fwrite(s,stop_order); %发送5次关机命令
    pause(1e-2);
end

fwrite(s,start_order); %发送1次开机命令

global num_data;
data=[];
hold off
while(size(data,1)<num_data)
    data0=[];
    rec=fscanf(s);
    data0=sbz_parse(rec);
%     hold on
%     plot(length(data)+1:length(data)+length(data0),data0,'r');
    data=[data;data0];
end
disp('得分:')
disp((1-pid_judge(data))*100);

hold off
draw_pid(data)

for i=1:5
    fwrite(s,stop_order);
    pause(1e-2);
end

 fclose(s) ; %Close Com Port
end