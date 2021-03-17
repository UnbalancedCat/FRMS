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
	char people_num[6];			//人数
	char price[6];				//价格
	//变量部分大小112

	struct flight_info* next_global;	//保存整体的链表下一个成员的地址
	struct flight_info* next_part;		//保存查询后链表下一个成员的地址

	//实际测试大小120个字节
}flight;

//全局变量全局头节点和部分头节点
flight* head_flight_global, * head_flight_part;

flight* secret;

//全局变量航班信息数量
int flight_info_num,search_flight_info_num;







#endif
