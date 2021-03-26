#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int

sbit RS = P1^0;   //定义端口 
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
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS 
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
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{  
 while(t--)
 {
     //大致延时1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
/*------------------------------------------------
              判忙函数
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
              写入命令函数
------------------------------------------------*/
 void LCD_Write_Com(unsigned char com) 
 {  
     //while(LCD_Check_Busy()); //忙则等待
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
    // while(LCD_Check_Busy()); //忙则等待
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
     DelayMs(5);
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
   
/*------------------------------------------------
                    主函数
------------------------------------------------*/ 
void main(void) 
{ 
LCD_Init(); 
LCD_Clear();//清屏
LCD_Write_Char(1, 0, 'o');
LCD_Write_Char(8,0,'k');
LCD_Write_String(1,1,"hello world");
while(1);
}