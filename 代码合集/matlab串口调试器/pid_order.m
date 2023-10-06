function pidorder = pid_order(stop,pid)

if(size(pid,1)>size(pid,2))
    pid=pid';
end

if length(pid)<9
   pid=[pid,zeros(1,9-length(pid))];
end

pidorder=[pid,stop];

pidorder=sbz_format(pidorder);

end

