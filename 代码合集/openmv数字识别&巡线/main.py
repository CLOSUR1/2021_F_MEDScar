import sensor, image, time, lcd
from pyb import UART,LED

sensor.reset() # 初始化摄像头
sensor.set_pixformat(sensor.RGB565) # 格式为 RGB565.
sensor.set_framesize(sensor.QQVGA2)
sensor.skip_frames(10) # 跳过10帧，使新设置生效
sensor.set_auto_whitebal(False)               # Create a clock object to track the FPS.
sensor.set_vflip(0)
sensor.set_hmirror(0)

clock = time.clock()
lcd.init(type=1)

baud=9600
uart = UART(3,baud)  
uart.init(baud, bits=8, parity=None, stop=1) #串口初始化，波特率9600

led=LED(1)#LED初始化


def abs(a): #求绝对值函数
    if a>0:
        return a
    else:
        return -a

def dec(a,d): #数组每个元素都减d
    c=a
    for i in range(len(a)):
        c[i]=c[i]-d
    return c

def mean(a): #求数组平均值
    return sum(a)/len(a)

def cross(a,b):    #卷积函数
    n=max(len(a),len(b))
    if len(a)==n:
        long=a
        short=b
    else:
        long=b
        short=a
    c=[0]*n
    j=0
    i=0
    valid=1
    while i<n and j<len(short):  #判断a,b哪个元素数量多
        if abs(short[j]-long[i])<2:  #如果相差小于2，则认为匹配正确
            c[i]=valid
            i+=1       #两数组同时向后滑动
            j+=1
            valid+=1   #匹配度+1
        else:          #如果短的数组的元素与长数组对应元素相差超过2，则认为短数组元素缺项，两数组本应该一样长，实际测量可能导致缺项
            valid-=1   #匹配度-1
            c[i]=0
            i+=1       #只有短数组继续滑动
    return c

def mycov(a,b):
    aver_a=mean(a)
    aver_b=mean(b)
    dec_a=dec(a,aver_a)
    dec_b=dec(b,aver_b)
    return mean(cross(dec_a,dec_b))    #计算两数组的卷积匹配程度

def cov2(data,d):
    return mycov(data[0],d[0])*mycov(data[1],d[1]) #最终结果，由横纵坐标分别匹配程度的积

##############################
def between(a,b,c):     
    if (a>=b and a<=c) or (a>=c and a<=b):
        return True
    else:
        return False


def PIXEL_TEST(T,BT): #颜色判别，判断像素块是否属于红色或黑色
    if between(T[0],BT[0],BT[1]) and between(T[1],BT[2],BT[3])and between(T[2],BT[4],BT[5]):
        return 1
    else:
        return 0



def sbz_format(x):#串口数据帧封装
        data_trans='&'
        for i in x:
            data_trans+=('!'+str(i)+'!')
        data_trans+='*'
        return data_trans



def Blob_Pixel_Test(img,blob):     #提取数字特征点横纵坐标数据

    ROI_H=2

    RX=blob.x()
    RY=blob.y()
    H=blob.h()
    W=blob.w()
    dx=[0]
    dy=[0]

    skip=0
    e=3
    for i in [int(H/ROI_H*6/10),int(H/ROI_H*1.2/4)]:
        for j in range(int(W/ROI_H)):
            ROI=(int(RX+j*ROI_H),int(RY+i*ROI_H),ROI_H,ROI_H)

            statistics=img.get_statistics(roi=ROI)
            COLOR_THRESHOLD=[statistics.l_mode() ,statistics.a_mode() ,statistics.b_mode()] 

            if PIXEL_TEST(COLOR_THRESHOLD,BLACK_THRESHOLD)==1: #判断该点是否为黑色
                if skip==False:
                    #img.draw_rectangle((int(RX+j*ROI_H+e),int(RY+i*ROI_H+e),ROI_H,ROI_H),color=(255,0,0)) #绘制特征点图像
                    dx=dx+[int(10*(ROI[0]-RX+e)/W)]
                    dy=dy+[int(10*(ROI[1]-RY+e)/H)]
                    skip=1
            else:
                skip=0

    for i in [int(W/ROI_H/2)]:
        for j in range(int(H/ROI_H)):
            ROI=(int(RX+i*ROI_H),int(RY+j*ROI_H),ROI_H,ROI_H)
            statistics=img.get_statistics(roi=ROI)
            COLOR_THRESHOLD=[statistics.l_mode() ,statistics.a_mode() ,statistics.b_mode()]


            if PIXEL_TEST(COLOR_THRESHOLD,BLACK_THRESHOLD)==1:
                if skip==False:
                    #img.draw_rectangle((int(RX+i*ROI_H+e),int(RY+j*ROI_H+e),ROI_H,ROI_H),color=(255,0,0)) #绘制特征点图像
                    dx=dx+[int(10*(ROI[0]-RX+e)/W)]
                    dy=dy+[int(10*(ROI[1]-RY+e)/H)]
                    skip=1
            else:
                skip=0

    #print([dx,dy])
    return [dx,dy]

#########################################################
def Get_Num(d):     #数字识别总函数
    data=[test1(d),test2(d),test3(d),test4(d),test5(d),test6(d),test7(d),test8(d)]
    num=1                              #分别把测量的数据和1~8的标准数据进行卷积匹配，选匹配程度最高的那个作为结果
    target=max(data)
    for i in range(len(data)):
        if data[i]==target:
            return i+1

def supercov(d,d0):
    sumcov=0
    for i in range(len(d0)):
        sumcov+=cov2(d0[i],d)
    return sumcov/len(d0)

def test1(d):   #数字1测试函数

    d0=[
    [[0, 8, 2, 8, 6], [0, 6, 3, 3, 1]]  #存储的数字1的标准特征点数据
    ]
    return supercov(d,d0)

def test2(d): #数字2测试函数

    d0=[
    [[0, 5, 9, 5, 5, 5], [0, 6, 3, 0, 5, 9]]
    ]
    return supercov(d,d0)

def test3(d):

    d0=[
    [[0, 8, 7, 5, 5, 5], [0, 6, 2, 0, 4, 9]]
    ]
    return supercov(d,d0)


def test4(d):

    d0=[
    [[0, 0, 6, 3, 6, 4, 4], [0, 6, 6, 3, 3, 1, 6]]
    ]
    return supercov(d,d0)


def test5(d):

    d0=[
    [[0, 8, 0, 5, 5, 5], [0, 6, 3, 0, 3, 9]]
    ]
    return supercov(d,d0)

def test6(d):
                         
    d0=[
    [[0, 0, 8, 0, 5, 5, 5], [0, 5, 5, 2, 0, 3, 9]]
    ]
    return supercov(d,d0)

def test7(d):

    d0=[
    [[0, 4, 6, 5, 5], [0, 6, 3, 0, 4]]
    ]
    return supercov(d,d0)

def test8(d):

    d0=[
    [[0, 1, 8, 1, 8, 5, 5, 5], [0, 6, 6, 3, 3, 0, 4, 9]]
    ]
    return supercov(d,d0)


########################################################


def get_redline(img):  #巡线函数

    ROI_H=4
    W=128
    H=160
    POINT=[0,0]
    count=0
    length=[0,0]
    for i in [int(H/ROI_H/1.3),int(H/ROI_H/1.125)]:
        FIRST=0
        LAST=0
        for j in [8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26]:
            ROI=(int(j*ROI_H),int(i*ROI_H),ROI_H,ROI_H)
            statistics=img.get_statistics(roi=ROI)
            COLOR_THRESHOLD=[statistics.l_mean() ,statistics.a_mean() ,statistics.b_mean()]
            img.draw_rectangle((int(j*ROI_H),int(i*ROI_H),ROI_H,ROI_H),color=(0,0,255))

            if PIXEL_TEST(COLOR_THRESHOLD,RED_THRESHOLD)==1:      #判断色块是否属于红色
                img.draw_rectangle((int(j*ROI_H),int(i*ROI_H),ROI_H,ROI_H),color=(255,0,0))
                if FIRST==0:
                    FIRST=j-17
                LAST=j-17
            POINT[count]=(LAST+FIRST)/2
        count+=1

    ROI_H=4
    for i in [0]:
        for j in [11,12,13,16,17,18,21,22,23]:
            ROI=(int(j*ROI_H),int(i*ROI_H),ROI_H,ROI_H)
            statistics=img.get_statistics(roi=ROI)
            COLOR_THRESHOLD=[statistics.l_mean() ,statistics.a_mean() ,statistics.b_mean()]
            img.draw_rectangle((int(j*ROI_H),int(i*ROI_H),ROI_H,ROI_H),color=(0,0,255))

            if PIXEL_TEST(COLOR_THRESHOLD,RED_THRESHOLD)==1:
                img.draw_rectangle((int(j*ROI_H),int(i*ROI_H),ROI_H,ROI_H),color=(255,0,0))
                length[0]+=1
    ROI_H=10
    for i in [int(H/ROI_H)-1]:
        for j in [2,3,5,6,7,8,10,11]:
            ROI=(int(j*ROI_H),int(i*ROI_H),ROI_H,ROI_H)
            statistics=img.get_statistics(roi=ROI)
            COLOR_THRESHOLD=[statistics.l_mean() ,statistics.a_mean() ,statistics.b_mean()]
            img.draw_rectangle((int(j*ROI_H),int(i*ROI_H),ROI_H,ROI_H),color=(0,0,255))
                
            if PIXEL_TEST(COLOR_THRESHOLD,RED_THRESHOLD)==1:
                img.draw_rectangle((int(j*ROI_H),int(i*ROI_H),ROI_H,ROI_H),color=(255,0,0))
                length[1]+=1

    return [(POINT[0]-POINT[1]),(POINT[0]+POINT[1])/2,length[0],length[1]] #返回红线斜率，截距，LEN1,LEN2

########################################################

RED_THRESHOLD=(58, 9, 104, 17, 85, -92)
BLACK_THRESHOLD=(27, 0, -103, 47, 74, -112)



while(True):
    clock.tick()
    UART_DATA=[0]*7
    img = sensor.snapshot().lens_corr(strength = 1.7, zoom = 1)
    blobs=img.find_blobs([BLACK_THRESHOLD])      #先选出黑色色块，在黑色进行数字识别
    CX=[0,0]
    for blob in blobs:
        if blob.h()>70 and blob.h()<95 and blob.w()>10 and blob.w()<40 : #筛选色块的大小
            img.draw_rectangle(blob[0],blob[1],blob[2],blob[3])
            data=Blob_Pixel_Test(img,blob)  #计算特征点横纵坐标数据
            NUM=Get_Num(data)          #匹配得到数字
            img.draw_string(blob.x()+int(blob.w()/2), blob.y()-24, str(NUM),scale = 3, mono_space = False,color=(255,0,0))
            UART_DATA[UART_DATA[2]]=NUM
            if  UART_DATA[2]<2:
                CX[UART_DATA[2]]=blob.x()
            UART_DATA[2]+=1

    if CX[1]<CX[0] and CX[1]!=0:
         UART_DATA[1]= UART_DATA[0]
         UART_DATA[0]=NUM

    LINE_ERR=get_redline(img)
    UART_DATA[3]=LINE_ERR[0]
    UART_DATA[4]=LINE_ERR[1]
    UART_DATA[5]=LINE_ERR[2]
    UART_DATA[6]=LINE_ERR[3]
    real=[10000*UART_DATA[0]+1000*UART_DATA[1]+100*UART_DATA[2]+10*UART_DATA[5]+1*UART_DATA[6],UART_DATA[3],UART_DATA[4]]
    uart.write(sbz_format(real))
    #print(UART_DATA)
    print(real)

    img.draw_string(20, 20, str(UART_DATA[3])+"        "+str(UART_DATA[4]),scale = 1.8, mono_space = False,color=(0,0,255))
    img.draw_string(20, 120, " FPS: "+str(clock.fps()),scale = 1.8, mono_space = False,color=(0,255,0))
    lcd.display(img)
