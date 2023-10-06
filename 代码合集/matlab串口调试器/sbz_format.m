function str= sbz_format(data)

num=length(data);

str=[];
str=[str,'&'];
for i=1:num
    str=[str,'!',num2str(data(i)),'!'];
end
str=[str,'*'];

end

