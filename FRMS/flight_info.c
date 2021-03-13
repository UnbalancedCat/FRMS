#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<malloc.h>
#include"global.h"//自定义头文件
#include"output.h"//输出类头文件

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
						node->next = NULL;
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
	int i = 0;//定义循环变量
	flight* node;//定义普通节点
	node = head_flight;//初始化普通节点
	
	FRMS_title();//调用输出航班预定管理系统题头函数
	flight_info_title();//调用输出输出航班预定管理系统题头函数
	flight_info_subtitle();//调用输出航班时刻表分类栏函数

	printf("-----------------------------------------------------------------------------------------------------\n");
	while (node->next != NULL)
	{
		printf("|%02d|%20s|%20s|%12s|%7s|%8s|%8s|%8d|%6d|\n", ++i, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
		node = node->next;
	}
	printf("-----------------------------------------------------------------------------------------------------\n");
}

//排序航班信息



int main()
{
	get_flight_info();
	show_flight_info();


	return 0;
}