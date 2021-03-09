#include "reg52.h"
#include "intrins.h"

#define uint unsigned int
#define uchar unsigned char

sbit led1 = P1^0;
sbit led2 = P1^1;
sbit led3 = P1^2;
sbit led4 = P1^3;
sbit led5 = P1^4;
sbit led6 = P1^5;
sbit led7 = P1^6;
sbit led8 = P1^7;

void delay(uint i)
{
    uint k,j;
    for(k=i; k>0; k--)
        for(j=251; j<0; j--);
}

//uchar temp = 0x1;
int m;
void main()
{
    for(m=3; m>0; m--)
    {
       led1 = 0;
       led3 = 0;
       led5 = 0;
       led7 = 0;
       led2 = 1;
       led4 = 1;
       led6 = 1;
       led8 = 1;
       delay(30000);
       led2 = 0;
       led4 = 0;
       led6 = 0;
       led8 = 0;
       led1 = 1;
       led3 = 1;
       led5 = 1;
       led7 = 1;
       delay(30000);
    }
    P1 = 0xff;
    delay(500000);
    
    for(m=3; m>0; m--)
    {
       P1 = 0x7e;
       delay(30000);
       P1 = 0xbd;
       delay(30000);
       P1 = 0xdb;
       delay(30000);
       P1 = 0xe7;
       delay(30000);
    }
    P1 = 0xff;
    delay(500000);
    
    for(m=3; m>0; m--)
    {
       P1 = 0xe7;
       delay(30000);
       P1 = 0xdb;
       delay(30000);
       P1 = 0xbd;
       delay(30000);
       P1 = 0x7e;
       delay(30000);
    }
    P1 = 0xff;
    delay(500000);
    for(m=3; m>0; m--)
    {
       P1 = 0x00;
       delay(30000);
       P1 = 0xff;
       delay(30000);
    }
    P1 = 0xff;
    delay(10000000);
}