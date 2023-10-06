function score = pid_judge(error)

global num_data; 
% target=error(1);
% ct_area=0.05;
% ct=target*ct_area;
max=abs(error(1));
max_j=0;
abs_error=abs(error);
j=0;
for i=1:num_data
%     if(error(i)<0)
%         abs_error(i)= abs_error(i)*30;
%     end
   j=j+abs_error(i)*i; 
   max_j=max_j+i*max;
end
score=j/max_j;
end

% function j = pid_judge(error)
% 
% num_error=length(error);
% 
% abs_error=abs(error);
% jc=error(num_error);
% abs_jc=abs_error(num_error);
% 
% ache_time=0;
% 
% j=0;
% 
% for i=1:num_error
%     if(abs(abs_jc-abs_error(i))<5)
%         ache_time=i;
%         break;
%     end
% end
% 
% for i=1:num_error
%     j=j+i*abs_error(i);
%     if(error(i)<0)
%         j=j+1e3*abs_error(i);
%     end
%     if(j>ache_time)
%         j=j+1e2*abs_error(i);
%     end   
% end
% 
% j=j+abs_jc*1e5;
% 
% j=1e20/j;
% 
% disp(j);
% disp('m_ga');
% end
% 
