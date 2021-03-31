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
   //dula=0;
   //wela=0;
   EN_CLR;
   LCD_Write_Com(0x38);    /*显示模式设置*/ 
   LCD_Write_Com(0x0e);    /*显示关闭*/ 
   LCD_Write_Com(0x06);    /*显示光标移动设置*/ 
   LCD_Write_Com(0x01);    /*显示清屏*/ 
   LCD_Write_Com(0x80);    /*显示开及光标设置*/
}

uchar buf, count;
bit   flag=0;
uchar data  RXDdata[] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
                          0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20 };
void main()
{
 
	SCON=0x50;           //设定串口工作方式
    PCON=0x00;           //波特率不倍增	
    TMOD=0x20;           //定时器1工作于8位自动重载模式, 用于产生波特率
    EA=1;
    ES = 1;              //允许串口中断
    TL1=0xfd;
    TH1=0xfd;             //波特率9600
    TR1=1;

    
	LCD_Init(); 
	LCD_Clear();//清屏
	LCD_Write_Char(1, 0, 'o');
	LCD_Write_Char(2, 0, 'k');
	LCD_Write_String(1,1,"hello world");


	while(1)
    {
         if(flag)
         {
             delay(10);
             //LCD_Write_Char(9, 0, buf);
             //LCD_Write_Char(10, 0, 0x37);
             LCD_Write_String(3, 0, RXDdata);
             flag = 0;
         }
         
    }
}

/*********************************************************

  串行中断服务函数

*********************************************************/
void  serial() interrupt 4 
{
   buf = SBUF;            //从串口缓冲区取得数据
   ES = 0;                //关闭串行中断
   RI = 0;                //清除串行接受标志位
   flag = 1;
   SBUF = buf;
   while(!TI);
   TI = 0;
   ES = 1;    //允许串口中断
   
   //P1=0x00;
   if(count<16)
   {         
     RXDdata[count]=buf;
     count++;
	 if(count==16)
	 	count=0;
   }
}