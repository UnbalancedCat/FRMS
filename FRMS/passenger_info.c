#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"global.h"
//��ȡ�ļ�����
void pull_passenger_info(void)
{
	passenger_info_num = 0;//��ʼ���ÿ���Ϣ����
	FILE* fp;//�����ļ�ָ��

	fp = fopen("data\\passenger_info.txt", "r");//��passenger_info.txt�ļ�

	if (fp == NULL)
	{
		printf("�ÿ���Ϣ�ļ�ȱʧ��\a\n");//��ʾ�ļ��Ƿ�ȱʧ
		return;
	}
	else
	{
		passenger* node;//������ͨ�ڵ�
		node = (passenger*)malloc(sizeof(passenger));//����ռ�
		head_passenger_global = node;//����ͷ�ڵ�

		if (node == NULL)
		{
			printf("�ڴ����ʧ�ܣ�\a\n");//��ʾ�ռ��Ƿ���䲻��
			return;//��ֹ����
		}
		else
		{
			//��һ��¼��
			if (fscanf(fp, "%s %s %s %s %s", node->nickname, node->password, node->name, node->id_num, node->phone_num) != 5)
			{
				printf("�ļ���дʧ�ܣ�\a\n");//��ʾ�ļ��Ƿ��д�ɹ�
				return;//��ֹ����
			}
			//ʣ��¼��
			while (1)
			{
				passenger_info_num++;//�ÿ���Ϣ��������
				node->next_global = (passenger*)malloc(sizeof(passenger));//����ռ�
				node->next_part = node->next_global;
				if (node->next_global == NULL)
				{
					printf("�ڴ����ʧ�ܣ�\a\n");//��ʾ�ռ��Ƿ���䲻��
					return;//��ֹ����
				}
				else
				{
					node = node->next_global;//�����ƶ��ڵ�

					if (fscanf(fp, "%s %s %s %s %s", node->nickname, node->password, node->name, node->id_num, node->phone_num) != 5)//��ȡһ�����ݱ����ڵ�ǰ�ڵ�,���ж��Ƿ��д���
					{
						{	//��ʼ�����ÿռ�
							strcpy(node->nickname, "\0");
							strcpy(node->password, "\0");
							strcpy(node->name, "\0");
							strcpy(node->id_num, "\0");
							strcpy(node->phone_num, "\0");
							node->next_global = NULL;
							node->next_part = NULL;
							secret_passenger_info = node;//��������Ա�ĵ�ַ
						}
						break;
					}
				}
			}
			fclose(fp);//�ر��ļ�
		}
	}
}
//�����ļ�����
void push_passenger_info(void)
{
	passenger* node = head_passenger_global;
	FILE* fp;//�����ļ�ָ��
	fp = fopen("data\\passenger_info.output", "w");//�򿪲��������passenger_info.txt�ļ�����
	if (fp == NULL)
	{
		printf("�ļ��������\a\n");//��ʾfopen�Ƿ�ɹ�����ָ��
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
//��ʾ�ÿ���Ϣ����
void show_passenger_info(passenger* head)//��Ҫ ��ʾ��������׵�ַ
{
	int i = 0;//����ѭ������
	passenger* node = head;//���岢��ʼ����ͨ�ڵ�

	show_passenger_info_subtitle();//�����������ʱ�̱����������

	line();
	if (head != head_passenger_part && head == head_passenger_global)
	{
		while (node->next_global != NULL)
		{	
			printf("|%02d|%20s|%20s|%12s|%23s|%17s|\n", ++i, node->nickname, node->password, node->name, node->id_num, node->phone_num);
			node = node->next_global;
		}
	}
	else
	{
		if (head == NULL)
		{
			printf("                                      û �� �� �� �� �� �� �� Ϣ\n");
		}
		else
		{
			while (node->next_part != NULL)
			{
				printf("|%02d|%20s|%20s|%12s|%23s|%17s|\n", ++i, node->nickname, node->password, node->name, node->id_num, node->phone_num);
				node = node->next_part;
			}
		}
	}
	line();
}
//��ؼ���������
passenger* sort_passenger_info(char direction, int option_num, char* option_info, int loop_num, passenger* head)
//��Ҫ ˳�����ʶ�ַ� �ؼ��ֶ������ �ؼ��ֶ��������׵�ַ ������ÿ���Ϣ���� ������ÿ���Ϣ�׵�ַ || ���� ������׵�ַ
{
	int offset;//����������Առ�ó��Ȼ���ƫ����
	int i, j;//����ѭ������
	_Bool bool, bool_direction;

	passenger* node, * buffer, * lag;//������ͨ�ڵ㡢����ڵ㡢�ͺ�ڵ�	

	//�ж�����˳��
	switch (direction)
	{
	case 'D': bool_direction = 1; break;
	case 'U': bool_direction = 0; break;
	default: bool_direction = 1;
	}

	//�жϹؼ���
	switch (*option_info)
	{
	case 'A':offset = 0; break;
	case 'B':offset = 50; break;
	case 'C':offset = 100; break;
	case 'D':offset = 150; break;
	case 'E':offset = 180; break;
	default: printf("���ݲ�����������ؼ��ִ���\n\a"); return head;
	}

	//һ���ؼ���
	for (i = 0; i < loop_num - 1; i++)
	{
		node = head;//��ʼ����ͨ�ڵ�
		lag = head;//��ʼ���ͺ�ڵ�
		for (j = 0; j < loop_num - 1 - i; j++)
		{
			buffer = node;//��ʼ������ڵ�

			bool = ((strcmp(node->nickname + offset, node->next_global->nickname + offset) == 1) == bool_direction);

			if (bool)
			{
				node = node->next_global;
				buffer->next_global = node->next_global;
				node->next_global = buffer;
				if (j == 0)
				{
					head = node;
					lag = head;//��ʼ���ͺ�ڵ�
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

	//�����ؼ���
	if (option_num != 1)
	{
		passenger* head_next, * buffer_next, * lag;//���崫�ݸ�Ƕ�׺����������׵�ַ��
		int loop_num_next;//���崫�ݸ�Ƕ�׺����������Ա����
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

				if (bool)//ǰ���ԱԪ�رȶ���ͬ�������ȶ�
				{
					node = node->next_global;
					loop_num_next += 1;
				}
				else//ǰ���ԱԪ�ضԱȲ�ͬ����¼����ʼ�����ؼ�������,����������������ѭ��
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
//�ν�������
void bridge_sort_passenger_info(void)
{
	int i = 5;
	char direction[4] = { 0 };//˳��
	char option_info[10] = { 0 };//�洢�ؼ���
	int option_num = 0;//�ؼ��ָ���

	//���������ʶ������
	printf("��ѡ������˳��D��˳��U�����𣩣�");
	{
		rewind(stdin);
		fgets(direction, 3, stdin);
		rewind(stdin);
		if ('\n' == direction[strlen(direction) - 1]) direction[strlen(direction) - 1] = 0;
	}
	while (direction[1] != '\0' || (direction[0] != 'D' && direction[0] != 'U'))
	{
		printf("���зǷ��ַ������������룡\a\n");
		printf("��ѡ������˳��D��˳��U�����𣩣�");
		{
			rewind(stdin);
			fgets(direction, 3, stdin);
			rewind(stdin);
			if ('\n' == direction[strlen(direction) - 1]) direction[strlen(direction) - 1] = 0;
		}
	}
	//��������ؼ�������
	printf("��ѡ������ؼ�����ţ��磺ABH ����");
	{
		rewind(stdin);
		fgets(option_info, 7, stdin);
		rewind(stdin);
		if ('\n' == option_info[strlen(option_info) - 1]) option_info[strlen(option_info) - 1] = 0;
	}
	i = (int)strlen(option_info);
	while (i)
	{
		if (option_info[6] != '\0' || (option_info[i - 1] < 'A' || option_info[i - 1] > 'E'))
		{
			printf("���зǷ��ַ������������룡\a\n");
			printf("��ѡ������ؼ�����ţ��磺ABH ����");
			{
				memset(option_info, 0, sizeof(option_info));
				rewind(stdin);
				fgets(option_info, 7, stdin);
				rewind(stdin);
				if ('\n' == option_info[strlen(option_info) - 1]) option_info[strlen(option_info) - 1] = 0;
			}
			i = (int)strlen(option_info);
		}
		else i--;
	}
	//��������ؼ��ָ���
	option_num = (int)strlen(option_info);


	head_passenger_global = sort_passenger_info(direction[0], option_num, option_info, passenger_info_num, head_passenger_global);
	show_FRMS_title();//�����������Ԥ������ϵͳ��ͷ����
	show_passenger_info_title();//��������������Ԥ������ϵͳ��ͷ����
	show_passenger_info(head_passenger_global);
	return;
}
//��ؼ��־�ȷ��ѯ�����������ֲ�ѯΪģ����ѯ��
void refine_search_passenger_info(int option_num, char* option_info, char refer_info[][50], passenger* head)//��Ҫ �ؼ��ָ��� �ؼ��ֶ��������׵�ַ �ṩ�ؼ����׵�ַ ����ѯ�����׵�ַ
{
	search_passenger_info_num = 0;
	int j = 0;
	int offset;//����ƫ����
	passenger* node, * buffer;//������ͨ�ڵ㡢����ڵ�

	node = head;
	buffer = head;

	if (strlen(option_info) == 0 || refer_info[0][0] == '\n')
	{
		printf("δ��⵽�ַ���\n\a");
		return;
	}
	switch (*option_info)
	{
	case 'A':offset = 0; break;
	case 'B':offset = 50; break;
	case 'C':offset = 100; break;
	case 'D':offset = 150; break;
	case 'E':offset = 180; break;
	default: printf("���ݲ������󣬲�ѯ�ؼ��ִ���\n\a"); return;
	}

	//һ���ؼ���
	if (head != head_passenger_part && head == head_passenger_global)//��ȡ���׵�ַΪȫ�������ַ
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
	else//��ȡ���׵�ַΪ��ѯ�����ַ
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

	//�����ؼ���
	if (option_num != 1)
	{
		refine_search_passenger_info(option_num - 1, option_info + 1, refer_info + 1, head);
	}
	else if (search_passenger_info_num == 0)head_passenger_part = NULL;
}
//�νӲ�ѯ����
void bridge_refine_search_sort_passenger_info(void)
{
	int i = 0;//����ؼ��ָ���
	int j = 0;
	char refer_info[5][32] = { 0 };//�����Ӧ�ؼ��ֲ�ѯ
	char option_info[10] = { 0 };//�洢�ؼ���
	int option_num = 0;//�ؼ��ָ���
	char buffer[32] = { 0 };//��������

	i = 5;
	while (i)
	{
		printf("��ѡ���ѯ�ؼ����Լ���ѯ����,����0��ɣ��磺C��������");
		{
			rewind(stdin);
			fgets(buffer, 25, stdin);
			rewind(stdin);
			if ('\n' == buffer[strlen(buffer) - 1]) buffer[strlen(buffer) - 1] = 0;
		}
		if (buffer[0] == '0' && buffer[1] == '\0')break;
		while (buffer[24] != '\0' || (buffer[0] < 'A' || buffer[0] > 'E'))
		{
			printf("���зǷ��ַ������������룡\a\n");
			printf("��ѡ���ѯ�ؼ����Լ���ѯ����,����0��ɣ��磺C��������");
			{
				rewind(stdin);
				fgets(buffer, 25, stdin);
				rewind(stdin);
				if ('\n' == buffer[strlen(buffer) - 1]) buffer[strlen(buffer) - 1] = 0;
			}
		}
		if (buffer[0] == '0' && buffer[1] == '\0')break;
		option_info[5 - i] = buffer[0];
		strcpy(refer_info[5 - i], buffer + 1);
		i--;
	}

	option_num = 5 - i;
	refine_search_passenger_info(option_num, option_info, refer_info, head_passenger_global);
	system("cls");
	show_FRMS_title();//�����������Ԥ������ϵͳ��ͷ����
	show_passenger_info_title();//�����������ÿ���ͷ����
	show_passenger_info(head_passenger_part);
	system("pause");
	return;
}
//����ÿ���Ϣ����
void add_passenger_info(void)
{
	char* endptr = NULL;
	passenger* temporary = (passenger*)malloc(sizeof(passenger));
	if (temporary == NULL)
	{
		printf("����ռ�ʧ��\a\n");
		return;
	}
	else
	{
		passenger* node;
		node = secret_passenger_info;

		{
			line();
			printf("|�ַ������Ƴ��ȣ�\n");
			printf("|A:20   B:20   C:12   D:23   E:17\n");
			line();
			printf("|����������ӵĶ�Ӧ��Ϣ��\n");
			printf("|A   ��          �ƣ�");
			{
				rewind(stdin);
				fgets(temporary->nickname, 21, stdin);
				rewind(stdin);
				if ('\n' == temporary->nickname[strlen(temporary->nickname) - 1]) temporary->nickname[strlen(temporary->nickname) - 1] = 0;
			}
			while (temporary->nickname[0] == '\0')
			{
				printf("δ��⵽�ַ������������룡\a\n");
				printf("|A   ��          �ƣ�");
				{
					memset(temporary->nickname, 0, sizeof(temporary->nickname));
					rewind(stdin);
					fgets(temporary->nickname, 21, stdin);
					rewind(stdin);
					if ('\n' == temporary->nickname[strlen(temporary->nickname) - 1]) temporary->nickname[strlen(temporary->nickname) - 1] = 0;
				}
			}
			printf("|B   ��          �룺");
			{
				rewind(stdin);
				fgets(temporary->password, 21, stdin);
				rewind(stdin);
				if ('\n' == temporary->password[strlen(temporary->password) - 1]) temporary->password[strlen(temporary->password) - 1] = 0;
			}
			while (temporary->password[0] == '\0')
			{
				printf("δ��⵽�ַ������������룡\a\n");
				printf("|B   ��          �룺");
				{
					memset(temporary->password, 0, sizeof(temporary->password));
					rewind(stdin);
					fgets(temporary->password, 21, stdin);
					rewind(stdin);
					if ('\n' == temporary->password[strlen(temporary->password) - 1]) temporary->password[strlen(temporary->password) - 1] = 0;
				}
			}
			printf("|C   ��  ʵ  ��  ����");
			{
				rewind(stdin);
				fgets(temporary->name, 13, stdin);
				rewind(stdin);
				if ('\n' == temporary->name[strlen(temporary->name) - 1]) temporary->name[strlen(temporary->name) - 1] = 0;
			}
			while (temporary->name[0] == '\0')
			{
				printf("δ��⵽�ַ������������룡\a\n");
				printf("|C   ��  ʵ  ��  ����");
				{
					memset(temporary->name, 0, sizeof(temporary->name));
					rewind(stdin);
					fgets(temporary->name, 13, stdin);
					rewind(stdin);
					if ('\n' == temporary->name[strlen(temporary->name) - 1]) temporary->name[strlen(temporary->name) - 1] = 0;
				}
			}
			printf("|C   �� �� ֤ �� �룺");
			{
				rewind(stdin);
				fgets(temporary->id_num, 24, stdin);
				rewind(stdin);
				if ('\n' == temporary->id_num[strlen(temporary->id_num) - 1]) temporary->id_num[strlen(temporary->id_num) - 1] = 0;
			}
			while (temporary->id_num[0] == '\0')
			{
				printf("δ��⵽�ַ������������룡\a\n");
				printf("|C   �� �� ֤ �� �룺");
				{
					memset(temporary->id_num, 0, sizeof(temporary->id_num));
					rewind(stdin);
					fgets(temporary->id_num, 24, stdin);
					rewind(stdin);
					if ('\n' == temporary->id_num[strlen(temporary->id_num) - 1]) temporary->id_num[strlen(temporary->id_num) - 1] = 0;
				}
			}
			printf("|E   ��  ��  ��  �룺");
			{
				rewind(stdin);
				fgets(temporary->phone_num, 18, stdin);
				rewind(stdin);
				if ('\n' == temporary->phone_num[strlen(temporary->phone_num) - 1]) temporary->phone_num[strlen(temporary->phone_num) - 1] = 0;
			}
			while (temporary->phone_num[0] == '\0')
			{
				printf("δ��⵽�ַ������������룡\a\n");
				printf("|E   ��  ��  ��  �룺");
				{
					memset(temporary->phone_num, 0, sizeof(temporary->phone_num));
					rewind(stdin);
					fgets(temporary->phone_num, 18, stdin);
					rewind(stdin);
					if ('\n' == temporary->phone_num[strlen(temporary->phone_num) - 1]) temporary->phone_num[strlen(temporary->phone_num) - 1] = 0;
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
			printf("�ռ�����ʧ�ܣ�\a\n");
			return;
		}
		else
		{
			passenger_info_num++;
			node->next_part = node->next_global;
			{
				printf("��ӳɹ�\n");
				line();
				printf("|%02d|%20s|%20s|%12s|%23s|%17s|\n", passenger_info_num, node->nickname, node->password, node->name, node->id_num, node->phone_num);
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
			secret_passenger_info = node;//��������Ա�ĵ�ַ
		}
	}
}
//�޸��ÿ���Ϣ����
void modify_passenger_info(void)
{
	int i;
	passenger* node;
	char located_passenger_info[32];

	system("cls");
	show_FRMS_title();//�����������Ԥ������ϵͳ��ͷ����
	show_passenger_info_title();//��������������Ԥ������ϵͳ��ͷ����
	show_passenger_info(head_passenger_global);

	printf("��ѡ��Ҫ�޸ĵ��ÿ���Ϣ��Ӧ��ţ�");
	{
		rewind(stdin);
		fgets(located_passenger_info, 4, stdin);
		rewind(stdin);
		if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
	}
	while (1)
	{
		if ((strtol(located_passenger_info, NULL, 10) <= 0 || strtol(located_passenger_info, NULL, 10) > passenger_info_num))printf("����Խ�磡\a\n");
		else
			if (located_passenger_info[0] == '\0')printf("δ��⵽�ַ���\a\n");
			else break;
		printf("��ѡ��Ҫ�޸ĵ��ÿ���Ϣ��Ӧ��ţ�");
		{
			rewind(stdin);
			fgets(located_passenger_info, 4, stdin);
			rewind(stdin);
			if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
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
		printf("|%02d|%20s|%20s|%12s|%23s|%17s|\n", ++i, node->nickname, node->password, node->name, node->id_num, node->phone_num);
		line();
	}
	printf("��ѡ��Ҫ�޸ĵ��ÿ���Ϣ��Ӧ��ţ�");
	{
		rewind(stdin);
		fgets(located_passenger_info, 4, stdin);
		rewind(stdin);
		if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
	}
	while (1)
	{
		if (located_passenger_info[0] == '\0')printf("δ��⵽�ַ���\a\n");
		else
			if (located_passenger_info[0] < 'A' || located_passenger_info[0] > 'H')printf("���зǷ��ַ���\a\n");
			else break;
		printf("��ѡ��Ҫ�޸ĵ��ÿ���Ϣ��Ӧ��ţ�");
		{
			rewind(stdin);
			fgets(located_passenger_info, 4, stdin);
			rewind(stdin);
			if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
		}
	}
	switch (located_passenger_info[0])
	{
	case 'A':offset = 0, limmit = 21; break;
	case 'B':offset = 50, limmit = 21; break;
	case 'C':offset = 100, limmit = 13; break;
	case 'D':offset = 150, limmit = 24; break;
	case 'E':offset = 180, limmit = 18; break;

	default: printf("���ݲ������󣬹ؼ��ִ���\n\a"); return;
	}
	{
		line();
		printf("|�ַ������Ƴ��ȣ�\n");
		printf("|A:20   B:20   C:12   D:23   E:17\n");
		line();
		printf("%s -> ", node->nickname + offset);
		{
			rewind(stdin);
			fgets((node->nickname + offset), limmit, stdin);
			rewind(stdin);
			if ('\n' == (node->nickname + offset)[strlen((node->nickname + offset)) - 1]) (node->nickname + offset)[strlen((node->nickname + offset)) - 1] = 0;
		}
		printf("�޸ĳɹ�\n");
		line();
		printf("|%02d|%20s|%20s|%12s|%23s|%17s|\n", ++i, node->nickname, node->password, node->name, node->id_num, node->phone_num);
		line();

	}
}
//ɾ���ÿ���Ϣ����
void delete_passenger_info(void)
{
	int i;
	passenger* node, * buffer;
	char located_passenger_info[5];


	system("cls");
	show_FRMS_title();//�����������Ԥ������ϵͳ��ͷ����
	show_passenger_info_title();//��������������Ԥ������ϵͳ��ͷ����
	show_passenger_info(head_passenger_global);

	printf("��ѡ��Ҫɾ�����ÿ���Ϣ��Ӧ��ţ�");
	{
		rewind(stdin);
		fgets(located_passenger_info, 4, stdin);
		rewind(stdin);
		if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
	}
	while (1)
	{
		if ((strtol(located_passenger_info, NULL, 10) <= 0 || strtol(located_passenger_info, NULL, 10) > passenger_info_num))printf("����Խ�磡\a\n");
		else
			if (located_passenger_info[0] == '\0')printf("δ��⵽�ַ���\a\n");
			else break;
		printf("��ѡ��Ҫɾ�����ÿ���Ϣ��Ӧ��ţ�");
		{
			rewind(stdin);
			fgets(located_passenger_info, 4, stdin);
			rewind(stdin);
			if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
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
			printf("|%02d|%20s|%20s|%12s|%23s|%17s|\n", max, node->nickname, node->password, node->name, node->id_num, node->phone_num);
			line();
		}
		printf("��ȷ���Ƿ�ɾ�������ÿ���Ϣ��y or n����");
		{
			rewind(stdin);
			fgets(located_passenger_info, 3, stdin);
			rewind(stdin);
			if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
		}
		while (1)
		{
			if (located_passenger_info[0] != 'y' && located_passenger_info[0] != 'n')printf("���зǷ��ַ���\a\n");
			else
				if (located_passenger_info[0] == '\0')printf("δ��⵽�ַ���\a\n");
				else break;
			printf("��ȷ���Ƿ�ɾ�������ÿ���Ϣ��y or n����");
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
			printf("ɾ���ɹ�\n");
		}
		else printf("δ����ɾ������\n");
	}
	else
	{
		system("cls");
		show_FRMS_title();
		show_passenger_info_subtitle();
		line();
		printf("|%02d|%20s|%20s|%12s|%23s|%17s|\n", max, node->nickname, node->password, node->name, node->id_num, node->phone_num);
		line();
		printf("��ȷ���Ƿ�ɾ�������ÿ���Ϣ��y or n����");
		{
			rewind(stdin);
			fgets(located_passenger_info, 3, stdin);
			rewind(stdin);
			if ('\n' == located_passenger_info[strlen(located_passenger_info) - 1]) located_passenger_info[strlen(located_passenger_info) - 1] = 0;
		}
		while (1)
		{
			if (located_passenger_info[0] != 'y' && located_passenger_info[0] != 'n')printf("���зǷ��ַ���\a\n");
			else
				if (located_passenger_info[0] == '\0')printf("δ��⵽�ַ���\a\n");
				else break;
			printf("��ȷ���Ƿ�ɾ�������ÿ���Ϣ��y or n����");
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
			printf("ɾ���ɹ�\n");
		}
		else printf("δ����ɾ������\n");
	}
}
