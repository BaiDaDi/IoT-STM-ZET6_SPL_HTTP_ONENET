#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
 
#define	DHT11_GPIO       GPIOA
#define	DHT11_GPIO_RCC   RCC_APB2Periph_GPIOA
#define	DHT11_GPIO_Pin   GPIO_Pin_1

#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=8<<4;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=3<<4;}

#define	DHT11_DQ_OUT PAout(1) //数据端口	PA0 
#define	DHT11_DQ_IN  PAin(1)  //数据端口	PA0 


u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    
#endif
