#pragma once
#ifndef GLOBAL_H_
#define GLOBAL_H_

//航班信息结构体
typedef struct flight_info
{

	char start_place[32];	//起飞地
	char end_place[32];		//目的地
	char company[16];		//航空公司
	char flight_num[8];		//航班号
	char start_time[8];		//起飞时间
	char end_time[8];		//到达时间
	char people_num[8];			//人数
	char price[6];				//价格

	struct flight_info* next;	//保存下一个地址

}flight;//实际测试大小124个字节

//全局变量头节点和尾节点
flight* head_flight, * end_flight;

//全局变量航班信息数量
int flight_info_num;

#endif
