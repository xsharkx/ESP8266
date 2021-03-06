/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2016 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "ets_sys.h"
#include "osapi.h"

#include "user_interface.h"
#include "driver/uart.h"
#include "gpio.h"
#include "eagle_soc.h"
#include "driver/delay.h"
#include "driver/led.h"
#include "driver/key.h"
#include "driver/HwTimer.h"
#include "osapi.h"
#include "mem.h"				// 内存申请等函数
#include "spi_flash.h"
#include "user_interface.h"
char TxBuff[] = "1234567890";
char Rxbuff[100];
/*
 * 在使用SPI Flash读写接口的时候有以下注意事项：
 * ①．我们使用的ESP8266模块为32Mbit，内存空间=4MB
 * ②．一个扇区(sector)为4KB，从扇区0开始计数
 * ③．Flash必须先对扇区擦除之后再进行写操作
 * ④．Flash读写必须以4个字节(4096bit)对齐
 * ⑤．程序区：代码编译生成的bin文件，不要写入其他数据
 * ⑥．系统参数区：用于存放系统参数的区域，不要写入其他数据
 * ⑦．读写数据的地址最好放在0x7 0000之后的地址
 * */

uint32 ICACHE_FLASH_ATTR user_rf_cal_sector_set(void)
{
    enum flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;

            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;

            break;

        case FLASH_SIZE_16M_MAP_512_512:
            rf_cal_sec = 512 - 5;

            break;
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;

            break;

        case FLASH_SIZE_32M_MAP_512_512:
            rf_cal_sec = 1024 - 5;

            break;
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;

            break;

        case FLASH_SIZE_64M_MAP_1024_1024:
            rf_cal_sec = 2048 - 5;

            break;

        case FLASH_SIZE_128M_MAP_1024_1024:
            rf_cal_sec = 4096 - 5;

            break;
        default:
            rf_cal_sec = 0;

            break;
    }

    return rf_cal_sec;
}

void ICACHE_FLASH_ATTR user_rf_pre_init(void){}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void ICACHE_FLASH_ATTR user_init(void)
{
	int i;
	os_DelayMs(1000);
	uart_init(115200,115200);//设置串口波特率
//	LedInitConfig();//LED灯初始化函数
//	KeyInitConfig();//按键初始化函数
//	KeyExtiInitConfig();//配置按键外部中断
//	TimerInitConfig(500,1);
//	hw_timer_set_func();
//	HwTimerInitConfig();
	os_printf("=============================================\r\n");
	os_printf("\t SDK version:\t%s", system_get_sdk_version());
	os_printf("\r\n嵌入式陈工个人编辑资料\r\n未经本人同意请勿私自传播\r\n");
	os_printf("\r\n外部Flash代码\r\n");
	os_printf("\r\n带看门狗\r\n");
	os_printf("\r\nSPI Flash 的 ID 号:%d\r\n",spi_flash_get_id());
	os_printf("=============================================\r\n");

	//1.擦除外部Flash
	spi_flash_erase_sector(0x80);//0x80为扇区编号
	//2.往扇区0x80写入数据   写入的数组必须强制数据类型转换
	spi_flash_write(0x80 * 4096,(uint32 *)TxBuff,sizeof(TxBuff));
	//3.读取扇区0x80的数据  读出的数组必须强制数据类型转换
	spi_flash_read(0x80 * 4096,(uint32 *)Rxbuff,100);
	os_printf("%s\r\n",Rxbuff);
//	for(i = 0; i < sizeof(TxBuff); i ++)
//	{
//		os_printf("Rxbuff[%d] = %d\r\n",i,Rxbuff[i]);
//	}
}



