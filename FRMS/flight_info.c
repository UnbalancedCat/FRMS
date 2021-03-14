#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include"global.h"//自定义头文件
#include"output.h"//输出类头文件

//读取flight_info.txt航班信息
void get_flight_info(void)
{
	flight_info_num = 0;//初始化航班信息数量
	FILE* fp;//定义文件指针

	fp = fopen("flight_info.txt", "r");//打开flight_info.txt文件

	if (fp == NULL)
	{
		printf("航班信息文件缺失！\a\n");//提示文件是否缺失
		return;
	}
	else
	{
		flight * node;//定义普通节点
		node = (flight*)malloc(sizeof(flight));//分配空间
		head_flight = node;//保存头节点

		if (node == NULL)
		{
			printf("内存分配失败！\a\n");//提示空间是否分配不足
			return;//中止函数
		}
		else
		{
			//第一次录入
			if (fscanf(fp, "%s %s %s %s %s %s %d %d", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)
			{
				printf("文件读写失败！\a\n");//提示文件是否读写成功
				return;//中止函数
			}
			//剩余录入
			while (1)
			{
				flight_info_num++;//航班信息数量自增
				node->next = (flight*)malloc(sizeof(flight));//分配空间

				if (node->next == NULL)
				{
					printf("内存分配失败！\a\n");//提示空间是否分配不足
					return;//中止函数
				}
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
		printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6d|%6d|\n", ++i, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
		node = node->next;
	}
	printf("-----------------------------------------------------------------------------------------------------\n");
}

/*
while ((std_in = getchar()) != EOF && std_in != '\n');//清空因非法输入而产生的输入区缓存
*/

//排序航班信息（单关键字）//目前对数字不行！其他可以
flight* sort_flight_info(char option_info, flight* head)//需要传递关键字，排序链表首地址 返回排序后首地址
{
	int offset;//用于描述成员占用长度或总偏移量
	int i, j;//定义循环变量
	flight* node, * buffer, * lag;//定义普通节点、缓存节点、滞后节点	

	if (option_info == 'G' || option_info == 'H')
	{
		if (option_info == 'G')
		{
			for (i = 0; i < flight_info_num - 1; i++)
			{
				node = head;//初始化普通节点
				lag = head;//初始化滞后节点
				for (j = 0; j < flight_info_num - 1 - i; j++)
				{
					buffer = node;//初始化缓存节点
					if (node->people_num > node->next->people_num)
					{
						node = node->next;
						buffer->next = node->next;
						node->next = buffer;
						if (j == 0)
						{
							head = node;
							lag = head;//初始化滞后节点
						}
						else
						{
							lag->next = node;
						}
					}
					if (j != 0)lag = lag->next;
					node = node->next;
				}
			}
		}
		if (option_info == 'H')
		{
			for (i = 0; i < flight_info_num - 1; i++)
			{
				node = head;//初始化普通节点
				lag = head;//初始化滞后节点
				for (j = 0; j < flight_info_num - 1 - i; j++)
				{
					buffer = node;//初始化缓存节点
					if (node->price > node->next->price)
					{
						node = node->next;
						buffer->next = node->next;
						node->next = buffer;
						if (j == 0)
						{
							head = node;
							lag = head;//初始化滞后节点
						}
						else
						{
							lag->next = node;
						}
					}
					if (j != 0)lag = lag->next;
					node = node->next;
				}
			}
		}
	}
	else
	{
		switch (option_info)
		{
		case 'A':offset = 0; break;
		case 'B':offset = 32; break;
		case 'C':offset = 64; break;
		case 'D':offset = 80; break;
		case 'E':offset = 88; break;
		case 'F':offset = 96; break;
		default: printf("错误指令,请重新输入\n\a"); return head;
		}

		for (i = 0; i < flight_info_num - 1; i++)
		{
			node = head;//初始化普通节点
			lag = head;//初始化滞后节点
			for (j = 0; j < flight_info_num - 1 - i; j++)
			{
				buffer = node;//初始化缓存节点
				if (strcmp(node->start_place + offset, node->next->start_place + offset) == 1)
				{
					node = node->next;
					buffer->next = node->next;
					node->next = buffer;
					if (j == 0)
					{
						head = node;
						lag = head;//初始化滞后节点
					}
					else
					{
						lag->next = node;
					}
				}
				if (j != 0)lag = lag->next;
				node = node->next;
			}
		}
	}


	return head;
}

//测试用主函数
#define KEYWORD 'H'
#include<Windows.h>	
int main()
{
	char option;

	get_flight_info();
	show_flight_info();

	//用于测试排序函数
	while (1)
	{
		printf("请输入对应序号排序：");
		
		option = getchar();
		getchar();
		if (option == 'q')break;
		
		printf("##排序之前##\n");
		
		head_flight = sort_flight_info(option, head_flight);
		
		
		printf("##排序之后##\n");
		printf("##排序关键字:%c##\n", option);

		show_flight_info();
	}
	
	
	printf("##Done##\n");

	return 0;
}