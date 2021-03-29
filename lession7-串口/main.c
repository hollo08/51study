#include <reg52.h>
#include <intrins.h>
	
#define uchar  unsigned char 
#define uint   unsigned int

sbit RS = P1^0;   //����˿� 
sbit RW = P1^1;
sbit EN = P2^5;	  //

sbit dula=P2^6;
sbit wela=P2^7;

#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1

#define DataPort P0

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

/*------------------------------------------------
              д�������
------------------------------------------------*/
 void LCD_Write_Com(unsigned char com) 
 {     
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
      delay(5);
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

uchar buf;
void main()
{
	LCD_Init(); 
	LCD_Clear();//����
	LCD_Write_Char(1, 0, 'o');
	LCD_Write_Char(8,0,'k');
//	LCD_Write_String(1,1,"hello world");
 
	SCON=0x50;           //�趨���ڹ�����ʽ
    PCON=0x00;           //�����ʲ�����	
    TMOD=0x20;           //��ʱ��1������8λ�Զ�����ģʽ, ���ڲ���������
    EA=1;
    ES = 1;              //�������ж�
    TL1=0xfd;
    TH1=0xfd;             //������9600
    TR1=1;
	while(1);
}

/*********************************************************

  �����жϷ�����

*********************************************************/
void  serial() interrupt 4 
{
   ES = 0;                //�رմ����ж�
   RI = 0;                //������н��ܱ�־λ
   buf = SBUF;            //�Ӵ��ڻ�����ȡ������
   switch(buf)
   {
      case 0x31:  
	  	P1=0xfe; 
		LCD_Write_Char(9, 0, 'x');
		break;  //���ܵ�1����һ��LED��         
      case 0x32:  
	  	P1=0xfd;
		break;  //���ܵ�2���ڶ���LED��        
      case 0x33:  P1=0xfb;LCD_Write_Char(9, 0, 'x');break;  //���ܵ�3��������LED��        
      case 0x34:  P1=0xf7;LCD_Write_Char(9, 0, 'x');break;  //���ܵ�4�����ĸ�LED��       
      case 0x35:  P1=0xef;LCD_Write_Char(9, 0, 'x');break;  //���ܵ�5�������LED��            
      case 0x36:  P1=0xdf;LCD_Write_Char(9, 0, 'x');break;  //���ܵ�5��������LED��                   
      case 0x37:  P1=0xbf;LCD_Write_Char(9, 0, 'x');break;  //���ܵ�5�����߸�LED��
	  case 0x38:  P1=0x7f;LCD_Write_Char(9, 0, 'x');break;  //���ܵ�5���ڰ˸�LED��
	  default:    P1=0xff;LCD_Write_Char(9, 0, 'x');break;  //���ܵ��������ݣ���������         
   }
   ES = 1;    //�������ж�
}