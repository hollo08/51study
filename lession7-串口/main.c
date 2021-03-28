#include <reg52.h>
#include <intrins.h>
	
#define uchar  unsigned char 
#define uint   unsigned int

sbit RS = P1^0;   //定义端口 
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
              写入命令函数
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
              写入数据函数
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
                清屏函数
------------------------------------------------*/
 void LCD_Clear(void) 
 { 
     LCD_Write_Com(0x01); 
      delay(5);
 }

/*------------------------------------------------
              写入字符串函数
------------------------------------------------*/
 void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
 {     
     if (y == 0) 
     {     
    	 LCD_Write_Com(0x80 + x);     //表示第一行
     }
     else 
     {      
     	LCD_Write_Com(0x80 + 0x40 + x);      //表示第二行
     }        
     while (*s) 
     {     
         LCD_Write_Data(*s);     
         s++;     
     }
 }
/*------------------------------------------------
              写入字符函数
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
              初始化函数
------------------------------------------------*/
 void LCD_Init(void) 
 {
   RW_CLR;
   dula=0;
   wela=0;
   EN_CLR;
   LCD_Write_Com(0x38);    /*显示模式设置*/ 
   LCD_Write_Com(0x0e);    /*显示关闭*/ 
   LCD_Write_Com(0x06);    /*显示光标移动设置*/ 
   LCD_Write_Com(0x01);    /*显示清屏*/ 
   LCD_Write_Com(0x80);    /*显示开及光标设置*/
}

uchar buf;
void main()
{
	LCD_Init(); 
	LCD_Clear();//清屏
	LCD_Write_Char(1, 0, 'o');
	LCD_Write_Char(8,0,'k');
//	LCD_Write_String(1,1,"hello world");
 
	SCON=0x50;           //设定串口工作方式
    PCON=0x00;           //波特率不倍增	
    TMOD=0x20;           //定时器1工作于8位自动重载模式, 用于产生波特率
    EA=1;
    ES = 1;              //允许串口中断
    TL1=0xfd;
    TH1=0xfd;             //波特率9600
    TR1=1;
	while(1);
}

/*********************************************************

  串行中断服务函数

*********************************************************/
void  serial() interrupt 4 
{
   ES = 0;                //关闭串行中断
   RI = 0;                //清除串行接受标志位
   buf = SBUF;            //从串口缓冲区取得数据
   switch(buf)
   {
      case 0x31:  
	  	P1=0xfe; 
		LCD_Write_Char(9, 0, 'x');
		break;  //接受到1，第一个LED亮         
      case 0x32:  
	  	P1=0xfd;
		break;  //接受到2，第二个LED亮        
      case 0x33:  P1=0xfb;LCD_Write_Char(9, 0, 'x');break;  //接受到3，第三个LED亮        
      case 0x34:  P1=0xf7;LCD_Write_Char(9, 0, 'x');break;  //接受到4，第四个LED亮       
      case 0x35:  P1=0xef;LCD_Write_Char(9, 0, 'x');break;  //接受到5，第五个LED亮            
      case 0x36:  P1=0xdf;LCD_Write_Char(9, 0, 'x');break;  //接受到5，第六个LED亮                   
      case 0x37:  P1=0xbf;LCD_Write_Char(9, 0, 'x');break;  //接受到5，第七个LED亮
	  case 0x38:  P1=0x7f;LCD_Write_Char(9, 0, 'x');break;  //接受到5，第八个LED亮
	  default:    P1=0xff;LCD_Write_Char(9, 0, 'x');break;  //接受到其它数据，蜂鸣器响         
   }
   ES = 1;    //允许串口中断
}