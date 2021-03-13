#pragma once
#ifndef _GLOBAL_H
#define _GLOBAL_H

//输出航班时刻表题头
void flight_info_title(void)
{
	printf("-----------------------------------------------------------------------------------------------------------\n");
	printf("                                               航 班 时 刻 表\n");
}

//输出航班预定管理系统题头
void FRMS_title(void)
{
	printf("-----------------------------------------------------------------------------------------------------------\n\n");
	printf("                  航        班        预        定        管        理        系        统\n\n");
}

//航班信息结构体
typedef struct flight_info
{

	char start_place[32];	//起飞地
	char end_place[32];		//目的地
	char company[16];		//航空公司
	char flight_num[8];		//航班号
	char start_time[8];		//起飞时间
	char end_time[8];		//到达时间
	int people_num;			//人数
	int price;				//价格

	struct flight_info* next;	//保存下一个地址

}flight;//实际测试占用116字节

//全局变量头节点和尾节点
flight* head_flight, * end_flight;

//全局变量航班信息数量
int flight_info_num;

#endif
