#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"global.h"
#include"flight_info.h"
//初始化
void init(void)
{
	pull_flight_info();//读取航班信息;
	read_passenger();
}
//读取文件函数
void pull_flight_info(void)
{
	flight_info_num = 0;//初始化航班信息数量
	FILE* fp;//定义文件指针

	fp = fopen("data\\flight_info.txt", "r");//打开flight_info.txt文件

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
							secret = node;//保存最后成员的地址
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
	fp = fopen("data\\flight_info.output", "w");//打开并覆盖清楚flight_info.txt文件内容
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
	system("cls");
	int i = 0;//定义循环变量
	flight* node = head;//定义并初始化普通节点

	show_FRMS_title();//调用输出航班预定管理系统题头函数
	show_flight_info_title();//调用输出输出航班预定管理系统题头函数
	show_flight_info_subtitle();//调用输出航班时刻表分类栏函数

	line();
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
		if (head == NULL)
		{
			printf("                                      没 有 符 合 条 件 的 信 息\n");
		}
		else
		{
			while (node->next_part != NULL)
			{
				printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", ++i, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
				node = node->next_part;
			}
		}
	}
	line();
}
//多关键字排序函数
flight* sort_flight_info(char direction, int option_num, char* option_info, int loop_num, flight* head)
//需要 顺序倒叙标识字符 关键字对象个数 关键字对象数组首地址 排序的航班信息数量 排序的航班信息首地址 || 返回 排序后首地址
{
	int offset;//用于描述成员占用长度或总偏移量
	int i, j;//定义循环变量
	_Bool bool, bool_direction;

	flight* node, * buffer, * lag;//定义普通节点、缓存节点、滞后节点	

	//判断排序顺序
	switch (direction)
	{
	case 'D': bool_direction = 1; break;
	case 'U': bool_direction = 0; break;
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
				bool = ((strtol((node->start_place + offset), NULL, 10) > strtol((node->next_global->start_place + offset), NULL, 10)) == bool_direction);
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
//衔接排序函数
void bridge_sort_flight_info()
{
	int i = 8;
	char direction[4] = { 0 };//顺序
	char option_info[10] = { 0 };//存储关键字
	int option_num = 0;//关键字个数

	//处理排序标识符输入
	printf("请选择排序顺序（D：顺序，U：倒叙）：");
	{
		rewind(stdin);
		fgets(direction, 3, stdin);	
		rewind(stdin);
		if ('\n' == direction[strlen(direction) - 1]) direction[strlen(direction) - 1] = 0;
	}
	while (direction[1]!='\0'||(direction[0]!='D' && direction[0] !='U'))
	{
		printf("含有非法字符，请重新输入！\a\n");
		printf("请选择排序顺序（D：顺序，U：倒叙）：");
		{
			rewind(stdin);
			fgets(direction, 3, stdin);	
			rewind(stdin);
			if ('\n' == direction[strlen(direction) - 1]) direction[strlen(direction) - 1] = 0;
		}
	}
	//处理排序关键字输入
	printf("请选择排序关键字序号（如：ABH ）：");
	{
		rewind(stdin);
		fgets(option_info, 10, stdin);
		rewind(stdin);
		if ('\n' == option_info[strlen(option_info) - 1]) option_info[strlen(option_info) - 1] = 0;
	}
	i = (int)strlen(option_info);
	while (i)
	{
		if (option_info[9] != '\0' || (option_info[i - 1] < 'A' || option_info[i - 1] > 'H'))
		{
			printf("含有非法字符，请重新输入！\a\n");
			printf("请选择排序关键字序号（如：ABH ）：");
			{
				memset(option_info, 0, sizeof(option_info));
				rewind(stdin);
				fgets(option_info, 10, stdin);
				rewind(stdin);
				if ('\n' == option_info[strlen(option_info) - 1]) option_info[strlen(option_info) - 1] = 0;
			}
			i = (int)strlen(option_info);
		}
		else i--;
	}
	//处理排序关键字个数
	option_num = (int)strlen(option_info);
	
	
	head_flight_global = sort_flight_info(direction[0], option_num, option_info, flight_info_num, head_flight_global);
	show_flight_info(head_flight_global);
	return;
}
//多关键字精确查询函数（对数字查询为模糊查询）
void refine_search_flight_info(int option_num, char* option_info, char refer_info[][32], flight* head)//需要 关键字个数 关键字对象数组首地址 提供关键字首地址 被查询链表首地址
{
	search_flight_info_num = 0;
	int j = 0;
	int offset;//定义偏移量
	flight* node, * buffer;//定义普通节点、缓冲节点

	node = head;
	buffer = head;

	if (strlen(option_info) == 0 || refer_info[0][0] == '\n')
	{
		printf("未检测到字符！\n\a");
		return;
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
	default: printf("传递参数错误，查询关键字错误\n\a"); return;
	}

	//一级关键字
	if (head != head_flight_part && head == head_flight_global)//获取的首地址为全局链表地址
	{
		while (node->next_global != NULL)
		{

			if (strstr((node->start_place + offset), refer_info[0]) != NULL)
			{
				search_flight_info_num++;
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
		buffer->next_part = secret;
	}
	else//获取的首地址为查询链表地址
	{
		while (node->next_part != NULL)
		{
			if (strstr((node->start_place + offset), refer_info[0]) != NULL)
			{
				search_flight_info_num++;
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

	head_flight_part = head ;

	//二级关键字
	if (option_num != 1)
	{
		refine_search_flight_info(option_num - 1, option_info + 1, refer_info + 1, head);
	}
	else if (search_flight_info_num == 0)head_flight_part = NULL;
}
//衔接查询函数
void bridge_refine_search_sort_flight_info()
{
	int i = 0;//处理关键字个数
	int j = 0;
	char refer_info[8][32] = { 0 };//储存对应关键字查询
	char option_info[10] = { 0 };//存储关键字
	int option_num = 0;//关键字个数
	char buffer[32] = { 0 };//缓冲数组

	//do
	//{
		i = 8;
		while (i)
		{
			printf("请选择查询关键词以及查询数据,输入0完成（如：A上海）：");
			{
				rewind(stdin);
				fgets(buffer, 23, stdin);
				rewind(stdin);
				if ('\n' == buffer[strlen(buffer) - 1]) buffer[strlen(buffer) - 1] = 0;
			}
			if (buffer[0] == '0' && buffer[1] == '\0')break;
			while (buffer[21] != '\0' || (buffer[0] < 'A' || buffer[0] > 'H'))
			{
				printf("含有非法字符，请重新输入！\a\n");
				printf("请选择查询关键词以及查询数据,输入0完成（如：A上海）：");
				{
					rewind(stdin);
					fgets(buffer, 23, stdin);
					rewind(stdin);
					if ('\n' == buffer[strlen(buffer) - 1]) buffer[strlen(buffer) - 1] = 0;
				}
			}
			if (buffer[0] == '0' && buffer[1] == '\0')break;
			option_info[8 - i] = buffer[0];
			strcpy(refer_info[8 - i], buffer + 1);
			i--;
		}
	//} while (refer_info[8 - i][0]!='\0');
		option_num = 8 - i;
	refine_search_flight_info(option_num, option_info, refer_info, head_flight_global);
	show_flight_info(head_flight_part);
	system("pause");
	return;
}
//添加航班信息函数
void add_flight_info(void)
{
	char* endptr = NULL;
	flight* temporary = (flight*)malloc(sizeof(flight));
	if (temporary == NULL)
	{
		printf("申请空间失败\a\n");
		return;
	}
	else
	{
		flight* node;
		node = secret;

		{
			line();
			printf("|字符数限制长度：\n");
			printf("|A:20   B:20   C:12   D:7   E:7   F:7   G:5   H:5\n");
			line();
			printf("|请输入新添加的对应信息：\n");
			printf("|A   始    发    地："); if (gets_s(temporary->start_place, 21) == NULL) { printf("未检测到字符\a\n"); return; }
			printf("|B   目    的    地："); if (gets_s(temporary->end_place, 21) == NULL) { printf("未检测到字符\a\n"); return; }
			printf("|C   航  空  公  司："); if (gets_s(temporary->company, 13) == NULL) { printf("未检测到字符\a\n"); return; }
			printf("|D   航    班    号："); if (gets_s(temporary->flight_num, 8) == NULL) { printf("未检测到字符\a\n"); return; }
			printf("|E   起  飞  时  间："); if (gets_s(temporary->start_time, 8) == NULL) { printf("未检测到字符\a\n"); return; }
			printf("|F   到  达  时  间："); if (gets_s(temporary->end_time, 8) == NULL) { printf("未检测到字符\a\n"); return; }
			printf("|G   载          客："); if (gets_s(temporary->people_num, 6) == NULL ) { printf("未检测到字符\a\n"); return; }
			printf("|H   价          格："); if (gets_s(temporary->price, 6) == NULL ) { printf("未检测到字符\a\n"); return; }
			line();
		}

		{
			strcpy(node->start_place, temporary->start_place);
			strcpy(node->end_place, temporary->end_place);
			strcpy(node->company, temporary->company);
			strcpy(node->flight_num, temporary->flight_num);
			strcpy(node->start_time, temporary->start_time);
			strcpy(node->end_time, temporary->end_time);
			strcpy(node->people_num, temporary->people_num);
			strcpy(node->price, temporary->price);
			node->next_global = NULL;
			node->next_part = NULL;
		}

		node->next_global = (flight*)malloc(sizeof(flight));
		if (node->next_global == NULL)
		{
			printf("空间申请失败！\a\n");
			return;
		}
		else
		{
			flight_info_num++;
			node->next_part = node->next_global;
			{
				printf("添加成功\n");
				line();
				printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", flight_info_num, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
				line();
			}
			node = node->next_global;

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
			secret = node;//保存最后成员的地址
		}
	}
}
//修改航班信息函数
void modify_flight_info(void)
{
	int i;
	flight* node;
	char located_flight_info[32];


	system("cls");
	show_flight_info(head_flight_global);

	printf("请选择要修改的航班信息对应序号（字符限制：2）：");
	if (gets_s(located_flight_info,3) == NULL) { printf("未检测到字符\a\n"); return; }
	if (strtol(located_flight_info, NULL, 10) <= 0 || strtol(located_flight_info, NULL, 10) > flight_info_num){printf("输入数据越界\a\n"); return; }
	else
	{
		int max = strtol(located_flight_info, NULL, 10);
		node = head_flight_global;
		int offset, limmit;
		for (i = 0; i < max - 1; i++)node = node->next_global;
		{
			system("cls");
			show_FRMS_title();
			show_flight_info_subtitle();
			line();
			printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", max, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			line();
		}
		printf("请选择要修改的航班信息对应代码：");
		if (gets_s(located_flight_info, 3) == NULL) { printf("未检测到字符\a\n"); return; }
		switch (located_flight_info[0])
		{
		case 'A':offset = 0, limmit = 21; break;
		case 'B':offset = 32, limmit = 21; break;
		case 'C':offset = 64, limmit = 13; break;
		case 'D':offset = 80, limmit = 8; break;
		case 'E':offset = 88, limmit = 8; break;
		case 'F':offset = 96, limmit = 8; break;
		case 'G':offset = 104, limmit = 6; break;
		case 'H':offset = 110, limmit = 6; break;
		default: printf("传递参数错误，关键字错误\n\a"); return;
		}
		{
			line();
			printf("|字符数限制长度：\n");
			printf("|A:20   B:20   C:12   D:7   E:7   F:7   G:5   H:5\n");
			line();
			printf("%s -> ", node->start_place + offset);
			gets_s(node->start_place + offset, limmit);
			printf("修改成功\n");
			line();
			printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", max, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			line();
		}
	}
}
//删除航班信息函数
void delete_flight_info(void)
{
	int i;
	flight* node, * buffer;
	char located_flight_info[5];


	system("cls");
	show_flight_info(head_flight_global);

	printf("请选择要删除的航班信息对应序号（字符限制：2）：");
	if (gets_s(located_flight_info, 3) == NULL) { printf("未检测到字符\a\n"); return; }
	if (strtol(located_flight_info, NULL, 10) <= 0 || strtol(located_flight_info, NULL, 10) > flight_info_num) { printf("输入数据越界\a\n"); return; }
	else
	{
		int max = strtol(located_flight_info, NULL, 10);
		node = head_flight_global;
		buffer = node;
		if (max != 1)
		{
			for (i = 0; i < max - 1; i++)
			{
				buffer = node;
				node = node->next_global;
			}
			{
				system("cls");
				show_FRMS_title();
				show_flight_info_subtitle();
				line();
				printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", max, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
				line();
			}
			printf("请确认是否删除这条航班信息（y or n）：");
			if (gets_s(located_flight_info, 3) == NULL) { printf("未检测到字符\a\n"); return; }
			if (located_flight_info[0] == 'y')
			{
				buffer->next_global = node->next_global;
				buffer->next_part = node->next_part;
				flight_info_num--;
				if (node->next_part != NULL)head_flight_part--;
				free(node);
				printf("删除成功\n");
			}
			else printf("未进行删除操作\n");
		}
		else
		{
			system("cls");
			show_FRMS_title();
			show_flight_info_subtitle();
			line();
			printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", max, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			line();
			printf("请确认是否删除这条航班信息（y or n）：");
			if (gets_s(located_flight_info, 3) == NULL) { printf("未检测到字符\a\n"); return; }
			if (located_flight_info[0] == 'y')
			{
				head_flight_global = node->next_global;
				head_flight_part = node->next_part;
				flight_info_num--;
				if (node->next_part != NULL)head_flight_part--;
				free(node);
				printf("删除成功\n");
			}
			else printf("未进行删除操作\n");
		}
	}
}
//订票函数
void reserve_flight_ticket(void)
{


	show_flight_info(head_flight_global);
	printf("请选择预定航班对应序号：");

}
//输出长横线
void line(void)
{
	printf("-----------------------------------------------------------------------------------------------------\n");
}
//输出航班时刻表题头
void show_flight_info_title(void)
{
	line();
	printf("                                            航 班 时 刻 表\n");
}
//输出航班预定管理系统题头
void show_FRMS_title(void)
{
	line();
	printf("\n                      航      班      预      定      管      理      系      统\n\n");
}
//输出航班时刻表分类栏
void show_flight_info_subtitle(void)
{
	line();
	printf("|  |%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", "A始发地", "B目的地", "C航空公司", "D航班号", "E起飞时间", "F到达时间", "G载客", "H票价");
}
//输出管理员标题
void show_manager_title(void)
{
	line();
	printf("                                            管 理 员 模 式\n");
}

#include <Windows.h>
#pragma comment(lib,"Winmm.lib")
//function plays music
void play_music(void)
{
	char* point;
	int i = 0;
	char q = 'a';
	char no_use = '\n';
	char sentence[] = "Loading Knock Me Out. . .\nEnter q to stop the music and start the rael project         ;)\nPlease enter a letter:\0";
	char sentence_reload[] = "Reloading Knock Me Out...\nWhy don't you LISTEN TO ME to continue!?                     :(\nEnter q!:\0";
	while (q != 'q')
	{
		if (i == 0)
		{
			point = sentence;
			i++;
		}
		else point = sentence_reload;


		PlaySound(TEXT("Knock Me Out.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

		while (*point != '\0')
		{
			printf("%c", *point);
			if (*point == '\n')Sleep(1500);
			else Sleep(100);
			point++;
		}

		q = getchar();
		no_use = getchar();
		system("cls");
	}

	exit(0);
}

//测试用主函数
//int main()
//{
//	int i = 0;;
//	//char option_sort[9] = { 'B','A','C','D','E','F','G','B' };
//	char option_sort[9] = { 'A','H','C','B'};
//	char refer_info[8][32] = { "上海","2","大韩" ,"MI"};
//	int option_num = 3;
//	char direction = 'A';
//
//	//music();//careful!
//
//	//测试函数
//	{
//		printf("读取全局数据...\n");
//		pull_flight_info();
//		printf("数据读写成功\n\n");
//
//		printf("输出全局数据...\n");
//		show_flight_info(head_flight_global);
//		printf("数据输出成功\n\n");
//
//		modify_flight_info();
//
//		delete_flight_info();
//
//		printf("查询数据...\n");
//		refine_search_flight_info(option_num, option_sort, refer_info, head_flight_global);
//		printf("查询关键字:%s\n", option_sort);
//		printf("查询关键词:");
//		while(refer_info[i][0]!='\0')
//		{
//			printf("%s ", refer_info[i]);
//			i++;
//		}
//		printf("\n");
//		printf("数据查询成功\n\n");
//		system("pause");
//
//		printf("输出查询数据...\n");
//		show_flight_info(head_flight_part);
//		printf("数据输出成功\n\n");
//		system("pause");
//
//		printf("排序全局数据...\n");
//		head_flight_global = sort_flight_info(direction, option_num, option_sort, flight_info_num, head_flight_global);
//		printf("排序关键字:%s\n", option_sort);
//		printf("数据排序成功\n\n");
//
//
//		printf("添加全局数据...\n");
//		add_flight_info();
//		printf("数据添加成功\n\n");
//		system("pause");
//		
//
//		printf("输出全局数据...\n");
//		show_flight_info(head_flight_global);
//		printf("数据输出成功\n\n");
//		system("pause");
//
//		printf("保存全局数据...\n");
//		push_flight_info();
//		printf("数据保存成功\n\n");
//		system("pause");
//
//	}
//
//
//	printf("Done\n");
//
//	return 0;
//}