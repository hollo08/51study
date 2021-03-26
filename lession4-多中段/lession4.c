#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char         
#define uint unsigned int
#define dula P0

uchar code sz[17]={0x3f , 0x06 , 0x5b ,0x4f , 0x66 , 0x6d ,0x7d , 0x07 , 0x7f , 0x6f ,0x77 , 0x7c , 0x39 , 0x5e , 0x79 , 0x71 , 0x00};

sbit wela1 = P2^4;
sbit wela2 = P2^5;
sbit wela3 = P2^6;
sbit wela4 = P2^7; 

sbit beep = P2^3;

sbit btn1 = P3^4;
sbit btn2 = P3^5;
sbit btn3 = P3^6;
sbit btn4 = P3^7;

uint tt, t2, num, qian, bai, shi, ge, beep_flag;
uint temp;
uint btn1_flag, btn2_flag, btn3_flag, btn4_flag;
void delay(unsigned int xms);
void getNum(uint num);


void init()
{
    temp = 0xfe;
    P1 = temp;
    TMOD = 0x11;            //定时器工作模式
    TH0 = (65535-50000)/256;
    TL0 = (65535-50000)%256;
    TH1 = (65535-50000)/256;
    TL1 = (65535-50000)%256;
    EA = 1;     //开启中断
    ET0 = 1;    //定时器T0中断, 用于数码管   
    ET1 = 1;    //定时器T1中断, 用于跑马灯
    TR0 = 1;    //定时器T0启动 
    TR1 = 1;    //定时器T1启动
}

void timer1() interrupt 1
{
    TH0 = (65535-50000)/256;
    TL0 = (65535-50000)%256;
    tt++;
    if(tt==2)
    {
        tt = 0;
        /**
        if(btn1_flag==1)
        {
            return;
        }
        **/
        num++;
        if(num==10000)
            num = 0;
        if(num==999)//等于999时，定时器停止
        {
            //TR0 = 0;
            beep_flag = 1;
            //TR1 = 0;
        }
        if(beep_flag==1 && num%20==0)
        {
            //num = 1;
            beep = 0;
        }
        else
        {
            beep = 1;
        }
        getNum(num);
    }
}

void led0() interrupt 3
{
    TH1 = (65535-50000)/256;
    TL1 = (65535-50000)%256;
    t2++;
    
    if(t2==10)
    {
        t2=0;
        temp = _crol_(P1, 1);
        P1 = temp;
    }
}

void display(uint qian, uint bai, uint shi, uint ge)
{
    dula = sz[qian];
    wela1 = 1;
    wela2 = 0;
    wela3 = 0;
    wela4 = 0;
    delay(5);
    dula = sz[bai];
    wela1 = 0;
    wela2 = 1;
    wela3 = 0;
    wela4 = 0;
    delay(5);
    dula = sz[shi];
    wela1 = 0;
    wela2 = 0;
    wela3 = 1;
    wela4 = 0;
    delay(5);
    dula = sz[ge];
    wela1 = 0;
    wela2 = 0;
    wela3 = 0;
    wela4 = 1;
    delay(5);
}

void delay(unsigned int xms)				
{
	unsigned int i,j;
	for(i=xms;i>0;i--)		      //i=xms即延时约xms毫秒
		for(j=110;j>0;j--);
}

void getNum(uint num)
{
    qian = num/1000;
    bai = num/100%10;
    shi = num/10%10;
    ge = num%10;
}



void main()
{
    init();
    
    while(1)
    {
        display(qian, bai, shi, ge);
           
        if(btn1==0)
        {
           delay(10);		 //消抖
           if(btn1==0)
           {
                TR0 = 0;
                //while(!btn1)
                //    display(qian, bai, shi, ge);
                
                btn1_flag = 1;
                //TR0 = 1;
           }
           
        }
        if(btn2==0)
        {
            delay(10);
            if(btn2==0)
            {
                //while(!btn1)
                //    display(qian, bai, shi, ge);
                btn1_flag = 0;
                TR0 = 1;
            }
        }
        if(btn3==0)
        {
            delay(10);
            if(btn3==0)
            {
                num = 0;
                TR0 = 1;
                delay(20);
                TR0 = 0;
            }
        }
    }
}