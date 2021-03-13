#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
			if (fscanf(fp, "%s %s %s %s %s %s %s %s", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)printf("文件读写失败！\a\n");//提示文件是否读写成功
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

					if (fscanf(fp, "%s %s %s %s %s %s %s %s", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price) != 8)//读取一行数据保存在当前节点,并判断是否读写完毕
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
		printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", ++i, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
		node = node->next;
	}
	printf("-----------------------------------------------------------------------------------------------------\n");
}

/*
while ((std_in = getchar()) != EOF && std_in != '\n');//清空因非法输入而产生的输入区缓存
*/

//排序航班信息（单关键字）
void sort_flight_info(char option)
{
	int offset;//定义偏移量
	int i, j;//定义循环变量，用于排序

	switch(option)
	{
	case 'A':offset = 0; break;
	case 'B':offset = 32; break;
	case 'C':offset = 64; break;
	case 'D':offset = 80; break;
	case 'E':offset = 88; break;
	case 'F':offset = 96; break;
	case 'G':offset = 104; break;
	case 'H':offset = 112; break;
	default: printf("错误指令,请重新输入\n\a"); return;
	}


	flight* node, * buffer;//定义普通节点、缓存节点

	for (i = 0; i < flight_info_num-1; i++)
	{
		node = head_flight;//初始化普通节点
		for (j = 0; j < flight_info_num - 1 - i; j++)
		{
			
			buffer = node;//初始化缓存节点
			if (strcmp(node->start_place + offset, node->next->start_place + offset) == 1)
			{
				node = node->next;
				buffer->next = node->next;
				node->next = buffer;
				if (j == 0)head_flight = node;
			}
			node = node->next;
		}
	}
}


int main()
{
	get_flight_info();
	show_flight_info();
	/*flight* node;
	node = head_flight;
	while (node->next != NULL)
	{
		printf("%s ", node->start_place + 0);
		printf("%s ", node->start_place + 32);
		printf("%s ", node->start_place + 64);
		printf("%s ", node->start_place + 80);
		printf("%s ", node->start_place + 88);
		printf("%s ", node->start_place + 96);
		printf("%s ", node->start_place + 104);
		printf("%s\n", node->start_place + 112);
		node = node->next;
	}*/

	sort_flight_info('H');
	show_flight_info();
	return 0;
}