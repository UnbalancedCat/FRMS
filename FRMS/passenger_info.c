#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"global.h"
//读取文件函数
void pull_passenger_info(void)
{
	passenger_info_num = 0;//初始化旅客信息数量
	FILE* fp;//定义文件指针

	fp = fopen("data\\passenger_info.txt", "r");//打开passenger_info.txt文件

	if (fp == NULL)
	{
		printf("                             |旅客信息文件缺失！\a\n");//提示文件是否缺失
		return;
	}
	else
	{
		passenger* node;//定义普通节点
		node = (passenger*)malloc(sizeof(passenger));//分配空间
		head_passenger_global = node;//保存头节点

		if (node == NULL)
		{
			printf("                             |内存分配失败！\a\n");//提示空间是否分配不足
			return;//中止函数
		}
		else
		{
			//第一次录入
			if (fscanf(fp, "%s %s %s %s %s", node->nickname, node->password, node->name, node->id_num, node->phone_num) != 5)
			{
				printf("                             |文件读写失败！\a\n");//提示文件是否读写成功
				return;//中止函数
			}
			//剩余录入
			while (1)
			{
				passenger_info_num++;//旅客信息数量自增
				node->next_global = (passenger*)malloc(sizeof(passenger));//分配空间
				node->next_part = node->next_global;
				if (node->next_global == NULL)
				{
					printf("                             |内存分配失败！\a\n");//提示空间是否分配不足
					return;//中止函数
				}
				else
				{
					node = node->next_global;//向下移动节点

					if (fscanf(fp, "%s %s %s %s %s", node->nickname, node->password, node->name, node->id_num, node->phone_num) != 5)//读取一行数据保存在当前节点,并判断是否读写完毕
					{
						{	//初始化无用空间
							strcpy(node->nickname, "\0");
							strcpy(node->password, "\0");
							strcpy(node->name, "\0");
							strcpy(node->id_num, "\0");
							strcpy(node->phone_num, "\0");
							node->next_global = NULL;
							node->next_part = NULL;
							secret_passenger_info = node;//保存最后成员的地址
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
void push_passenger_info(void)
{
	passenger* node = head_passenger_global;
	FILE* fp;//定义文件指针
	fp = fopen("data\\passenger_info.output", "w");//打开并覆盖清楚passenger_info.txt文件内容
	if (fp == NULL)
	{
		printf("文件输出错误！\a\n");//提示fopen是否成功返回指针
		return;
	}
	else
	{
		while (node->next_global != NULL)
		{
			fprintf(fp, "%s %s %s %s %s\n", node->nickname, node->password, node->name, node->id_num, node->phone_num);
			node = node->next_global;
		}
	}
	fclose(fp);
}
//显示旅客信息函数
void show_passenger_info(passenger* head)//需要 显示的链表的首地址
{
	int i = 0;//定义循环变量
	passenger* node = head;//定义并初始化普通节点

	show_passenger_info_subtitle();//调用输出航班时刻表分类栏函数

	line();
	if (head != head_passenger_part && head == head_passenger_global)
	{
		while (node->next_global != NULL)
		{	
			printf("                             |%02d|%20s|%20s|%12s|%23s|%17s|\n", ++i, node->nickname, node->password, node->name, node->id_num, node->phone_num);
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
				printf("                             |%02d|%20s|%20s|%12s|%23s|%17s|\n", ++i, node->nickname, node->password, node->name, node->id_num, node->phone_num);
				node = node->next_part;
			}
		}
	}
	line();
}
//多关键字排序函数
passenger* sort_passenger_info(char direction, int option_num, char* option_info, int loop_num, passenger* head)
//需要 顺序倒叙标识字符 关键字对象个数 关键字对象数组首地址 排序的旅客信息数量 排序的旅客信息首地址 || 返回 排序后首地址
{
	int offset;//用于描述成员占用长度或总偏移量
	int i, j;//定义循环变量
	_Bool bool, bool_direction;

	passenger* node, * buffer, * lag;//定义普通节点、缓存节点、滞后节点	

	//判断排序顺序
	switch (direction)
	{
	case 'D': bool_direction = 1; break;
	case 'U': bool_direction = 0; break;
	default: bool_direction = 1;
	}

	//判断关键字
	switch (*option_info)
	{
	case 'A':offset = 0; break;
	case 'B':offset = 50; break;
	case 'C':offset = 100; break;
	case 'D':offset = 150; break;
	case 'E':offset = 180; break;
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

			bool = ((strcmp(node->nickname + offset, node->next_global->nickname + offset) == 1) == bool_direction);

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
		passenger* head_next, * buffer_next, * lag;//定义传递给嵌套函数的链表首地址等
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
					bool = ((strcmp(node->nickname + offset, node->next_global->nickname + offset) == 1) == bool_direction);

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
						buffer = sort_passenger_info(direction, option_num - 1, option_info + 1, loop_num_next, head_next);
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
void bridge_sort_passenger_info(void)
{
	int i = 5;
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
	while (direction[1] != '\0' || (direction[0] != 'D' && direction[0] != 'U'))
	{
		printf("                             |含有非法字符，请重新输入！\a\n");
		printf("                             |请选择排序顺序（D：顺序，U：倒叙）：");
		{
			rewind(stdin);
			fgets(direction, 3, stdin);
			rewind(stdin);
			if ('\n' == direction[strlen(direction) - 1]) direction[strlen(direction) - 1] = 0;
		}
	}*/
	//处理排序关键字输入
	while (1)
	{
		printf("                             |请选择排序关键字序号（如：AE ）：");
		{
			rewind(stdin);
			fgets(option_info, 7, stdin);
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
		if (option_info[0] != '\0')break;
		else
		{
			printf("                             |未检测到字符，请重新输入！\a\n");
		}
	}
	while (i)
	{
		if (option_info[6] != '\0' || (option_info[i - 1] < 'A' || option_info[i - 1] > 'E'))
		{
			printf("                             |含有非法字符，请重新输入！\a\n");
			printf("                             |请选择排序关键字序号（如：AE ）：");
			{
				memset(option_info, 0, sizeof(option_info));
				rewind(stdin);
				fgets(option_info, 7, stdin);
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
	head_passenger_global = sort_passenger_info(direction[0], option_num, option_info, passenger_info_num, head_passenger_global);
	show_passenger_info_title();
	show_passenger_info(head_passenger_global);
	printf("                             |排序成功！\n");
	printf("                             |");
	system("pause");
	system("cls");
	return;
}
//多关键字精确查询函数（对数字查询为模糊查询）
void refine_search_passenger_info(int option_num, char* option_info, char refer_info[][50], passenger* head)//需要 关键字个数 关键字对象数组首地址 提供关键字首地址 被查询链表首地址
{
	search_passenger_info_num = 0;
	int j = 0;
	int offset;//定义偏移量
	passenger* node, * buffer;//定义普通节点、缓冲节点

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
	case 'B':offset = 50; break;
	case 'C':offset = 100; break;
	case 'D':offset = 150; break;
	case 'E':offset = 180; break;
	default: printf("                             |传递参数错误，查询关键字错误\n\a"); return;
	}

	//一级关键字
	if (head != head_passenger_part && head == head_passenger_global)//获取的首地址为全局链表地址
	{
		while (node->next_global != NULL)
		{

			if (strstr((node->nickname + offset), refer_info[0]) != NULL)
			{
				search_passenger_info_num++;
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
		buffer->next_part = secret_passenger_info;
	}
	else//获取的首地址为查询链表地址
	{
		while (node->next_part != NULL)
		{
			if (strstr((node->nickname + offset), refer_info[0]) != NULL)
			{
				search_passenger_info_num++;
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
		buffer->next_part = secret_passenger_info;
	}

	head_passenger_part = head;

	//二级关键字
	if (option_num != 1)
	{
		refine_search_passenger_info(option_num - 1, option_info + 1, refer_info + 1, head);
	}
	else if (search_passenger_info_num == 0)head_passenger_part = NULL;
}
//衔接查询函数
void bridge_refine_search_sort_passenger_info(void)
{
	int i = 0;//处理关键字个数
	int j = 0;
	char refer_info[5][50] = { 0 };//储存对应关键字查询
	char option_info[10] = { 0 };//存储关键字
	int option_num = 0;//关键字个数
	char buffer[32] = { 0 };//缓冲数组


	while (1)
	{
		i = 5;
		show_FRMS_title();
		line();
		printf("                             |关键词个数上限为5个，键入f完成输入；键入c取消输入，返回上级菜单！\n");
		line();
		while (i)
		{
			printf("                             |请选择查询关键词以及查询数据（如：C张三）：");
			{
				rewind(stdin);
				fgets(buffer, 25, stdin);
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
			while (buffer[24] != '\0' || (buffer[0] < 'A' || buffer[0] > 'E'))
			{
				printf("                             |含有非法字符！\a\n");
				printf("                             |请选择查询关键词以及查询数据（如：C张三）：");
				{
					rewind(stdin);
					fgets(buffer, 25, stdin);
					rewind(stdin);
					if ('\n' == buffer[strlen(buffer) - 1]) buffer[strlen(buffer) - 1] = 0;
				}
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
			if (buffer[0] == 'f' && buffer[1] == '\0')break;
			option_info[5 - i] = buffer[0];
			strcpy(refer_info[5 - i], buffer + 1);
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
	option_num = 5 - i;
	refine_search_passenger_info(option_num, option_info, refer_info, head_passenger_global);
	system("cls");
	show_FRMS_title();//调用输出航班预定管理系统题头函数
	show_passenger_info_title();//调用输出输出旅客题头函数
	show_passenger_info(head_passenger_part);
	printf("                             |");
	system("pause");
	system("cls");
	return;
}
//添加旅客信息函数
void add_passenger_info(void)
{
	char* endptr = NULL;
	passenger* temporary = (passenger*)malloc(sizeof(passenger));
	if (temporary == NULL)
	{
		printf("                             |申请空间失败\a\n");
		system("pause");
		system("cls");
		return;
	}
	else
	{
		passenger* node;
		node = secret_passenger_info;

		{
			show_FRMS_title();//调用输出航班预定管理系统题头函数
			show_passenger_info_title();//调用输出输出航班预定管理系统题头函数
			//show_passenger_info(head_passenger_global);
			line();
			printf("                             |字符数限制长度：\n");
			printf("                             |A:20   B:20   C:12   D:23   E:17\n");
			line();
			printf("                             |键入c取消录入，返回上级菜单!\n");
			printf("                             |请输入新添加的对应信息：\n");
			printf("                             |A   用    户    名：");
			{
				rewind(stdin);
				fgets(temporary->nickname, 21, stdin);
				rewind(stdin);
				if ('\n' == temporary->nickname[strlen(temporary->nickname) - 1]) temporary->nickname[strlen(temporary->nickname) - 1] = 0;
			}
			if (temporary->nickname[0] == 'c' && temporary->nickname[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			while (temporary->nickname[0] == '\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |A   用    户    名：");
				{
					memset(temporary->nickname, 0, sizeof(temporary->nickname));
					rewind(stdin);
					fgets(temporary->nickname, 21, stdin);
					rewind(stdin);
					if ('\n' == temporary->nickname[strlen(temporary->nickname) - 1]) temporary->nickname[strlen(temporary->nickname) - 1] = 0;
				}
				if (temporary->nickname[0] == 'c' && temporary->nickname[1] == '\0')
				{
					line();
					printf("                             |取消成功！\n");
					printf("                             |");
					system("pause");
					system("cls");
					return;
				}
			}
			printf("                             |B   密          码：");
			{
				rewind(stdin);
				fgets(temporary->password, 21, stdin);
				rewind(stdin);
				if ('\n' == temporary->password[strlen(temporary->password) - 1]) temporary->password[strlen(temporary->password) - 1] = 0;
			}
			if (temporary->password[0] == 'c' && temporary->password[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			while (temporary->password[0] == '\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |B   密          码：");
				{
					memset(temporary->password, 0, sizeof(temporary->password));
					rewind(stdin);
					fgets(temporary->password, 21, stdin);
					rewind(stdin);
					if ('\n' == temporary->password[strlen(temporary->password) - 1]) temporary->password[strlen(temporary->password) - 1] = 0;
				}
			}
			if (temporary->password[0] == 'c' && temporary->password[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			printf("                             |C   真  实  姓  名：");
			{
				rewind(stdin);
				fgets(temporary->name, 13, stdin);
				rewind(stdin);
				if ('\n' == temporary->name[strlen(temporary->name) - 1]) temporary->name[strlen(temporary->name) - 1] = 0;
			}
			if (temporary->name[0] == 'c' && temporary->name[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			while (temporary->name[0] == '\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |C   真  实  姓  名：");
				{
					memset(temporary->name, 0, sizeof(temporary->name));
					rewind(stdin);
					fgets(temporary->name, 13, stdin);
					rewind(stdin);
					if ('\n' == temporary->name[strlen(temporary->name) - 1]) temporary->name[strlen(temporary->name) - 1] = 0;
				}
				if (temporary->name[0] == 'c' && temporary->name[1] == '\0')
				{
					line();
					printf("                             |取消成功！\n");
					printf("                             |");
					system("pause");
					system("cls");
					return;
				}
			}
			printf("                             |D   身 份 证 号 码：");
			{
				rewind(stdin);
				fgets(temporary->id_num, 24, stdin);
				rewind(stdin);
				if ('\n' == temporary->id_num[strlen(temporary->id_num) - 1]) temporary->id_num[strlen(temporary->id_num) - 1] = 0;
			}
			if (temporary->id_num[0] == 'c' && temporary->id_num[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			while (temporary->id_num[0] == '\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |D   身 份 证 号 码：");
				{
					memset(temporary->id_num, 0, sizeof(temporary->id_num));
					rewind(stdin);
					fgets(temporary->id_num, 24, stdin);
					rewind(stdin);
					if ('\n' == temporary->id_num[strlen(temporary->id_num) - 1]) temporary->id_num[strlen(temporary->id_num) - 1] = 0;
				}
				if (temporary->id_num[0] == 'c' && temporary->id_num[1] == '\0')
				{
					line();
					printf("                             |取消成功！\n");
					printf("                             |");
					system("pause");
					system("cls");
					return;
				}
			}
			printf("                             |E   电  话  号  码：");
			{
				rewind(stdin);
				fgets(temporary->phone_num, 18, stdin);
				rewind(stdin);
				if ('\n' == temporary->phone_num[strlen(temporary->phone_num) - 1]) temporary->phone_num[strlen(temporary->phone_num) - 1] = 0;
			}
			if (temporary->phone_num[0] == 'c' && temporary->phone_num[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			while (temporary->phone_num[0] == '\0')
			{
				printf("                             |未检测到字符，请重新输入！\a\n");
				printf("                             |E   电  话  号  码：");
				{
					memset(temporary->phone_num, 0, sizeof(temporary->phone_num));
					rewind(stdin);
					fgets(temporary->phone_num, 18, stdin);
					rewind(stdin);
					if ('\n' == temporary->phone_num[strlen(temporary->phone_num) - 1]) temporary->phone_num[strlen(temporary->phone_num) - 1] = 0;
				}
				if (temporary->phone_num[0] == 'c' && temporary->phone_num[1] == '\0')
				{
					line();
					printf("                             |取消成功！\n");
					printf("                             |");
					system("pause");
					system("cls");
					return;
				}
			}
			line();
		}
		{
			strcpy(node->nickname, temporary->nickname);
			strcpy(node->password, temporary->password);
			strcpy(node->name, temporary->name);
			strcpy(node->id_num, temporary->id_num);
			strcpy(node->phone_num, temporary->phone_num);
			node->next_global = NULL;
			node->next_part = NULL;
		}

		node->next_global = (passenger*)malloc(sizeof(passenger));
		if (node->next_global == NULL)
		{
			printf("                             |空间申请失败！\a\n");
			return;
		}
		else
		{
			passenger_info_num++;
			node->next_part = node->next_global;
			{
				printf("                             |添加成功\n");
				line();
				printf("                             |%02d|%20s|%20s|%12s|%23s|%17s|\n", passenger_info_num, node->nickname, node->password, node->name, node->id_num, node->phone_num);
				line();
			}
			node = node->next_global;

			strcpy(node->nickname, "\0");
			strcpy(node->password, "\0");
			strcpy(node->name, "\0");
			strcpy(node->id_num, "\0");
			strcpy(node->phone_num, "\0");
			node->next_global = NULL;
			node->next_part = NULL;
			secret_passenger_info = node;//保存最后成员的地址
		}
	}
	printf("                             |");
	system("pause");
	system("cls");
}
//修改旅客信息函数_管理员
void modify_passenger_info(void)
{
	int i;
	passenger* node;
	char located_passenger_info[32];

	system("cls");
	show_FRMS_title();//调用输出航班预定管理系统题头函数
	show_passenger_info_title();//调用输出输出航班预定管理系统题头函数
	show_passenger_info(head_passenger_global);
	printf("                             |键入c取消修改，返回上级菜单!\n");
	printf("                             |请选择要修改的旅客信息对应序号：");
	{
		rewind(stdin);
		fgets(located_passenger_info, 4, stdin);
		rewind(stdin);
		if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
	}
	if (located_passenger_info[0] == 'c' && located_passenger_info[1] == '\0')
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
		if ((strtol(located_passenger_info, NULL, 10) <= 0 || strtol(located_passenger_info, NULL, 10) > passenger_info_num))printf("                             |数据越界！\a\n");
		else
			if (located_passenger_info[0] == '\0')printf("                             |未检测到字符！\a\n");
			else break;
		printf("                             |请选择要修改的旅客信息对应序号：");
		{
			rewind(stdin);
			fgets(located_passenger_info, 4, stdin);
			rewind(stdin);
			if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
		}
		if (located_passenger_info[0] == 'c' && located_passenger_info[1] == '\0')
		{
			line();
			printf("                             |取消成功！\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
	}

	int max = strtol(located_passenger_info, NULL, 10);
	node = head_passenger_global;
	int offset, limmit;

	for (i = 0; i < max - 1; i++)node = node->next_global;
	{
		system("cls");
		show_FRMS_title();
		show_passenger_info_subtitle();
		line();
		printf("                             |%02d|%20s|%20s|%12s|%23s|%17s|\n", ++i, node->nickname, node->password, node->name, node->id_num, node->phone_num);
		line();
	}
	printf("                             |键入c取消修改，返回上级菜单!\n");
	printf("                             |请选择要修改的旅客信息对应序号：");
	{
		rewind(stdin);
		fgets(located_passenger_info, 4, stdin);
		rewind(stdin);
		if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
	}
	if (located_passenger_info[0] == 'c' && located_passenger_info[1] == '\0')
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
		if (located_passenger_info[0] == '\0')printf("                             |未检测到字符！\a\n");
		else
			if (located_passenger_info[0] < 'A' || located_passenger_info[0] > 'H')printf("                             |含有非法字符！\a\n");
			else break;
		printf("                             |键入c取消修改，返回上级菜单!\n");
		printf("                             |请选择要修改的旅客信息对应序号：");
		{
			rewind(stdin);
			fgets(located_passenger_info, 4, stdin);
			rewind(stdin);
			if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
		}
		if (located_passenger_info[0] == 'c' && located_passenger_info[1] == '\0')
		{
			line();
			printf("                             |取消成功！\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
	}
	switch (located_passenger_info[0])
	{
	case 'A':offset = 0, limmit = 21; break;
	case 'B':offset = 50, limmit = 21; break;
	case 'C':offset = 100, limmit = 13; break;
	case 'D':offset = 150, limmit = 24; break;
	case 'E':offset = 180, limmit = 18; break;

	default: printf("                             |传递参数错误，关键字错误\n\a"); return;
	}
	{
		line();
		printf("                             |字符数限制长度：\n");
		printf("                             |A:20   B:20   C:12   D:23   E:17\n");
		line();
		printf("                             |%s -> ", node->nickname + offset);
		{
			rewind(stdin);
			fgets((node->nickname + offset), limmit, stdin);
			rewind(stdin);
			if ('\n' == (node->nickname + offset)[strlen((node->nickname + offset)) - 1]) (node->nickname + offset)[strlen((node->nickname + offset)) - 1] = 0;
		}
		printf("                             |修改成功\n");
		line();
		printf("                             |%02d|%20s|%20s|%12s|%23s|%17s|\n", ++i, node->nickname, node->password, node->name, node->id_num, node->phone_num);
		line();
	}
	printf("                             |");
	system("pause");
	system("cls");
}
//修改旅客信息函数_旅客
void modify_passenger_info_passenger(void)
{
	passenger* node = located_passenger_info_global;
	char located_passenger_info[32];
	int offset, limmit;


	system("cls");
	show_FRMS_title();
	show_passenger_title();
	show_passenger_info_subtitle();
	line();
	printf("                             |  |%20s|%20s|%12s|%23s|%17s|\n", node->nickname, node->password, node->name, node->id_num, node->phone_num);
	line();
	printf("                             |键入c取消修改，返回上级菜单!\n");
	while (1)
	{
		printf("                             |请选择要修改的旅客信息对应序号：");
		{
			rewind(stdin);
			fgets(located_passenger_info, 4, stdin);
			rewind(stdin);
			if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
		}
		if (located_passenger_info[0] == 'c' && located_passenger_info[1] == '\0')
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
			if (located_passenger_info[0] == '\0')printf("                             |未检测到字符！\a\n");
			else
				if (located_passenger_info[0] < 'A' || located_passenger_info[0] > 'H')printf("                             |含有非法字符！\a\n");
				else break;
			printf("                             |键入c取消修改，返回上级菜单!\n");
			printf("                             |请选择要修改的旅客信息对应序号：");
			{
				rewind(stdin);
				fgets(located_passenger_info, 4, stdin);
				rewind(stdin);
				if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
			}
			if (located_passenger_info[0] == 'c' && located_passenger_info[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
		}
		switch (located_passenger_info[0])
		{
		case 'A':offset = 0, limmit = 21; break;
		case 'B':offset = 50, limmit = 21; break;
		case 'C':break;
		case 'D':offset = 150, limmit = 24; break;
		case 'E':offset = 180, limmit = 18; break;
		default: printf("                             |传递参数错误，关键字错误\n\a"); return;
		}
		if (located_passenger_info[0] != 'C')break;
		else
		{
			line();
			printf("                             |没有权限！如需修改姓名，请联系管理员！\a\n");
			line();
		}
	}
	{
		line();
		printf("                             |字符数限制长度：\n");
		printf("                             |A:20   B:20   C:12   D:23   E:17\n");
		line();
		printf("                             |%s -> ", node->nickname + offset);
		{
			rewind(stdin);
			fgets((node->nickname + offset), limmit, stdin);
			rewind(stdin);
			if ('\n' == (node->nickname + offset)[strlen((node->nickname + offset)) - 1]) (node->nickname + offset)[strlen((node->nickname + offset)) - 1] = 0;
		}
		printf("                             |修改成功\n");
		line();
		printf("                             |  |%20s|%20s|%12s|%23s|%17s|\n", node->nickname, node->password, node->name, node->id_num, node->phone_num);
		line();
	}
	printf("                             |");
	system("pause");
	system("cls");
}
//删除旅客信息函数
void delete_passenger_info(void)
{
	int i;
	passenger* node, * buffer;
	char located_passenger_info[5];


	system("cls");
	show_FRMS_title();//调用输出航班预定管理系统题头函数
	show_passenger_info_title();//调用输出输出航班预定管理系统题头函数
	show_passenger_info(head_passenger_global);
	printf("                             |键入c取消修改，返回上级菜单!\n");
	printf("                             |请选择要删除的旅客信息对应序号：");
	{
		rewind(stdin);
		fgets(located_passenger_info, 4, stdin);
		rewind(stdin);
		if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
	}
	if (located_passenger_info[0] == 'c' && located_passenger_info[1] == '\0')
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
		if ((strtol(located_passenger_info, NULL, 10) <= 0 || strtol(located_passenger_info, NULL, 10) > passenger_info_num))printf("                             |数据越界！\a\n");
		else
			if (located_passenger_info[0] == '\0')printf("                             |未检测到字符！\a\n");
			else break;
		printf("                             |请选择要删除的旅客信息对应序号：");
		{
			rewind(stdin);
			fgets(located_passenger_info, 4, stdin);
			rewind(stdin);
			if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
		}
		if (located_passenger_info[0] == 'c' && located_passenger_info[1] == '\0')
		{
			line();
			printf("                             |取消成功！\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
	}

	int max = strtol(located_passenger_info, NULL, 10);
	node = head_passenger_global;
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
			show_passenger_info_subtitle();
			line();
			printf("                             |%02d|%20s|%20s|%12s|%23s|%17s|\n", max, node->nickname, node->password, node->name, node->id_num, node->phone_num);
			line();
		}
		printf("                             |请确认是否删除这条旅客信息（y or n）：");
		{
			rewind(stdin);
			fgets(located_passenger_info, 3, stdin);
			rewind(stdin);
			if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
		}
		while (1)
		{
			if (located_passenger_info[0] != 'y' && located_passenger_info[0] != 'n')printf("                             |含有非法字符！\a\n");
			else
				if (located_passenger_info[0] == '\0')printf("                             |未检测到字符！\a\n");
				else break;
			printf("                             |请确认是否删除这条旅客信息（y or n）：");
			{
				rewind(stdin);
				fgets(located_passenger_info, 3, stdin);
				rewind(stdin);
				if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
			}
		}
		if (located_passenger_info[0] == 'y')
		{
			buffer->next_global = node->next_global;
			buffer->next_part = node->next_part;
			passenger_info_num--;
			if (node->next_part != NULL)head_passenger_part--;
			free(node);
			printf("                             |删除成功\n");
		}
		else printf("                             |未进行删除操作\n");
	}
	else
	{
		system("cls");
		show_FRMS_title();
		show_passenger_info_subtitle();
		line();
		printf("                             |%02d|%20s|%20s|%12s|%23s|%17s|\n", max, node->nickname, node->password, node->name, node->id_num, node->phone_num);
		line();
		printf("                             |请确认是否删除这条旅客信息（y or n）：");
		{
			rewind(stdin);
			fgets(located_passenger_info, 3, stdin);
			rewind(stdin);
			if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
		}
		while (1)
		{
			if (located_passenger_info[0] != 'y' && located_passenger_info[0] != 'n')printf("                             |含有非法字符！\a\n");
			else
				if (located_passenger_info[0] == '\0')printf("                             |未检测到字符！\a\n");
				else break;
			printf("                             |请确认是否删除这条旅客信息（y or n）：");
			{
				rewind(stdin);
				fgets(located_passenger_info, 3, stdin);
				rewind(stdin);
				if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
			}
		}
		if (located_passenger_info[0] == 'y')
		{
			head_passenger_global = node->next_global;
			head_passenger_part = node->next_part;
			passenger_info_num--;
			if (node->next_part != NULL)head_passenger_part--;
			free(node);
			printf("                             |删除成功\n");
		}
		else printf("                             |未进行删除操作\n");
	}
	printf("                             |");
	system("pause");
	system("cls");
}
//旅客登录函数
void login_passenger(void)
{
	passenger* node = head_passenger_global;
	char input_passenger_username[25] = { 0 };
	char input_passenger_password[25] = { 0 };
	char judge[4] = { 0 };
	int i;

	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_passenger_title();
		line();
		printf("                             |键入c取消修改，返回上级菜单!\n");
		printf("                             |请输入旅客用户名：");
		{
			rewind(stdin);
			fgets(input_passenger_username, 25, stdin);
			rewind(stdin);
			if ('\n' == input_passenger_username[strlen(input_passenger_username) - 1]) input_passenger_username[strlen(input_passenger_username) - 1] = 0;
		}
		if (input_passenger_username[0] == 'c' && input_passenger_username[1] == '\0')
		{
			line();
			printf("                             |取消成功！\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
		while (input_passenger_username[24] != '\0')
		{
			printf("                             |超出字符限制长度！\a\n");
			printf("                             |请输入旅客用户名或身份证号码：");
			{
				memset(input_passenger_username, 0, sizeof(input_passenger_username));
				rewind(stdin);
				fgets(input_passenger_username, 25, stdin);
				rewind(stdin);
				if ('\n' == input_passenger_username[strlen(input_passenger_username) - 1]) input_passenger_username[strlen(input_passenger_username) - 1] = 0;
			}
		}
		if (input_passenger_username[0] == 'c' && input_passenger_username[1] == '\0')
		{
			line();
			printf("                             |取消成功！\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
		for (i = 0; i < passenger_info_num; i++)
		{
			if ((strcmp(input_passenger_username, node->nickname) == 0) || (strcmp(input_passenger_username, node->id_num) == 0))
			{
				located_passenger_info_global = node;
				break;
			}
			if (i == passenger_info_num - 1)
			{
				printf("                             |用户名或身份证号码不存在！\a\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			node = node->next_global;
		}
		system("cls");
		show_FRMS_title();
		show_passenger_title();
		line();
		printf("                             |登陆账户：%s\n", input_passenger_username);
		printf("                             |请输入密码：");
		{
			rewind(stdin);
			fgets(input_passenger_password, 22, stdin);
			rewind(stdin);
			if ('\n' == input_passenger_password[strlen(input_passenger_password) - 1]) input_passenger_password[strlen(input_passenger_password) - 1] = 0;
		}
		while (input_passenger_password[21] != '\0')
		{
			printf("                             |超出字符限制长度！\a\n");
			printf("                             |请输入密码：");
			{
				memset(input_passenger_password, 0, sizeof(input_passenger_password));
				rewind(stdin);
				fgets(input_passenger_password, 22, stdin);
				rewind(stdin);
				if ('\n' == input_passenger_password[strlen(input_passenger_password) - 1]) input_passenger_password[strlen(input_passenger_password) - 1] = 0;
			}
		}
		if (strcmp(input_passenger_password, node->password) != 0)
		{
			printf("                             |密码错误！\a\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
		else
		{
			located_passenger_info_global = node;
			line();
			printf("                             |登录成功，欢迎您 %s！\n", node->name);
			printf("                             |");
			system("pause");
			system("cls");
			while (1)
			{
				menu_passenger();
				system("cls");
				show_FRMS_title();
				show_passenger_title();
				line();
				printf("                             |%s，您是否要退出登录？（y or n）：", node->name);
				{
					memset(judge, 0, sizeof(judge));
					rewind(stdin);
					fgets(judge, 3, stdin);
					rewind(stdin);
					if ('\n' == judge[strlen(judge) - 1]) judge[strlen(judge) - 1] = 0;
				}
				while (judge[1] != '\0' || (judge[0] != 'y' && judge[0] != 'n'))
				{
					printf("                             |含有非法字符！\a\n");
					printf("                             |%s，您是否要退出登录？（y or n）：", node->name);
					{
						memset(judge, 0, sizeof(judge));
						rewind(stdin);
						fgets(judge, 3, stdin);
						rewind(stdin);
						if ('\n' == judge[strlen(judge) - 1]) judge[strlen(judge) - 1] = 0;
					}
				}
				if (judge[0] == 'y')
				{
					line();
					printf("                             |注销成功！欢迎再次使用本系统！\n");
					printf("                             |");
					system("pause");
					system("cls");
					return;
				}
				else
				{
					line();
					printf("                             |返回旅客菜单\n");
					printf("                             |");
					system("pause");
					system("cls");
				}
			}
		}
	}
}