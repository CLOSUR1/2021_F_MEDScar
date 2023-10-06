function stop
global s;
stop_order=pid_order(0,0); 
fwrite(s,stop_order);
fclose(s) ; 
end

