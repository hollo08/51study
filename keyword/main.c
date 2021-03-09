#include "reg52.h"
#define uchar unsigned char 

sbit led1 = P1^0;
sbit led2 = P1^1;
sbit led3 = P1^2;
sbit led4 = P1^3;
sbit led5 = P1^4;
sbit led6 = P1^5;
sbit led7 = P1^6;
sbit led8 = P1^7;

sbit key1 = P3^4;
sbit key2 = P3^5;
sbit key3 = P3^6;
sbit key4 = P3^7;

sbit beep = P2^3;

uchar num = 0;

/**
���ܣ�
���°�ť1ʱ1��3�������������°�ť1����ʱ����������
���°�ť2ʱ2��4������
���°�ť3ʱ5��7������
���°�ť4ʱ6��8����
**/
void delay(uchar i)
{
    uchar j, k;
    for(j=i; j>0; j--)
    {
        for(k=125; k>0; k--);
    }
}
void main()
{
    while(1)
    {
        if(key1==0)
        {
            delay(20);     //����
            if(key1==0)
            {
                while(!key1);
                num++;
            }
            switch(num)
            {
                case 1:
                    led1 = 0;
                    led3 = 0;
                    beep = 1;
                    break;
                case 2:
                    beep = 0;
                    led1 = 1;
                    led2 = 1;
                    num = 0;
                    break;
            }
        }
        if(key2==0)
        {
            led2 = 0;
            led4 = 0;
        } 
        else
        {
            P1 = 0xff;
        }
        if(key3==0)
        {
            led5 = 0;
            led7 = 0;
        }
        else
        {
            P1 = 0xff;
        }
        if(key4==0)
        {
            led6 = 0;
            led8 = 0;
        }
        else
        {
            P1 = 0xff;
        }
          
    }
    
}