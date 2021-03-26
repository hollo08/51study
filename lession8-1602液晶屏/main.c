#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int

sbit RS = P1^0;   //����˿� 
sbit RW = P1^1;
sbit EN = P2^5;



sbit dula=P2^6;
sbit wela=P2^7;

#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1

#define DataPort P0

/*------------------------------------------------
 uS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��,������ʱ
 �������� T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}


/*------------------------------------------------
 mS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��
------------------------------------------------*/
void DelayMs(unsigned char t)
{  
 while(t--)
 {
     //������ʱ1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
/*------------------------------------------------
              ��æ����
------------------------------------------------*/
 bit LCD_Check_Busy(void) 
 { 
 RS_CLR; 
 RW_SET; 
 EN_CLR; 
 delay(5); 
 EN_SET;
 return (bit)(DataPort & 0x80);//0x80;0x00
 }
/*------------------------------------------------
              д�������
------------------------------------------------*/
 void LCD_Write_Com(unsigned char com) 
 {  
     //while(LCD_Check_Busy()); //æ��ȴ�
     RS_CLR;
     DataPort= com; 
     delay(5); 
     EN_SET; 
     delay(5); 
     EN_CLR;
 }
/*------------------------------------------------
              д�����ݺ���
------------------------------------------------*/
 void LCD_Write_Data(unsigned char Data) 
 { 
    // while(LCD_Check_Busy()); //æ��ȴ�
     RS_SET;   
     DataPort= Data; 
     delay(5);
     EN_SET; 
     delay(5);
     EN_CLR;
 }

/*------------------------------------------------
                ��������
------------------------------------------------*/
 void LCD_Clear(void) 
 { 
     LCD_Write_Com(0x01); 
     DelayMs(5);
 }
/*------------------------------------------------
              д���ַ�������
------------------------------------------------*/
 void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
 {     
     if (y == 0) 
     {     
    	 LCD_Write_Com(0x80 + x);     //��ʾ��һ��
     }
     else 
     {      
     	LCD_Write_Com(0x80 + 0x40 + x);      //��ʾ�ڶ���
     }        
     while (*s) 
     {     
         LCD_Write_Data(*s);     
         s++;     
     }
 }
/*------------------------------------------------
              д���ַ�����
------------------------------------------------*/
 void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data) 
 {     
    if (y == 0)
    {     
        LCD_Write_Com(0x80 + x);     
    }    
    else 
    {     
        LCD_Write_Com(0x80 + 0x40 + x);     
    }        
    LCD_Write_Data( Data);  
 }
/*------------------------------------------------
              ��ʼ������
------------------------------------------------*/
 void LCD_Init(void) 
 {
   RW_CLR;
   dula=0;
   wela=0;
   EN_CLR;
   LCD_Write_Com(0x38);    /*��ʾģʽ����*/ 
   LCD_Write_Com(0x0e);    /*��ʾ�ر�*/ 
   LCD_Write_Com(0x06);    /*��ʾ����ƶ�����*/ 
   LCD_Write_Com(0x01);    /*��ʾ����*/ 
   LCD_Write_Com(0x80);    /*��ʾ�����������*/
}
   
/*------------------------------------------------
                    ������
------------------------------------------------*/ 
void main(void) 
{ 
LCD_Init(); 
LCD_Clear();//����
LCD_Write_Char(1, 0, 'o');
LCD_Write_Char(8,0,'k');
LCD_Write_String(1,1,"hello world");
while(1);
}