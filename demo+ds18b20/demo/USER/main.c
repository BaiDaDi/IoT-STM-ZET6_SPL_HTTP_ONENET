#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "usart3.h"
#include "esp8266.h"
#include "timer.h"
#include "dht11.h"
#include "lcd.h"
#include "adc.h"
#include "lsens.h"
#include "ds18b20.h"
#include "MQ2.h"
#include "dma.h"
//由于直插式DS18B20，故将DHT11数据口移动:由PG11-PB3


int main(void)
{
	u8 flag_DHT11 = 0;
    u8 tempValue = 0;
    u8 humidity = 0;
	short temperature;  
	u8 adcvalue_Lsens = 0;
	float adcvalue_MQ2 = 0;
	u16 lightvalue = 0;
	u16 ledctr = 0;
	u16 led0pwmval = 0;


    // 设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    delay_init();	   //延时函数初始化
    uart_init(115200); //串口初始化为115200
    
    
	// 初始化LED、LCD
    LED_Init();
	LCD_Init();	
	LCD_ShowString(30,50,200,16,16,(u8 *)"Information Collection");	
	LCD_ShowString(30,70,200,16,16,(u8 *)"       System         ");
	LCD_ShowString(30,110,200,16,16,(u8 *)"TeDS:   . C");
	LCD_ShowString(30,130,50,16,16,(u8 *)"Light:");
	LCD_ShowString(30,150,50,16,16,(u8 *)"TeDH:");		
	LCD_ShowString(30,170,50,16,16,(u8 *)"Humi:");
	LCD_ShowString(30,190,50,16,16,(u8 *)"PPM:");
	
	
	
	//初始化光敏电阻
	Lsens_Init();//此处会将Adc3_Init();	
	//Adc3_Init();	
	
	
	//TIM3_PWM_Init(1799,0);
	//TIM4_PWM_Init(999,71);
	
	
	//DS18B20初始化	
	while(DS18B20_Init())	
		{
			LCD_ShowString(30,230,200,16,16,(u8 *)"DS18B20 Error");
			delay_ms(200);
			LCD_Fill(30,230,239,170+16,WHITE);
			delay_ms(200);
		}	
	LCD_ShowString(30,230,200,16,16,(u8 *)"DS18B20 OK!");
	 
		
	
	//初始化dhtll
    flag_DHT11 = DHT11_Init();
	if(flag_DHT11 == 0)
	{
		LCD_ShowString(30,250,200,16,16,(u8 *)"DHT11 OK!");
	}
	else
	{
		LCD_ShowString(30,250,200,16,16,(u8 *)"DHT11 ERROR!");
	}
	
	
//    // 初始化ESP8266, 连接onenet, 进入透传模式
//    uart3_init(115200);
//	printf("Start 8266");delay_ms(500);
//    esp8266_start_trans();
//	LCD_ShowString(30,210,200,16,16,"8266 OK!");
		
    while (1)
    {
		delay_ms(3000);
		
		//DS18B20
		temperature=DS18B20_Get_Temp();	
		if(temperature<0)
		{
			LCD_ShowChar(30+40,110,'-',16,0);			//显示负号
			temperature=-temperature;					//转为正数
		}else LCD_ShowChar(30+40,110,' ',16,0);			//去掉负号
		LCD_ShowNum(30+40+8,110,temperature/10,2,16);	//显示正数部分	    
		LCD_ShowNum(30+40+32,110,temperature%10,1,16);	//显示小数部分 		
	
		//光敏电阻
		adcvalue_Lsens=Lsens_Get_Val();
		numToString(adcvalue_Lsens);
		printf("light: %s, ", strValue);	
		LCD_ShowString(100,130,200,16,16,(u8 *)strValue);	
//		esp8266_str_data("light", strValue);
		
		//DHT11
		DHT11_Read_Data(&tempValue,&humidity);	// 读取温湿度值
		numToString(tempValue);
		printf("tempValue: %s, ", strValue);
		LCD_ShowString(100,150,200,16,16,(u8 *)strValue);	
//         esp8266_str_data("temp", strValue);
		
		numToString(humidity);
		printf("humidity: %s\r\n\r\n", strValue);
		LCD_ShowString(100,170,200,16,16,(u8 *)strValue);	
 //      esp8266_str_data("humi", strValue);

		//MQ-2
//		ADC_Pin_Init();
//		
//		adcvalue_MQ2 = ADC_Trans();
		printf("ppm: %f\r\n",adcvalue_MQ2);
		numToString(adcvalue_MQ2);
		LCD_ShowString(100,190,200,16,16,(u8 *)strValue);	
//		esp8266_str_data("light", strValue);

		
	
	


/*		
		//通过get，从云上下传当前照度，低于40打开LED，反之关闭。实验验证成功
		lightvalue = esp8266_get_data("light");
		printf("lightvalue: %d, \r\n\r\n",lightvalue);
		if(lightvalue<40)
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);//LED1 = 0;
		else
			GPIO_SetBits(GPIOB,GPIO_Pin_5);//LED1 = 1;
*/


//			ledctr = esp8266_get_data("ledbtn");
//			if(ledctr == 1)
//			{
//				GPIO_ResetBits(GPIOB,GPIO_Pin_5);
//				//	LED1 = 0;LED0 = 0;
//			}
//			else if(ledctr == 0)
//			{
//				GPIO_SetBits(GPIOB,GPIO_Pin_5);
//				//LED1 = 1;LED0 = 1;
//			}


//						led0pwmval = esp8266_get_data("ledpwm");
//						TIM_SetCompare2(TIM3,led0pwmval);		 

	}
	
//			TIM_SetCompare3(TIM4,500);
//			delay_ms(100);
//			TIM_SetCompare3(TIM4,0);
//			delay_ms(100);

}
