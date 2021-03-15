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

	fp = fopen("flight_info.test", "r");//打开flight_info.txt文件

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

//排序航班信息（单关键字）
flight* sort_flight_info(char direction, int option_num, char* option_info, int loop_num, flight* head)//需要关键字字符数组首地址，排序链表成员个数，排序链表首地址 返回排序后首地址
{
	int offset;//用于描述成员占用长度或总偏移量
	int i, j;//定义循环变量
	_Bool bool;
	flight* node, * buffer, * lag;//定义普通节点、缓存节点、滞后节点	

	//一级关键字
	switch (*option_info)
	{
	case 'A':offset = 0; break;
	case 'B':offset = 32; break;
	case 'C':offset = 64; break;
	case 'D':offset = 80; break;
	case 'E':offset = 88; break;
	case 'F':offset = 96; break;
	case 'G': break;
	case 'H': break;
	default: printf("错误指令,请重新输入\n\a"); return head;
	}

	for (i = 0; i < loop_num - 1; i++)
	{
		node = head;//初始化普通节点
		lag = head;//初始化滞后节点
		for (j = 0; j < loop_num - 1 - i; j++)
		{
			buffer = node;//初始化缓存节点

			if (*option_info == 'G' || *option_info == 'H')
			{
				if (*option_info == 'G')bool = (node->people_num > node->next->people_num);
				if (*option_info == 'H')bool = (node->price > node->next->price);
			}
			else
			{
				bool = (strcmp(node->start_place + offset, node->next->start_place + offset) == 1);
			}


			if (bool)
				//node->people_num > node->next->people_num
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
	
	//二级关键字
	if (option_num != 1)
	{
		flight* head_next, * buffer_next;//定义传递给嵌套函数的链表首地址
		int loop_num_next;//定义传递给嵌套函数的链表成员个数
		j = 0;

		node = head;
		buffer_next = head;
		while (node->next != NULL)
		{
			
			loop_num_next = 1;
			head_next = buffer_next;
			node = head_next;
			buffer = head_next;
			while (node->next != NULL)
			{
				if (*option_info == 'G' || *option_info == 'H')
				{
					if (*option_info == 'G')bool = (node->people_num == node->next->people_num);
					if (*option_info == 'H')bool = (node->price == node->next->price);
				}
				else
				{
					bool = (strcmp(node->start_place + offset, node->next->start_place + offset) == 0);
				}

				if (bool)//前后成员元素比对相同，继续比对
				{
					node = node->next;
					loop_num_next += 1;
				}
				else//前后成员元素对比不同，记录，开始二级关键字排序,链接链表，结束初次循环
				{
					buffer_next = node->next;
					if (loop_num_next != 1)
					{
						buffer = sort_flight_info(direction, option_num - 1, option_info + 1, loop_num_next, head_next);
						if (j == 0)
						{
							head = buffer;
							j += 1;
						}
						while (--loop_num_next)
						{
							buffer = buffer->next;
						}
						buffer->next = buffer_next;
					}
					break;
				}
			}

		}
	}
	
	
	return head;
}












//测试用主函数
int main()
{
	char option[9] = { 'F','H' };
	int option_num = 2;
	char direction = 'A';//未启用
	int i = 1;

	get_flight_info();
	show_flight_info();

	//用于测试排序函数
	while (i--)
	{
		
		printf("##排序之前##\n");
		
		head_flight = sort_flight_info(direction, option_num, option, flight_info_num, head_flight);
		
		
		printf("##排序之后##\n");
		printf("##排序关键字:%s##\n", option);

		show_flight_info();
	}
	
	printf("##Done##\n");

	return 0;
}