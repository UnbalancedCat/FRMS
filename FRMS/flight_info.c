#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"global.h"//自定义头文件
#include"output.h"//输出类头文件

//读取文件函数
void pull_flight_info(void)
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
		head_flight_global = node;//保存头节点

		if (node == NULL)
		{
			printf("内存分配失败！\a\n");//提示空间是否分配不足
			return;//中止函数
		}
		else
		{
			//第一次录入
			if (fscanf(fp, "%s %s %s %s %s %s %s %s", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price) != 8)
			{
				printf("文件读写失败！\a\n");//提示文件是否读写成功
				return;//中止函数
			}
			//剩余录入
			while (1)
			{
				flight_info_num++;//航班信息数量自增
				node->next_global = (flight*)malloc(sizeof(flight));//分配空间
				node->next_part = node->next_global;
				if (node->next_global == NULL)
				{
					printf("内存分配失败！\a\n");//提示空间是否分配不足
					return;//中止函数
				}
				else
				{
					node = node->next_global;//向下移动节点

					if (fscanf(fp, "%s %s %s %s %s %s %s %s", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price) != 8)//读取一行数据保存在当前节点,并判断是否读写完毕
					{
						{	//初始化无用空间
							strcpy(node->start_place, "Airport muggle can not found");
							strcpy(node->end_place, "Airport can not be landed at");
							strcpy(node->company, "Hogwarts Co.");
							strcpy(node->flight_num, "HE5972");
							strcpy(node->start_time, "notoday");
							strcpy(node->end_time, "anytime");
							strcpy(node->people_num, "0");
							strcpy(node->price, "0");
							node->next_global = NULL;
							node->next_part = NULL;
							secret = node;
						}
						break;
					}				
				}
			}
			fclose(fp);//关闭文件
		}
	}
}

//保存文件函数
void push_flight_info(void)
{
	flight* node = head_flight_global;
	FILE* fp;//定义文件指针
	fp = fopen("flight_info.output", "w");//打开并覆盖清楚flight_info.txt文件内容
	if (fp == NULL)
	{
		printf("文件输出错误！\a\n");//提示fopen是否成功返回指针
		return;
	}
	else
	{
		while (node->next_global != NULL)
		{
			fprintf(fp, "%s %s %s %s %s %s %s %s\n", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			node = node->next_global;
		}
	}
	fclose(fp);
}

//显示航班信息函数
void show_flight_info(flight* head)//需要 显示的链表的首地址
{
	int i = 0;//定义循环变量
	flight* node = head;//定义并初始化普通节点

	FRMS_title();//调用输出航班预定管理系统题头函数
	flight_info_title();//调用输出输出航班预定管理系统题头函数
	flight_info_subtitle();//调用输出航班时刻表分类栏函数

	printf("-----------------------------------------------------------------------------------------------------\n");
	if (head != head_flight_part && head == head_flight_global)
	{
		while (node->next_global != NULL)
		{
			printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", ++i, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			node = node->next_global;
		}
	}
	else
	{
		while (node->next_part != NULL)
		{
			printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", ++i, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			node = node->next_part;
		}
	}
	printf("-----------------------------------------------------------------------------------------------------\n");
}

//多关键字排序函数
flight* sort_flight_info(char direction, int option_num, char* option_info, int loop_num, flight* head)
//需要 顺序倒叙标识字符 关键字个数 关键字数组首地址 排序的航班信息数量 排序的航班信息首地址 || 返回 排序后首地址
{
	int offset;//用于描述成员占用长度或总偏移量
	int i, j;//定义循环变量
	_Bool bool, bool_direction;

	flight* node, * buffer, * lag;//定义普通节点、缓存节点、滞后节点	

	//判断排序顺序
	switch (direction)
	{
	case 'A': bool_direction = 1; break;
	case 'B': bool_direction = 0; break;
	default : bool_direction = 1;
	}

	//判断关键字
	switch (*option_info)
	{
	case 'A':offset = 0; break;
	case 'B':offset = 32; break;
	case 'C':offset = 64; break;
	case 'D':offset = 80; break;
	case 'E':offset = 88; break;
	case 'F':offset = 96; break;
	case 'G':offset = 104; break;
	case 'H':offset = 110; break;
	default: printf("传递参数错误，排序关键字错误\n\a"); return head;
	}

	//一级关键字
	for (i = 0; i < loop_num - 1; i++)
	{
		node = head;//初始化普通节点
		lag = head;//初始化滞后节点
		for (j = 0; j < loop_num - 1 - i; j++)
		{
			buffer = node;//初始化缓存节点

			if (*option_info == 'G' || *option_info == 'H')
			{
				bool = ((strtol((node->start_place + offset), NULL, 10) > strtol((node->next_global->start_place + offset), NULL, 10) == bool_direction));
			}
			else
			{
				bool = ((strcmp(node->start_place + offset, node->next_global->start_place + offset) == 1) == bool_direction);
			}


			if (bool)
			{
				node = node->next_global;
				buffer->next_global = node->next_global;
				node->next_global = buffer;
				if (j == 0)
				{
					head = node;
					lag = head;//初始化滞后节点
				}
				else
				{
					lag->next_global = node;
				}
			}
			if (j != 0)lag = lag->next_global;
			node = node->next_global;

		}
	}
	
	//二级关键字
	if (option_num != 1)
	{
		flight* head_next, * buffer_next, * lag;//定义传递给嵌套函数的链表首地址等
		int loop_num_next;//定义传递给嵌套函数的链表成员个数
		j = 0;

		node = head;
		buffer_next = head;
		lag = NULL;
		while (node->next_global != NULL)
		{
			
			loop_num_next = 1;
			head_next = buffer_next;
			node = head_next;
			buffer = head_next;
			while (node->next_global != NULL)
			{
				if (*option_info == 'G' || *option_info == 'H')
				{
					bool = ((strtol((node->start_place + offset), NULL, 10) > strtol((node->next_global->start_place + offset), NULL, 10) == bool_direction));
				}
				else
				{
					bool = ((strcmp(node->start_place + offset, node->next_global->start_place + offset) == 1) == bool_direction);
				}

				if (bool)//前后成员元素比对相同，继续比对
				{
					node = node->next_global;
					loop_num_next += 1;
				}
				else//前后成员元素对比不同，记录，开始二级关键字排序,链接链表，结束初次循环
				{
					buffer_next = node->next_global;
					if (loop_num_next != 1)
					{
						buffer = sort_flight_info(direction, option_num - 1, option_info + 1, loop_num_next, head_next);
						if (j == 0)
						{
							head = buffer;
							j += 1;
						}
						else
						{
							lag->next_global = buffer;
						}
						while (--loop_num_next)
						{
							buffer = buffer->next_global;
						}
						
						buffer->next_global = buffer_next;
					}
					lag = buffer;
					break;
				}
			}

		}
	}
	return head;
}

//多关键字查询函数(单关键字已实现)
flight* refer_flight_info(int option_num, char* option_info, char* refer_info, flight* head)//需要 关键词个数 关键词首地址 被查询链表首地址 || 返回 查询后新链表首地址
{
	int j = 0;
	int offset;//定义偏移量
	flight* node, * buffer;//定义普通节点、缓冲节点

	node = head;
	buffer = head;
	if (strlen(option_info) == 0 || *refer_info == '\n')
	{
		printf("未检测到字符！\n");
		return NULL;
	}
	switch (*option_info)
	{
	case 'A':offset = 0; break;
	case 'B':offset = 32; break;
	case 'C':offset = 64; break;
	case 'D':offset = 80; break;
	case 'E':offset = 88; break;
	case 'F':offset = 96; break;
	case 'G':offset = 104; break;
	case 'H':offset = 110; break;
	default: printf("传递参数错误，查询关键字错误\n\a"); return NULL;
	}

	if (head != head_flight_part && head == head_flight_global)
	{
		while (node->next_global != NULL)
		{

			if (strstr((node->start_place + offset), refer_info) != NULL)
			{
				if (j == 0)
				{
					buffer = node;
					head = buffer;
					j += 1;
				}
				else
				{
					buffer->next_part = node;
					buffer = buffer->next_part;
				}
			}
			node = node->next_global;
		}
		buffer->next_part = NULL;
	}
	else
	{
		while (node->next_part != NULL)
		{

			if (strstr((node->start_place + offset), refer_info) != NULL)
			{
				if (j == 0)
				{
					buffer = node;
					head = buffer;
					j += 1;
				}
				else
				{
					buffer->next_part = node;
					buffer = buffer->next_part;
				}
			}
			node = node->next_part;
		}
		buffer->next_part = secret;
	}
	return head;
}















//测试用主函数
int main()
{
	char option_sort[9] = { 'A','B','F','B','C','E','H','D' };
	char refer_info[32] = { "上海" };
	int option_num = 1;
	char direction = 'B';

	//music();//careful!

	//测试函数
	{
		printf("读取数据...\n");
		pull_flight_info();
		printf("数据读写成功\n\n");
		system("pause");

		printf("输出数据...\n");
		show_flight_info(head_flight_global);
		printf("数据输出成功\n\n");
		system("pause");

		printf("查询数据...\n");
		head_flight_part = refer_flight_info(option_num, option_sort, refer_info, head_flight_global);
		printf("查询关键字:%s\n", option_sort);
		printf("数据查询成功\n\n");
		system("pause");

		printf("输出数据...\n");
		show_flight_info(head_flight_part);
		printf("数据输出成功\n\n");
		system("pause");

		//printf("排序数据...\n");
		//head_flight_global = sort_flight_info(direction, option_num, option_sort, flight_info_num, head_flight_global);
		//printf("排序关键字:%s\n", option);
		//printf("数据排序成功\n\n");
		

		//printf("输出数据...\n");
		//show_flight_info(head_flight_global);
		//printf("数据输出成功\n\n");

		//printf("保存数据...\n");
		//push_flight_info();
		//printf("数据保存成功\n\n");
	}


	printf("Done\n");

	return 0;
}