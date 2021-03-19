#include "reg52.h"
#include "intrins.h"

#define uint unsigned int
#define uchar unsigned char

sbit beep = P2^3;
void delay(uint i);
void main()
{
    P1 = 0xfe;
    while(1)
    {
        delay(5000);
        P1 = _crol_(P1, 1);
        delay(1000);
    }
}
void delay(uint i)
{
    uint k,j;
    for(k=i; k>0; k--)
        for(j=125; j<0; j--);
}