#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "usmart.h"
#include "rtc.h"

#include "digital_led.h"

/************************************************
 ALIENTEK ̽����STM32F407������ ʵ��15
 RTCʵ��-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

void DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
    POINT_COLOR = color;
    LCD_DrawLine(x1,y1,x2,y2);
}

int main(void)
{
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;
    u8 tbuf[40];
    u8 t=0;
    
    uint8_t widget = 12;

    HAL_Init();                   	//��ʼ��HAL��
    Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz
    delay_init(168);               	//��ʼ����ʱ����
    uart_init(115200);             	//��ʼ��USART
    LED_Init();						//��ʼ��LED
    LCD_Init();           			//��ʼ��LCD
    usmart_dev.init(84); 		    //��ʼ��USMART
    RTC_Init();                     //��ʼ��RTC
    RTC_Set_WakeUp(RTC_WAKEUPCLOCK_CK_SPRE_16BITS,0); //����WAKE UP�ж�,1�����ж�һ��
    POINT_COLOR = RED;
    BACK_COLOR = BLACK;
    LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");
    LCD_ShowString(30,70,200,16,16,"RTC TEST");
    LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
    LCD_ShowString(30,110,200,16,16,"2017/4/11");

    draw_str.Digital_Draw_Line = DrawLine;
    for(;;)
    {
        draw_str.Auto_Size_Scal = 5;
        draw_str.Draw_Pen_Size = 2;
        Digital_Draw_num(0  ,320,widget,60,120,RTC_TimeStruct.Hours/10,PARA_FILL_MAIN|PARA_AUTO_SIZE);
        Digital_Draw_num(80 ,320,widget,60,120,(RTC_TimeStruct.Hours%10)|0x10,PARA_FILL_MAIN|PARA_AUTO_SIZE|PARA_SHOW_POINT);
        Digital_Draw_num(160,320,widget,60,120,RTC_TimeStruct.Minutes/10,PARA_FILL_MAIN|PARA_AUTO_SIZE);
        Digital_Draw_num(240,320,widget,60,120,(RTC_TimeStruct.Minutes%10)|0x10,PARA_FILL_MAIN|PARA_AUTO_SIZE|PARA_SHOW_POINT);
        Digital_Draw_num(320,320,widget,60,120,RTC_TimeStruct.Seconds/10,PARA_FILL_MAIN|PARA_AUTO_SIZE);
        Digital_Draw_num(400,320,widget,60,120,RTC_TimeStruct.Seconds%10,PARA_FILL_MAIN|PARA_AUTO_SIZE);
        
        delay_ms(100);
        HAL_RTC_GetTime(&RTC_Handler,&RTC_TimeStruct,RTC_FORMAT_BIN);
        delay_ms(100);
        HAL_RTC_GetDate(&RTC_Handler,&RTC_DateStruct,RTC_FORMAT_BIN);
        POINT_COLOR = WHITE;
        sprintf((char*)tbuf,"Time:%02d:%02d:%02d",RTC_TimeStruct.Hours,RTC_TimeStruct.Minutes,RTC_TimeStruct.Seconds);
        LCD_ShowString(30,140,210,16,16,tbuf);
        sprintf((char*)tbuf,"Date:20%02d-%02d-%02d",RTC_DateStruct.Year,RTC_DateStruct.Month,RTC_DateStruct.Date);
        LCD_ShowString(30,160,210,16,16,tbuf);
        sprintf((char*)tbuf,"Week:%d",RTC_DateStruct.WeekDay);
        LCD_ShowString(30,180,210,16,16,tbuf);
    }
    
    while(1)
    {
        t++;
        if((t%10)==0)	//ÿ100ms����һ����ʾ����
        {
            POINT_COLOR = WHITE;
            HAL_RTC_GetTime(&RTC_Handler,&RTC_TimeStruct,RTC_FORMAT_BIN);
            sprintf((char*)tbuf,"Time:%02d:%02d:%02d",RTC_TimeStruct.Hours,RTC_TimeStruct.Minutes,RTC_TimeStruct.Seconds);
            LCD_ShowString(30,140,210,16,16,tbuf);
            HAL_RTC_GetDate(&RTC_Handler,&RTC_DateStruct,RTC_FORMAT_BIN);
            sprintf((char*)tbuf,"Date:20%02d-%02d-%02d",RTC_DateStruct.Year,RTC_DateStruct.Month,RTC_DateStruct.Date);
            LCD_ShowString(30,160,210,16,16,tbuf);
            sprintf((char*)tbuf,"Week:%d",RTC_DateStruct.WeekDay);
            LCD_ShowString(30,180,210,16,16,tbuf);
        }
        if((t%20)==0)LED0=!LED0;	//ÿ200ms,��תһ��LED0
        delay_ms(10);
    }
}

