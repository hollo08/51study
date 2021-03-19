#include<reg52.h>

#define uchar unsigned char         
#define uint unsigned int
#define dula P0

sbit wela1 = P2^4;
sbit wela2 = P2^5;
sbit wela3 = P2^6;
sbit wela4 = P2^7;   


uchar code sz[17]={0x3f , 0x06 , 0x5b ,0x4f , 0x66 , 0x6d ,0x7d , 0x07 , 0x7f , 0x6f ,0x77 , 0x7c , 0x39 , 0x5e , 0x79 , 0x71 , 0x00};
uchar  tt, num;
void main()
{
    TMOD = 0x01;
    TH0 = (65535-50000)/256;
    TL0 = (65535-50000)%256;
    EA = 1;
    ET0 = 1;
    TR0 = 1;

    //EA = 1;
    //EX0 = 1;
    //IT0 = 1; or    TCON = 0x01;
    wela1 = 1;
    wela2 = 0;
    wela3 = 0;
    wela4 = 0;
    P0 = sz[0];
    while(1)
    {
        if(tt == 6)              //6*20ms
        {
            tt = 0;
            num ++;
            if(num==10)
            {
                num = 0;
            }
            dula = sz[num];
            wela1 = 1;
            wela2 = 0;
            wela3 = 0;
            wela4 = 0;
        }
        
    }
    
}
void timer1() interrupt 1
{
    TH0 = (65535-50000)/256;
    TL0 = (65535-50000)%256;
    tt++;
}