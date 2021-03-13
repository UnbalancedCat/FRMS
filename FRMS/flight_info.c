#include<stdio.h>
#include<malloc.h>
#include<malloc.h>

typedef struct flight_info//航班信息结构体
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


void get_flight_info(void)//读取flight_info.txt航班信息
{
	FILE* fp;//定义文件指针
	fp = fopen("flight_info.txt", "r");//打开flight_info.txt文件
	if (fp == NULL)printf("航班信息缺失！\n");//提示文件是否缺失
	else{
		flight* head, * node, * end;//定义结构体头节点、普通节点、尾节点
		node = (flight*)malloc(sizeof(flight));//分配空间
		head = node;//保存首节点
		if (node == NULL)printf("内存分配不足！\n");//提示空间是否分配不足
		else{
			if (fscanf(fp, "%s %s %s %s %s %s %d %d",  node->start_place, node->start_time, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)printf("数据读写错误！\n");//读取一行数据保存在当前节点，并提示是否数据读写错误
			else{
			
			}
		}
	}
}

