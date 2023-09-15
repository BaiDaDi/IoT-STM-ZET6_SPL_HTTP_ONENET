#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
 
#define	DHT11_GPIO       GPIOA
#define	DHT11_GPIO_RCC   RCC_APB2Periph_GPIOA
#define	DHT11_GPIO_Pin   GPIO_Pin_1

#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=8<<4;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=3<<4;}

#define	DHT11_DQ_OUT PAout(1) //���ݶ˿�	PA0 
#define	DHT11_DQ_IN  PAin(1)  //���ݶ˿�	PA0 


u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
#endif