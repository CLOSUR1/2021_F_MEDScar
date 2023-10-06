function data=sbz_parse(s)

len=length(s);
single=[];
i=1;
data=[];
while(1)
    row_data=[];
    flag=0;
    if(i>len)
        break
    end
    if(s(i)=='&')
        while(1)
            i=i+1;
            if(i>len)
                break
            end
            if(s(i)=='!')
                flag=~flag;
            end
            if(flag==1&&s(i)~='!')
                single=[single,s(i)];
            end
            if(flag==0)
                row_data=[row_data,str2num(char(single))];
                single=[];
            end
            if(s(i)=='*')
                break;
            end
        end
    else
        i=i+1;
        if(i>len)
            break
        end
    end
    if(size(data)==0)
        data=[data;  row_data];
    else if(length(row_data)==size(data,2))
            data=[data;row_data];
        end
    end
end

% function data=sbz_parse(s)
% data=[];
% i=1;
% while(1)
%     data_f=[];
%     data_0=[];
%     if(s(i)=='&')
%         j=1;
%         while(1)
%             i=i+1;
%             if(i>length(s))
%                 break;
%             end
%             if(s(i)=='*')
%                 break;
%             end
%             data_0(j)=s(i);
%             j=j+1;
%         end
%         len=length(data_0);
%         k=1;
%         while(1)
%             if(k>len)
%                 break;
%             end
%             if(data_0(k)==33)
%                 l=1;
%                 num=[];
%                 while(1)
%                     k=k+1;
%                     if(k>len)
%                         break;
%                     end
%                     if(data_0(k)==33)
%                         break;
%                     end
%                     num(l)=data_0(k);
%                     l=l+1;
%                 end
%                 data_f=[data_f,str2num(char(num))];
%             end
%             if(k>len)
%                 break;
%             end
%         end
%     end
%     if(size(data)==0)
%         data=[data;data_f];
%     end
%     if(length(data_f)<size(data,2))
%     else
%         data=[data;data_f];
%     end
%     i=i+1;
%     if(i>length(s))
%         break;
%     end
% end
% end