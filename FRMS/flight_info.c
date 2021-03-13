#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<malloc.h>
#include"global.h"//自定义头文件

//读取flight_info.txt航班信息
void get_flight_info(void)
{
	flight_info_num = 0;//初始化航班信息数量
	FILE* fp;//定义文件指针

	fp = fopen("flight_info.txt", "r");//打开flight_info.txt文件

	if (fp == NULL)printf("航班信息文件缺失！\a\n");//提示文件是否缺失				//仍需编辑
	else
	{
		flight * node;//定义普通节点
		node = (flight*)malloc(sizeof(flight));//分配空间
		head_flight = node;//保存头节点

		if (node == NULL)printf("内存分配失败！\a\n");//提示空间是否分配不足		//仍需编辑
		else
		{
			//第一次录入
			if (fscanf(fp, "%s %s %s %s %s %s %d %d", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)printf("文件读写失败！\a\n");//提示文件是否读写成功
			//剩余录入
			while (1)
			{
				flight_info_num++;//航班信息数量自增
				node->next = (flight*)malloc(sizeof(flight));//分配空间

				if (node->next == NULL)printf("内存分配失败！\a\n");//提示空间是否分配不足//仍需编辑
				else
				{
					end_flight = node;//保存尾节点
					node = node->next;//向下移动节点

					if (fscanf(fp, "%s %s %s %s %s %s %d %d", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)//读取一行数据保存在当前节点,并判断是否读写完毕
					{
						node = NULL;
						break;
					}				
				}
			}
			fclose(fp);//关闭文件
		}
	}
}

//显示航班信息
void show_flight_info(void)
{
	int i;//定义循环变量
	flight* node;//定义普通节点
	node = head_flight;//初始化普通节点
	
	FRMS_title();//调用输出航班预定管理系统题头函数
	flight_info_title();//调用输出输出航班预定管理系统题头函数

	printf("-----------------------------------------------------------------------------------------------------------\n");
	printf("|No|%23s|%23s|%12s|%7s|%8s|%8s|%8s|%6s|\n", "始发地", "目的地", "航空公司", "航班号", "起飞时间", "到达时间", "航班人数", "票价");
	printf("-----------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < flight_info_num; i++)
	{
		printf("|%02d|%23s|%23s|%12s|%7s|%8s|%8s|%8d|%6d|\n", i + 1, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
		node = node->next;
	}
	printf("-----------------------------------------------------------------------------------------------------------\n");
	//单行输出长度为108个字符长度
}

//排序航班信息



int main()
{
	get_flight_info();
	show_flight_info();
	return 0;
}