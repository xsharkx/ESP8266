/*
 * timer.c
 *
 *  Created on: 2018年8月14日
 *      Author: 小良哥
 */

#include "driver/delay.h"
#include "driver/led.h"
#include "driver/key.h"
#include "driver/uart.h"
#include "driver/timer.h"
#include "driver/dht11.h"

/*
 * 函数名称：void TimerInitConfig(uint32_t DelayMs,bool repeat_flag)
 * 函数功能：定时器初始化函数
 * 函数形参：
 *       uint32_t DelayMs   延时时间
 *       bool repeat_flag   是否重复
 *       		1：重复   0：不重复
 * 返回值：
 * */
os_timer_t os_timer_500ms;//定义一个定时器名称
void TimerInitConfig(uint32_t DelayMs,bool repeat_flag)
{
	os_timer_disarm(&os_timer_500ms);//关闭定时器
	os_timer_setfn(&os_timer_500ms,(os_timer_func_t *)TimerBackFunction,NULL);//设置定时器回调函数
	os_timer_arm (&os_timer_500ms, DelayMs, repeat_flag);
}

/*
 * 函数名称：void TimerBackFunction(void)
 * 函数功能：定时器回调函数
 * 函数形参：无
 * 返回值：   无
 * */
void TimerBackFunction(void)
{
	//返回ADC测量的数值
	os_printf("ADC检测数值=%u\r\n", system_adc_read());
	//计算出ADC数值对应的电压值
	os_printf("实际电压=0.");
	os_printf("%u\r\n", system_adc_read()*100/1024);
}

