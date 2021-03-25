#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"global.h"
#include"flight_info.h"
//��ʼ��
void init(void)
{
	pull_flight_info();//��ȡ������Ϣ;
	read_passenger();
}
//��ȡ�ļ�����
void pull_flight_info(void)
{
	flight_info_num = 0;//��ʼ��������Ϣ����
	FILE* fp;//�����ļ�ָ��

	fp = fopen("data\\flight_info.txt", "r");//��flight_info.txt�ļ�

	if (fp == NULL)
	{
		printf("������Ϣ�ļ�ȱʧ��\a\n");//��ʾ�ļ��Ƿ�ȱʧ
		return;
	}
	else
	{
		flight * node;//������ͨ�ڵ�
		node = (flight*)malloc(sizeof(flight));//����ռ�
		head_flight_global = node;//����ͷ�ڵ�

		if (node == NULL)
		{
			printf("�ڴ����ʧ�ܣ�\a\n");//��ʾ�ռ��Ƿ���䲻��
			return;//��ֹ����
		}
		else
		{
			//��һ��¼��
			if (fscanf(fp, "%s %s %s %s %s %s %s %s", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price) != 8)
			{
				printf("�ļ���дʧ�ܣ�\a\n");//��ʾ�ļ��Ƿ��д�ɹ�
				return;//��ֹ����
			}
			//ʣ��¼��
			while (1)
			{
				flight_info_num++;//������Ϣ��������
				node->next_global = (flight*)malloc(sizeof(flight));//����ռ�
				node->next_part = node->next_global;
				if (node->next_global == NULL)
				{
					printf("�ڴ����ʧ�ܣ�\a\n");//��ʾ�ռ��Ƿ���䲻��
					return;//��ֹ����
				}
				else
				{
					node = node->next_global;//�����ƶ��ڵ�

					if (fscanf(fp, "%s %s %s %s %s %s %s %s", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price) != 8)//��ȡһ�����ݱ����ڵ�ǰ�ڵ�,���ж��Ƿ��д���
					{
						{	//��ʼ�����ÿռ�
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
							secret = node;//��������Ա�ĵ�ַ
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
void push_flight_info(void)
{
	flight* node = head_flight_global;
	FILE* fp;//�����ļ�ָ��
	fp = fopen("data\\flight_info.output", "w");//�򿪲��������flight_info.txt�ļ�����
	if (fp == NULL)
	{
		printf("�ļ��������\a\n");//��ʾfopen�Ƿ�ɹ�����ָ��
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
//��ʾ������Ϣ����
void show_flight_info(flight* head)//��Ҫ ��ʾ��������׵�ַ
{
	system("cls");
	int i = 0;//����ѭ������
	flight* node = head;//���岢��ʼ����ͨ�ڵ�

	show_FRMS_title();//�����������Ԥ������ϵͳ��ͷ����
	show_flight_info_title();//��������������Ԥ������ϵͳ��ͷ����
	show_flight_info_subtitle();//�����������ʱ�̱����������

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
			printf("                                      û �� �� �� �� �� �� �� Ϣ\n");
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
//��ؼ���������
flight* sort_flight_info(char direction, int option_num, char* option_info, int loop_num, flight* head)
//��Ҫ ˳�����ʶ�ַ� �ؼ��ֶ������ �ؼ��ֶ��������׵�ַ ����ĺ�����Ϣ���� ����ĺ�����Ϣ�׵�ַ || ���� ������׵�ַ
{
	int offset;//����������Առ�ó��Ȼ���ƫ����
	int i, j;//����ѭ������
	_Bool bool, bool_direction;

	flight* node, * buffer, * lag;//������ͨ�ڵ㡢����ڵ㡢�ͺ�ڵ�	

	//�ж�����˳��
	switch (direction)
	{
	case 'D': bool_direction = 1; break;
	case 'U': bool_direction = 0; break;
	default : bool_direction = 1;
	}

	//�жϹؼ���
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
		flight* head_next, * buffer_next, * lag;//���崫�ݸ�Ƕ�׺����������׵�ַ��
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
				if (*option_info == 'G' || *option_info == 'H')
				{
					bool = ((strtol((node->start_place + offset), NULL, 10) > strtol((node->next_global->start_place + offset), NULL, 10) == bool_direction));
				}
				else
				{
					bool = ((strcmp(node->start_place + offset, node->next_global->start_place + offset) == 1) == bool_direction);
				}

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
//�ν�������
void bridge_sort_flight_info()
{
	int i = 8;
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
	while (direction[1]!='\0'||(direction[0]!='D' && direction[0] !='U'))
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
		fgets(option_info, 10, stdin);
		rewind(stdin);
		if ('\n' == option_info[strlen(option_info) - 1]) option_info[strlen(option_info) - 1] = 0;
	}
	i = (int)strlen(option_info);
	while (i)
	{
		if (option_info[9] != '\0' || (option_info[i - 1] < 'A' || option_info[i - 1] > 'H'))
		{
			printf("���зǷ��ַ������������룡\a\n");
			printf("��ѡ������ؼ�����ţ��磺ABH ����");
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
	//��������ؼ��ָ���
	option_num = (int)strlen(option_info);
	
	
	head_flight_global = sort_flight_info(direction[0], option_num, option_info, flight_info_num, head_flight_global);
	show_flight_info(head_flight_global);
	return;
}
//��ؼ��־�ȷ��ѯ�����������ֲ�ѯΪģ����ѯ��
void refine_search_flight_info(int option_num, char* option_info, char refer_info[][32], flight* head)//��Ҫ �ؼ��ָ��� �ؼ��ֶ��������׵�ַ �ṩ�ؼ����׵�ַ ����ѯ�����׵�ַ
{
	search_flight_info_num = 0;
	int j = 0;
	int offset;//����ƫ����
	flight* node, * buffer;//������ͨ�ڵ㡢����ڵ�

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
	case 'B':offset = 32; break;
	case 'C':offset = 64; break;
	case 'D':offset = 80; break;
	case 'E':offset = 88; break;
	case 'F':offset = 96; break;
	case 'G':offset = 104; break;
	case 'H':offset = 110; break;
	default: printf("���ݲ������󣬲�ѯ�ؼ��ִ���\n\a"); return;
	}

	//һ���ؼ���
	if (head != head_flight_part && head == head_flight_global)//��ȡ���׵�ַΪȫ�������ַ
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
	else//��ȡ���׵�ַΪ��ѯ�����ַ
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

	//�����ؼ���
	if (option_num != 1)
	{
		refine_search_flight_info(option_num - 1, option_info + 1, refer_info + 1, head);
	}
	else if (search_flight_info_num == 0)head_flight_part = NULL;
}
//�νӲ�ѯ����
void bridge_refine_search_sort_flight_info()
{
	int i = 0;//����ؼ��ָ���
	int j = 0;
	char refer_info[8][32] = { 0 };//�����Ӧ�ؼ��ֲ�ѯ
	char option_info[10] = { 0 };//�洢�ؼ���
	int option_num = 0;//�ؼ��ָ���
	char buffer[32] = { 0 };//��������

	//do
	//{
		i = 8;
		while (i)
		{
			printf("��ѡ���ѯ�ؼ����Լ���ѯ����,����0��ɣ��磺A�Ϻ�����");
			{
				rewind(stdin);
				fgets(buffer, 23, stdin);
				rewind(stdin);
				if ('\n' == buffer[strlen(buffer) - 1]) buffer[strlen(buffer) - 1] = 0;
			}
			if (buffer[0] == '0' && buffer[1] == '\0')break;
			while (buffer[21] != '\0' || (buffer[0] < 'A' || buffer[0] > 'H'))
			{
				printf("���зǷ��ַ������������룡\a\n");
				printf("��ѡ���ѯ�ؼ����Լ���ѯ����,����0��ɣ��磺A�Ϻ�����");
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
//��Ӻ�����Ϣ����
void add_flight_info(void)
{
	char* endptr = NULL;
	flight* temporary = (flight*)malloc(sizeof(flight));
	if (temporary == NULL)
	{
		printf("����ռ�ʧ��\a\n");
		return;
	}
	else
	{
		flight* node;
		node = secret;

		{
			line();
			printf("|�ַ������Ƴ��ȣ�\n");
			printf("|A:20   B:20   C:12   D:7   E:7   F:7   G:5   H:5\n");
			line();
			printf("|����������ӵĶ�Ӧ��Ϣ��\n");
			printf("|A   ʼ    ��    �أ�"); if (gets_s(temporary->start_place, 21) == NULL) { printf("δ��⵽�ַ�\a\n"); return; }
			printf("|B   Ŀ    ��    �أ�"); if (gets_s(temporary->end_place, 21) == NULL) { printf("δ��⵽�ַ�\a\n"); return; }
			printf("|C   ��  ��  ��  ˾��"); if (gets_s(temporary->company, 13) == NULL) { printf("δ��⵽�ַ�\a\n"); return; }
			printf("|D   ��    ��    �ţ�"); if (gets_s(temporary->flight_num, 8) == NULL) { printf("δ��⵽�ַ�\a\n"); return; }
			printf("|E   ��  ��  ʱ  �䣺"); if (gets_s(temporary->start_time, 8) == NULL) { printf("δ��⵽�ַ�\a\n"); return; }
			printf("|F   ��  ��  ʱ  �䣺"); if (gets_s(temporary->end_time, 8) == NULL) { printf("δ��⵽�ַ�\a\n"); return; }
			printf("|G   ��          �ͣ�"); if (gets_s(temporary->people_num, 6) == NULL ) { printf("δ��⵽�ַ�\a\n"); return; }
			printf("|H   ��          ��"); if (gets_s(temporary->price, 6) == NULL ) { printf("δ��⵽�ַ�\a\n"); return; }
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
			printf("�ռ�����ʧ�ܣ�\a\n");
			return;
		}
		else
		{
			flight_info_num++;
			node->next_part = node->next_global;
			{
				printf("��ӳɹ�\n");
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
			secret = node;//��������Ա�ĵ�ַ
		}
	}
}
//�޸ĺ�����Ϣ����
void modify_flight_info(void)
{
	int i;
	flight* node;
	char located_flight_info[32];


	system("cls");
	show_flight_info(head_flight_global);

	printf("��ѡ��Ҫ�޸ĵĺ�����Ϣ��Ӧ��ţ��ַ����ƣ�2����");
	if (gets_s(located_flight_info,3) == NULL) { printf("δ��⵽�ַ�\a\n"); return; }
	if (strtol(located_flight_info, NULL, 10) <= 0 || strtol(located_flight_info, NULL, 10) > flight_info_num){printf("��������Խ��\a\n"); return; }
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
		printf("��ѡ��Ҫ�޸ĵĺ�����Ϣ��Ӧ���룺");
		if (gets_s(located_flight_info, 3) == NULL) { printf("δ��⵽�ַ�\a\n"); return; }
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
		default: printf("���ݲ������󣬹ؼ��ִ���\n\a"); return;
		}
		{
			line();
			printf("|�ַ������Ƴ��ȣ�\n");
			printf("|A:20   B:20   C:12   D:7   E:7   F:7   G:5   H:5\n");
			line();
			printf("%s -> ", node->start_place + offset);
			gets_s(node->start_place + offset, limmit);
			printf("�޸ĳɹ�\n");
			line();
			printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", max, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			line();
		}
	}
}
//ɾ��������Ϣ����
void delete_flight_info(void)
{
	int i;
	flight* node, * buffer;
	char located_flight_info[5];


	system("cls");
	show_flight_info(head_flight_global);

	printf("��ѡ��Ҫɾ���ĺ�����Ϣ��Ӧ��ţ��ַ����ƣ�2����");
	if (gets_s(located_flight_info, 3) == NULL) { printf("δ��⵽�ַ�\a\n"); return; }
	if (strtol(located_flight_info, NULL, 10) <= 0 || strtol(located_flight_info, NULL, 10) > flight_info_num) { printf("��������Խ��\a\n"); return; }
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
			printf("��ȷ���Ƿ�ɾ������������Ϣ��y or n����");
			if (gets_s(located_flight_info, 3) == NULL) { printf("δ��⵽�ַ�\a\n"); return; }
			if (located_flight_info[0] == 'y')
			{
				buffer->next_global = node->next_global;
				buffer->next_part = node->next_part;
				flight_info_num--;
				if (node->next_part != NULL)head_flight_part--;
				free(node);
				printf("ɾ���ɹ�\n");
			}
			else printf("δ����ɾ������\n");
		}
		else
		{
			system("cls");
			show_FRMS_title();
			show_flight_info_subtitle();
			line();
			printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", max, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			line();
			printf("��ȷ���Ƿ�ɾ������������Ϣ��y or n����");
			if (gets_s(located_flight_info, 3) == NULL) { printf("δ��⵽�ַ�\a\n"); return; }
			if (located_flight_info[0] == 'y')
			{
				head_flight_global = node->next_global;
				head_flight_part = node->next_part;
				flight_info_num--;
				if (node->next_part != NULL)head_flight_part--;
				free(node);
				printf("ɾ���ɹ�\n");
			}
			else printf("δ����ɾ������\n");
		}
	}
}
//��Ʊ����
void reserve_flight_ticket(void)
{


	show_flight_info(head_flight_global);
	printf("��ѡ��Ԥ�������Ӧ��ţ�");

}
//���������
void line(void)
{
	printf("-----------------------------------------------------------------------------------------------------\n");
}
//�������ʱ�̱���ͷ
void show_flight_info_title(void)
{
	line();
	printf("                                            �� �� ʱ �� ��\n");
}
//�������Ԥ������ϵͳ��ͷ
void show_FRMS_title(void)
{
	line();
	printf("\n                      ��      ��      Ԥ      ��      ��      ��      ϵ      ͳ\n\n");
}
//�������ʱ�̱������
void show_flight_info_subtitle(void)
{
	line();
	printf("|  |%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", "Aʼ����", "BĿ�ĵ�", "C���չ�˾", "D�����", "E���ʱ��", "F����ʱ��", "G�ؿ�", "HƱ��");
}
//�������Ա����
void show_manager_title(void)
{
	line();
	printf("                                            �� �� Ա ģ ʽ\n");
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

//������������
//int main()
//{
//	int i = 0;;
//	//char option_sort[9] = { 'B','A','C','D','E','F','G','B' };
//	char option_sort[9] = { 'A','H','C','B'};
//	char refer_info[8][32] = { "�Ϻ�","2","��" ,"MI"};
//	int option_num = 3;
//	char direction = 'A';
//
//	//music();//careful!
//
//	//���Ժ���
//	{
//		printf("��ȡȫ������...\n");
//		pull_flight_info();
//		printf("���ݶ�д�ɹ�\n\n");
//
//		printf("���ȫ������...\n");
//		show_flight_info(head_flight_global);
//		printf("��������ɹ�\n\n");
//
//		modify_flight_info();
//
//		delete_flight_info();
//
//		printf("��ѯ����...\n");
//		refine_search_flight_info(option_num, option_sort, refer_info, head_flight_global);
//		printf("��ѯ�ؼ���:%s\n", option_sort);
//		printf("��ѯ�ؼ���:");
//		while(refer_info[i][0]!='\0')
//		{
//			printf("%s ", refer_info[i]);
//			i++;
//		}
//		printf("\n");
//		printf("���ݲ�ѯ�ɹ�\n\n");
//		system("pause");
//
//		printf("�����ѯ����...\n");
//		show_flight_info(head_flight_part);
//		printf("��������ɹ�\n\n");
//		system("pause");
//
//		printf("����ȫ������...\n");
//		head_flight_global = sort_flight_info(direction, option_num, option_sort, flight_info_num, head_flight_global);
//		printf("����ؼ���:%s\n", option_sort);
//		printf("��������ɹ�\n\n");
//
//
//		printf("���ȫ������...\n");
//		add_flight_info();
//		printf("������ӳɹ�\n\n");
//		system("pause");
//		
//
//		printf("���ȫ������...\n");
//		show_flight_info(head_flight_global);
//		printf("��������ɹ�\n\n");
//		system("pause");
//
//		printf("����ȫ������...\n");
//		push_flight_info();
//		printf("���ݱ���ɹ�\n\n");
//		system("pause");
//
//	}
//
//
//	printf("Done\n");
//
//	return 0;
//}