# IoT-STM-ZET6_HTTP_ONENET
一种使用标准库架构的STM32F103ZET6通过ESP8266模块以HTTP协议连接ONENET的解决方案    

采集：光敏电阻、DS18B20、DHT11并显示在LCD上
云平台可以下传控制点亮板载LED灯。

优点：发送AT指令到ESP是通过应答判断而不是延时，程序架构更科学
缺点：使用HTTP协议
