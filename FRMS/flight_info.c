#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"global.h"
//程序启动时读取文件,以及启动界面
void init(void)
{
	pull_flight_info();//读取航班信息;
	pull_passenger_info();

	full_screen();
	line();
	printf("\n\n\n                                                                   欢      迎      使      用\n\n\n");
	printf("                                                   航      班      预      定      管      理      系      统\n\n\n\n");
	line();
	printf("                             |");
	system("pause");
	system("cls");
}
//程序关闭时保存并自动备份文件，以及退出界面
void shut_down(void)
{
	push_flight_info();
	push_passenger_info();
	menu_file_backup_auto();

	system("cls");
	line();
	printf("\n\n\n                                                                  退      出      成      功\n\n\n");
	printf("                                                          欢      迎      再      次      使      用\n\n\n\n");
	line();
	printf("                             |");
	system("pause");
}
//读取文件函数
void pull_flight_info(void)
{
	flight_info_num = 0;//初始化航班信息数量
	FILE* fp;//定义文件指针

	fp = fopen("data\\flight_info.txt", "r");//打开flight_info.txt文件

	if (fp == NULL)
	{
		printf("                             |航班信息文件缺失！\a\n");//提示文件是否缺失
		return;
	}
	else
	{
		flight * node;//定义普通节点
		node = (flight*)malloc(sizeof(flight));//分配空间
		head_flight_global = node;//保存头节点

		if (node == NULL)
		{
			printf("                             |内存分配失败！\a\n");//提示空间是否分配不足
			return;//中止函数
		}
		else
		{
			//第一次录入
			if (fscanf(fp, "%s %s %s %s %s %s %s %s", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price) != 8)
			{
				printf("                             |文件读写失败！\a\n");//提示文件是否读写成功
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
					printf("                             |内存分配失败！\a\n");//提示空间是否分配不足
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
							secret_flight_info = node;//保存最后成员的地址
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
	int i = 0;//定义循环变量
	flight* node = head;//定义并初始化普通节点

	show_flight_info_subtitle();//调用输出航班时刻表分类栏函数

	line();
	if (head != head_flight_part && head == head_flight_global)
	{
		while (node->next_global != NULL)
		{
			printf("                             |%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", ++i, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			node = node->next_global;
		}
	}
	else
	{
		if (head == NULL)
		{
			printf("                                                                   没 有 符 合 条 件 的 信 息\n");
		}
		else
		{
			while (node->next_part != NULL)
			{
				printf("                             |%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", ++i, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
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
	default: printf("                             |传递参数错误，排序关键字错误\n\a"); return head;
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
void bridge_sort_flight_info(void)
{
	int i = 8;
	char direction[4] = { 0 };
	direction[0] = 'D';//顺序
	char option_info[10] = { 0 };//存储关键字
	int option_num = 0;//关键字个数

	//处理排序标识符输入
	show_FRMS_title();
	line();
	printf("                             |键入c取消输入，返回上级菜单!\n");
	/*printf("                             |请选择排序顺序（D：顺序，U：倒叙）：");
	{
		rewind(stdin);
		fgets(direction, 3, stdin);	
		rewind(stdin);
		if ('\n' == direction[strlen(direction) - 1]) direction[strlen(direction) - 1] = 0;
	}
	if (direction[0] == 'c' && direction[1] == '\0')
	{
		line();
		printf("                             |取消成功！\n");
		printf("                             |");
		system("pause");
		system("cls");
		return;
	}
	while (direction[1]!='\0'||(direction[0]!='D' && direction[0] !='U'))
	{
		printf("                             |含有非法字符，请重新输入！\a\n");
		printf("                             |请选择排序顺序（D：顺序，U：倒叙）：");
		{
			rewind(stdin);
			fgets(direction, 3, stdin);	
			rewind(stdin);
			if ('\n' == direction[strlen(direction) - 1]) direction[strlen(direction) - 1] = 0;
		}
		if (direction[0] == 'c' && direction[1] == '\0')
		{
			line();
			printf("                             |取消成功！\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
	}*/
	//处理排序关键字输入
	printf("                             |请选择排序关键字序号（如：ABH ）：");
	{
		rewind(stdin);
		fgets(option_info, 10, stdin);
		rewind(stdin);
		if ('\n' == option_info[strlen(option_info) - 1]) option_info[strlen(option_info) - 1] = 0;
	}
	if (option_info[0] == 'c' && option_info[1] == '\0')
	{
		line();
		printf("                             |取消成功！\n");
		printf("                             |");
		system("pause");
		system("cls");
		return;
	}
	i = (int)strlen(option_info);
	while (i)
	{
		if (option_info[9] != '\0' || (option_info[i - 1] < 'A' || option_info[i - 1] > 'H'))
		{
			printf("                             |含有非法字符，请重新输入！\a\n");
			printf("                             |请选择排序关键字序号（如：ABH ）：");
			{
				memset(option_info, 0, sizeof(option_info));
				rewind(stdin);
				fgets(option_info, 10, stdin);
				rewind(stdin);
				if ('\n' == option_info[strlen(option_info) - 1]) option_info[strlen(option_info) - 1] = 0;
			}
			if (option_info[0] == 'c' && option_info[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			i = (int)strlen(option_info);
		}
		else i--;
	}
	//处理排序关键字个数
	option_num = (int)strlen(option_info);
	head_flight_global = sort_flight_info(direction[0], option_num, option_info, flight_info_num, head_flight_global);
	show_flight_info_title();
	show_flight_info(head_flight_global);
	printf("                             |排序成功！\n");
	printf("                             |");
	system("pause");
	system("cls");
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
		printf("                             |未检测到字符！\n\a");
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
	default: printf("                             |传递参数错误，查询关键字错误\n\a"); return;
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
		buffer->next_part = secret_flight_info;
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
		buffer->next_part = secret_flight_info;
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
void bridge_refine_search_sort_flight_info(void)
{
	int i = 0;//处理关键字个数
	int j = 0;
	char refer_info[8][32] = { 0 };//储存对应关键字查询
	char option_info[10] = { 0 };//存储关键字
	int option_num = 0;//关键字个数
	char buffer[32] = { 0 };//缓冲数组
	while (1)
	{
		i = 8;
		show_FRMS_title();
		line();
		printf("                             |关键词个数上限为8个，键入f完成输入；键入c取消输入，返回上级菜单！\n");
		line();
		while (i)
		{
			printf("                             |请选择查询关键词以及查询数据（如：A上海）：");
			{
				rewind(stdin);
				fgets(buffer, 23, stdin);
				rewind(stdin);
				if ('\n' == buffer[strlen(buffer) - 1]) buffer[strlen(buffer) - 1] = 0;
			}
			if (buffer[0] == 'f' && buffer[1] == '\0')break;
			if (buffer[0] == 'c' && buffer[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			while (buffer[21] != '\0' || (buffer[0] < 'A' || buffer[0] > 'H'))
			{
				printf("                             |含有非法字符！\a\n");
				printf("                             |请选择查询关键词以及查询数据（如：A上海）：");
				{
					rewind(stdin);
					fgets(buffer, 23, stdin);
					rewind(stdin);
					if ('\n' == buffer[strlen(buffer) - 1]) buffer[strlen(buffer) - 1] = 0;
				}
				if (buffer[0] == 'f' && buffer[1] == '\0')break;
				if (buffer[0] == 'c' && buffer[1] == '\0')
				{
					line();
					printf("                             |取消成功！\n");
					printf("                             |");
					system("pause");
					system("cls");
					return;
				}
			}
			if (buffer[0] == 'f' && buffer[1] == '\0')break;
			option_info[8 - i] = buffer[0];
			strcpy(refer_info[8 - i], buffer + 1);
			i--;
		}
		if (refer_info[0][0] != '\0')break;
		else
		{
			line();
			printf("                             |未接收到查询数据！请重新输入！\a\n");
			printf("                             |");
			system("pause");
			system("cls");
		}
	}
	option_num = 8 - i;
	refine_search_flight_info(option_num, option_info, refer_info, head_flight_global);
	system("cls");
	show_FRMS_title();//调用输出航班预定管理系统题头函数
	show_flight_info_title();//调用输出输出航班预定管理系统题头函数
	show_flight_info(head_flight_part);
	printf("                             |");
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
		printf("                             |申请空间失败\a\n");
		return;
	}
	else
	{
		flight* node;
		node = secret_flight_info;

		{
			show_FRMS_title();
			show_manager_title();
			line();
			printf("                             |字符数限制长度：\n");
			printf("                             |A:20   B:20   C:12   D:7   E:7   F:7   G:5   H:5\n");
			line();
			printf("                             |键入c取消录入，返回上级菜单!\n");
			printf("                             |请输入新添加的对应信息\n");
			printf("                             |A   始    发    地：");
			{
				rewind(stdin);
				fgets(temporary->start_place, 21, stdin);
				rewind(stdin);
				if ('\n' == temporary->start_place[strlen(temporary->start_place) - 1]) temporary->start_place[strlen(temporary->start_place) - 1] = 0;
			}
			while (temporary->start_place[0]=='\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |A   始    发    地：");
				{
					memset(temporary->start_place, 0, sizeof(temporary->start_place));
					rewind(stdin);
					fgets(temporary->start_place, 21, stdin);
					rewind(stdin);
					if ('\n' == temporary->start_place[strlen(temporary->start_place) - 1]) temporary->start_place[strlen(temporary->start_place) - 1] = 0;
				}
			}
			if (temporary->start_place[0] == 'c' && temporary->start_place[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			printf("                             |B   目    的    地：");
			{
				rewind(stdin);
				fgets(temporary->end_place, 21, stdin);
				rewind(stdin);
				if ('\n' == temporary->end_place[strlen(temporary->end_place) - 1]) temporary->end_place[strlen(temporary->end_place) - 1] = 0;
			}
			while (temporary->end_place[0]=='\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |B   目    的    地：");
				{
					memset(temporary->end_place, 0, sizeof(temporary->end_place));
					rewind(stdin);
					fgets(temporary->end_place, 21, stdin);
					rewind(stdin);
					if ('\n' == temporary->end_place[strlen(temporary->end_place) - 1]) temporary->end_place[strlen(temporary->end_place) - 1] = 0;
				}
			}
			if (temporary->end_place[0] == 'c' && temporary->end_place[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			printf("                             |C   航  空  公  司：");
			{
				rewind(stdin);
				fgets(temporary->company, 13, stdin);
				rewind(stdin);
				if ('\n' == temporary->company[strlen(temporary->company) - 1]) temporary->company[strlen(temporary->company) - 1] = 0;
			}
			while (temporary->company[0] == '\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |C   航  空  公  司：");
				{
					memset(temporary->company, 0, sizeof(temporary->company));
					rewind(stdin);
					fgets(temporary->company, 13, stdin);
					rewind(stdin);
					if ('\n' == temporary->company[strlen(temporary->company) - 1]) temporary->company[strlen(temporary->company) - 1] = 0;
				}
			}
			if (temporary->company[0] == 'c' && temporary->company[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			printf("                             |D   航    班    号：");
			{
				rewind(stdin);
				fgets(temporary->flight_num, 8, stdin);
				rewind(stdin);
				if ('\n' == temporary->flight_num[strlen(temporary->flight_num) - 1]) temporary->flight_num[strlen(temporary->flight_num) - 1] = 0;
			}
			while (temporary->flight_num[0] == '\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |D   航    班    号：");
				{
					memset(temporary->flight_num, 0, sizeof(temporary->flight_num));
					rewind(stdin);
					fgets(temporary->flight_num, 9, stdin);
					rewind(stdin);
					if ('\n' == temporary->flight_num[strlen(temporary->flight_num) - 1]) temporary->flight_num[strlen(temporary->flight_num) - 1] = 0;
				}
			}
			if (temporary->flight_num[0] == 'c' && temporary->flight_num[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			printf("                             |E   起  飞  时  间：");
			{
				rewind(stdin);
				fgets(temporary->start_time, 8, stdin);
				rewind(stdin);
				if ('\n' == temporary->start_time[strlen(temporary->start_time) - 1]) temporary->start_time[strlen(temporary->start_time) - 1] = 0;
			}
			while (temporary->start_time[0] == '\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |E   起  飞  时  间：");
				{
					memset(temporary->start_time, 0, sizeof(temporary->start_time));
					rewind(stdin);
					fgets(temporary->start_time, 8, stdin);
					rewind(stdin);
					if ('\n' == temporary->start_time[strlen(temporary->start_time) - 1]) temporary->start_time[strlen(temporary->start_time) - 1] = 0;
				}
			}
			if (temporary->start_time[0] == 'c' && temporary->start_time[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			printf("                             |F   到  达  时  间：");
			{
				rewind(stdin);
				fgets(temporary->end_time, 8, stdin);
				rewind(stdin);
				if ('\n' == temporary->end_time[strlen(temporary->end_time) - 1]) temporary->end_time[strlen(temporary->end_time) - 1] = 0;
			}
			while (temporary->end_time[0] == '\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |F   到  达  时  间：");
				{
					memset(temporary->end_time, 0, sizeof(temporary->end_time));
					rewind(stdin);
					fgets(temporary->end_time, 8, stdin);
					rewind(stdin);
					if ('\n' == temporary->end_time[strlen(temporary->end_time) - 1]) temporary->end_time[strlen(temporary->end_time) - 1] = 0;
				}
			}
			if (temporary->end_time[0] == 'c' && temporary->end_time[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			printf("                             |G   座          位：");
			{
				rewind(stdin);
				fgets(temporary->people_num, 6, stdin);
				rewind(stdin);
				if ('\n' == temporary->people_num[strlen(temporary->people_num) - 1]) temporary->people_num[strlen(temporary->people_num) - 1] = 0;
			}
			while (temporary->people_num[0] == '\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |G   座          位：");
				{
					memset(temporary->people_num, 0, sizeof(temporary->people_num));
					rewind(stdin);
					fgets(temporary->people_num, 6, stdin);
					rewind(stdin);
					if ('\n' == temporary->people_num[strlen(temporary->people_num) - 1]) temporary->people_num[strlen(temporary->people_num) - 1] = 0;
				}
			}
			if (temporary->people_num[0] == 'c' && temporary->people_num[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			printf("                             |H   价          格：");
			{
				rewind(stdin);
				fgets(temporary->price, 6, stdin);
				rewind(stdin);
				if ('\n' == temporary->price[strlen(temporary->price) - 1]) temporary->price[strlen(temporary->price) - 1] = 0;
			}
			while (temporary->price[0] == '\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |H   价          格：");
				{
					memset(temporary->price, 0, sizeof(temporary->price));
					rewind(stdin);
					fgets(temporary->price, 6, stdin);
					rewind(stdin);
					if ('\n' == temporary->price[strlen(temporary->price) - 1]) temporary->price[strlen(temporary->price) - 1] = 0;
				}
			}
			if (temporary->price[0] == 'c' && temporary->price[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
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
			printf("                             |空间申请失败！\a\n");
			return;
		}
		else
		{
			flight_info_num++;
			node->next_part = node->next_global;
			{
				show_flight_info_subtitle();
				line();
				printf("                             |%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", flight_info_num, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
				line();
				printf("                             |添加成功！\n");
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
			secret_flight_info = node;//保存最后成员的地址
		}
	}
	printf("                             |");
	system("pause");
	system("cls");
}
//修改航班信息函数
void modify_flight_info(void)
{
	int i;
	flight* node;
	char located_flight_info[32];

	system("cls");
	show_FRMS_title();//调用输出航班预定管理系统题头函数
	show_flight_info_title();//调用输出输出航班预定管理系统题头函数
	show_flight_info(head_flight_global);
	show_manager_title();
	line();
	printf("                             |键入c取消修改，返回上级菜单!\n");
	printf("                             |请选择要修改的航班信息对应序号(1-%02d)：", flight_info_num);
	{
		rewind(stdin);
		fgets(located_flight_info, 4, stdin);
		rewind(stdin);
		if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
	}
	while (1)
	{
		if ((strtol(located_flight_info, NULL, 10) < 0 || strtol(located_flight_info, NULL, 10) > flight_info_num) && located_flight_info[0] != 'c') printf("                             |输入数据越界！\a\n");
		else
			if (located_flight_info[0] == '\0')printf("                             |未检测到字符！\a\n");
			else break;
		printf("                             |请选择要修改的航班信息对应序号(1-%02d)：", flight_info_num);
		{
			rewind(stdin);
			fgets(located_flight_info, 4, stdin);
			rewind(stdin);
			if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
		}
	}
	if (located_flight_info[0] == 'c' && located_flight_info[1] == '\0')
	{
		line();
		printf("                             |取消成功！\n");
		printf("                             |");
		system("pause");
		system("cls");
		return;
	}
	int max = strtol(located_flight_info, NULL, 10);
	node = head_flight_global;
	int offset, limmit;
	for (i = 0; i < max - 1; i++)node = node->next_global;
	while (1)
	{
		{
			system("cls");
			show_FRMS_title();
			show_manager_title();
			show_flight_info_subtitle();
			line();
			printf("                             |%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", max, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			line();
		}
		printf("                             |键入c取消修改，返回上级菜单!\n");
		printf("                             |请选择要修改的航班信息对应序号（A-H）：");
		{
			rewind(stdin);
			fgets(located_flight_info, 4, stdin);
			rewind(stdin);
			if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
		}
		while (1)
		{
			if (located_flight_info[0] == '\0')printf("                             |未检测到字符！\a\n");
			else
				if ((located_flight_info[0] < 'A' || located_flight_info[0] > 'H') && located_flight_info[0] != 'c' || located_flight_info[1] != '\0') printf("                             |含有非法字符！\a\n");
				else break;
			printf("                             |请选择要修改的航班信息对应序号（A-H）：");
			{
				rewind(stdin);
				fgets(located_flight_info, 4, stdin);
				rewind(stdin);
				if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
			}
		}
		if (located_flight_info[0] == 'c')
		{
			line();
			printf("                             |取消成功！\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
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
		default: printf("                             |传递参数错误，关键字错误\n\a"); return;
		}
		{
			line();
			printf("                             |字符数限制长度：\n");
			printf("                             |A:20   B:20   C:12   D:7   E:7   F:7   G:5   H:5\n");
			line();
			printf("                             |%s -> ", node->start_place + offset);
			{
				rewind(stdin);
				fgets((node->start_place + offset), limmit, stdin);
				rewind(stdin);
				if ('\n' == (node->start_place + offset)[strlen((node->start_place + offset)) - 1]) (node->start_place + offset)[strlen((node->start_place + offset)) - 1] = 0;
			}
			show_flight_info_subtitle();
			line();
			printf("                             |%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", max, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			line();
			printf("                             |修改成功\n");
		}
		printf("                             |是否继续修改本条航班信息（y or n）：");

		{
			rewind(stdin);
			fgets(located_flight_info, 3, stdin);
			rewind(stdin);
			if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
		}
		while (1)
		{
			if (located_flight_info[0] != 'y' && located_flight_info[0] != 'n')printf("                             |含有非法字符！\a\n");
			else
				if (located_flight_info[0] == '\0')printf("                             |未检测到字符！\a\n");
				else break;
			printf("                             |是否继续修改本条航班信息（y or n）：");
			{
				rewind(stdin);
				fgets(located_flight_info, 3, stdin);
				rewind(stdin);
				if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
			}
		}
		if (located_flight_info[0] == 'n')
		{
			printf("                             |");
			system("pause");
			system("cls");
			return;
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
	show_FRMS_title();//调用输出航班预定管理系统题头函数
	show_flight_info_title();//调用输出输出航班预定管理系统题头函数
	show_flight_info(head_flight_global);
	show_manager_title();
	line();
	printf("                             |键入c取消删除，返回上级菜单！\n");
	printf("                             |请选择要删除的航班信息对应序号(1-%02d)：", flight_info_num);
	{
		rewind(stdin);
		fgets(located_flight_info, 4, stdin);
		rewind(stdin);
		if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
	}
	if (located_flight_info[0] == 'c' && located_flight_info[1] == '\0')
	{
		line();
		printf("                             |取消成功！\n");
		printf("                             |");
		system("pause");
		system("cls");
		return;
	}
	while (1)
	{
		if ((strtol(located_flight_info, NULL, 10) <= 0 || strtol(located_flight_info, NULL, 10) > flight_info_num))printf("                             |数据越界！\a\n");
		else
			if (located_flight_info[0] == '\0')printf("                             |未检测到字符！\a\n");
			else break;
		printf("                             |请选择要删除的航班信息对应序号(1-%02d)：", flight_info_num);
		{
			rewind(stdin);
			fgets(located_flight_info, 4, stdin);
			rewind(stdin);
			if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
		}
		if (located_flight_info[0] == 'c' && located_flight_info[1] == '\0')
		{
			line();
			printf("                             |取消成功！\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
	}
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
			show_manager_title();
			show_flight_info_subtitle();
			line();
			printf("                             |%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", max, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			line();
		}
		printf("                             |请确认是否删除这条航班信息（y or n）：");
		{
			rewind(stdin);
			fgets(located_flight_info, 3, stdin);
			rewind(stdin);
			if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
		}
		while (1)
		{
			if (located_flight_info[0] != 'y' && located_flight_info[0] != 'n')printf("                             |含有非法字符！\a\n");
			else
				if (located_flight_info[0] == '\0')printf("                             |未检测到字符！\a\n");
				else break;
			printf("                             |请确认是否删除这条航班信息（y or n）：");
			{
				rewind(stdin);
				fgets(located_flight_info, 3, stdin);
				rewind(stdin);
				if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
			}
		}
		line();
		if (located_flight_info[0] == 'y')
		{
			buffer->next_global = node->next_global;
			buffer->next_part = node->next_part;
			flight_info_num--;
			if (node->next_part != NULL)head_flight_part--;
			free(node);
			printf("                             |删除成功!\n");
		}
		else printf("                             |未进行删除操作!\n");
	}
	else
	{
		system("cls");
		show_FRMS_title();
		show_flight_info_subtitle();
		line();
		printf("                             |%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", max, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
		line();
		printf("                             |请确认是否删除这条航班信息（y or n）：");
		{
			rewind(stdin);
			fgets(located_flight_info, 3, stdin);
			rewind(stdin);
			if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
		}
		while (1)
		{
			if (located_flight_info[0] != 'y'&& located_flight_info[0] != 'n')printf("                             |含有非法字符！\a\n");
			else
				if (located_flight_info[0] == '\0')printf("                             |未检测到字符！\a\n");
				else break;
			printf("                             |请确认是否删除这条航班信息（y or n）：");
			{
				rewind(stdin);
				fgets(located_flight_info, 3, stdin);
				rewind(stdin);
				if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
			}
		}
		if (located_flight_info[0] == 'y')
		{
			head_flight_global = node->next_global;
			head_flight_part = node->next_part;
			flight_info_num--;
			if (node->next_part != NULL)head_flight_part--;
			free(node);
			printf("                             |删除成功\n");
		}
		else printf("                             |未进行删除操作\n");
	}
	printf("                             |");
	system("pause");
	system("cls");
}
//订票函数
void reserve_flight_ticket(void)
{
	int i;
	flight* node;
	char located_flight_info[32];

	system("cls");
	show_FRMS_title();//调用输出航班预定管理系统题头函数
	show_flight_info_title();//调用输出输出航班预定管理系统题头函数
	show_flight_info(head_flight_global);

	printf("                             |请选择预定航班对应序号：");
	{
		rewind(stdin);
		fgets(located_flight_info, 4, stdin);
		rewind(stdin);
		if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
	}
	while (1)
	{
		if ((strtol(located_flight_info, NULL, 10) <= 0 || strtol(located_flight_info, NULL, 10) > flight_info_num))printf("                             |数据越界！\a\n");
		else
			if (located_flight_info[0] == '\0')printf("                             |未检测到字符！\a\n");
			else break;
		printf("                             |请选择要修改的航班信息对应序号：");
		{
			rewind(stdin);
			fgets(located_flight_info, 4, stdin);
			rewind(stdin);
			if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
		}
	}

	int max = strtol(located_flight_info, NULL, 10);
	node = head_flight_global;

	for (i = 0; i < max - 1; i++)node = node->next_global;

	{
		system("cls");
		show_FRMS_title();
		show_flight_info_subtitle();
		line();
		printf("                             |%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", max, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
		line();
	}

	printf("                             |请确认是否预定本次航班（y or n）：");
	{
		rewind(stdin);
		fgets(located_flight_info, 3, stdin);
		rewind(stdin);
		if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
	}
	while (1)
	{
		if (located_flight_info[0] != 'y' && located_flight_info[0] != 'n')printf("                             |含有非法字符！\a\n");
		else
			if (located_flight_info[0] == '\0')printf("                             |未检测到字符！\a\n");
			else break;
		printf("                             |请确认是否预定本次航班（y or n）：");
		{
			rewind(stdin);
			fgets(located_flight_info, 3, stdin);
			rewind(stdin);
			if ('\n' == located_flight_info[strlen(located_flight_info) - 1]) located_flight_info[strlen(located_flight_info) - 1] = 0;
		}
	}

	switch (located_flight_info[0])
	{
	case'y'://处理航班信息记录到旅客
		rewind(stdin);
		passenger_item(node);//传递指针
		printf("                             |");
		system("pause");
		system("cls");
		break;
	case'n':system("cls"); return;
	}//插入记录订票的函数

}
//订票函数附属函数
void passenger_item(flight* fp_person)//订票明细
{
	char he[20] = { "data\\users\\" };//名头,data里的
	char he_2[20] = { "backup\\users\\" };//名头,备份里的
	char tail[8] = { ".txt" };//名尾
	char total_file[120] = { 0 };//原始users文件名，大点
	char total_file_2[120] = { 0 };//备份文件名，大点
	flight* node = fp_person;
	strcat(total_file, he);//接头
	strcat(total_file, located_passenger_info_global->nickname);//中间
	//strcat(total_file, "BHK");//测试用BHK备份
	strcat(total_file, tail);//接尾

	strcat(total_file_2, he_2);//接头
	strcat(total_file_2, located_passenger_info_global->nickname);//中间
	//strcat(total_file, "BHK");//测试用BHK备份
	strcat(total_file_2, tail);//接尾

	FILE* fp = fopen(total_file, "a+");//data里的
	FILE* fp2 = fopen(total_file_2, "a+");//backup里的
	fprintf(fp, "%s %s %s %s %s %s %s %s\n", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);//写入data下的user
	fprintf(fp2, "%s %s %s %s %s %s %s %s\n", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);//写入back下的user
	printf("                             |订票成功！\n");
	fclose(fp);
	return;
}

//输出长横线
void line(void)
{
	printf("                             -----------------------------------------------------------------------------------------------------\n");//101个- 29个空格
}
//输出航班预定管理系统题头
void show_FRMS_title(void)
{
	line();
	printf("\n\n                                                  航      班      预      定      管      理      系      统\n\n\n");
}
//输出航班时刻表题头
void show_flight_info_title(void)
{
	line();
	printf("\n                                                                        航 班 时 刻 表\n\n");
}
//输出航班时刻表分类栏
void show_flight_info_subtitle(void)
{
	line();
	printf("                             |  |%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", "A始发地", "B目的地", "C航空公司", "D航班号", "E起飞时间", "F到达时间", "G座位", "H票价");
}
//输出旅客信息表题头
void show_passenger_info_title(void)
{
	line();
	printf("\n                                                                        旅 客 信 息 表\n\n");
}
//输出旅客模式题头
void show_passenger_title(void)
{
	line();
	printf("\n                                                                         旅 客 模 式 \n\n");
}
//输出旅客信息分类栏
void show_passenger_info_subtitle(void)
{
	line();
	printf("                             |  |%20s|%20s|%12s|%23s|%17s|\n", "A用户名", "B用户密码", "C姓名", "D身份证号", "E联系方式");
}
//输出管理员标题
void show_manager_title(void)
{
	line();
	printf("\n                                                                        管 理 员 模 式\n\n");
}
//输出历史记录标题
void show_passenger_histroy_title(void)
{
	line();
	printf("\n                                                                         历 史 记 录\n\n");
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
	char sentence[] = "                             |Loading Knock Me Out. . .\nEnter q to stop the music and start the rael project         ;)\nPlease enter a letter:\0";
	char sentence_reload[] = "                             |Reloading Knock Me Out...\nWhy don't you LISTEN TO ME to continue!?                     :(\nEnter q!:\0";
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
//resize the window
void full_screen(void)
{
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            //获取屏幕宽度 像素
	int cy = GetSystemMetrics(SM_CYSCREEN);            //获取屏幕高度 像素
	//printf("%d %d\n", cx, cy);
	if (cx > 1280 || cy > 720)
	{
		LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);  //获取窗口信息
		SetWindowLong(hwnd, 0, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);//设置窗口信息
		SetWindowPos(hwnd, HWND_TOP, (int)((cx - 1280) / 2), (int)((cy - 720) / 2), 1280, 720, 0);//COOL
	}
	else
	{
		LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);  //获取窗口信息
		SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);//设置窗口信息
		SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
	}
}