#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"global.h"//�Զ���ͷ�ļ�
#include"output.h"//�����ͷ�ļ�

//��ȡ�ļ�����
void pull_flight_info(void)
{
	flight_info_num = 0;//��ʼ��������Ϣ����
	FILE* fp;//�����ļ�ָ��

	fp = fopen("flight_info.txt", "r");//��flight_info.txt�ļ�

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
							secret = node;
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
	fp = fopen("flight_info.output", "w");//�򿪲��������flight_info.txt�ļ�����
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
	int i = 0;//����ѭ������
	flight* node = head;//���岢��ʼ����ͨ�ڵ�

	FRMS_title();//�����������Ԥ������ϵͳ��ͷ����
	flight_info_title();//��������������Ԥ������ϵͳ��ͷ����
	flight_info_subtitle();//�����������ʱ�̱����������

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

//��ؼ���������
flight* sort_flight_info(char direction, int option_num, char* option_info, int loop_num, flight* head)
//��Ҫ ˳�����ʶ�ַ� �ؼ��ָ��� �ؼ��������׵�ַ ����ĺ�����Ϣ���� ����ĺ�����Ϣ�׵�ַ || ���� ������׵�ַ
{
	int offset;//����������Առ�ó��Ȼ���ƫ����
	int i, j;//����ѭ������
	_Bool bool, bool_direction;

	flight* node, * buffer, * lag;//������ͨ�ڵ㡢����ڵ㡢�ͺ�ڵ�	

	//�ж�����˳��
	switch (direction)
	{
	case 'A': bool_direction = 1; break;
	case 'B': bool_direction = 0; break;
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

//��ؼ��ֲ�ѯ����(���ؼ�����ʵ��)
flight* refer_flight_info(int option_num, char* option_info, char* refer_info, flight* head)//��Ҫ �ؼ��ʸ��� �ؼ����׵�ַ ����ѯ�����׵�ַ || ���� ��ѯ���������׵�ַ
{
	int j = 0;
	int offset;//����ƫ����
	flight* node, * buffer;//������ͨ�ڵ㡢����ڵ�

	node = head;
	buffer = head;
	if (strlen(option_info) == 0 || *refer_info == '\n')
	{
		printf("δ��⵽�ַ���\n");
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
	default: printf("���ݲ������󣬲�ѯ�ؼ��ִ���\n\a"); return NULL;
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















//������������
int main()
{
	char option_sort[9] = { 'A','B','F','B','C','E','H','D' };
	char refer_info[32] = { "�Ϻ�" };
	int option_num = 1;
	char direction = 'B';

	//music();//careful!

	//���Ժ���
	{
		printf("��ȡ����...\n");
		pull_flight_info();
		printf("���ݶ�д�ɹ�\n\n");
		system("pause");

		printf("�������...\n");
		show_flight_info(head_flight_global);
		printf("��������ɹ�\n\n");
		system("pause");

		printf("��ѯ����...\n");
		head_flight_part = refer_flight_info(option_num, option_sort, refer_info, head_flight_global);
		printf("��ѯ�ؼ���:%s\n", option_sort);
		printf("���ݲ�ѯ�ɹ�\n\n");
		system("pause");

		printf("�������...\n");
		show_flight_info(head_flight_part);
		printf("��������ɹ�\n\n");
		system("pause");

		//printf("��������...\n");
		//head_flight_global = sort_flight_info(direction, option_num, option_sort, flight_info_num, head_flight_global);
		//printf("����ؼ���:%s\n", option);
		//printf("��������ɹ�\n\n");
		

		//printf("�������...\n");
		//show_flight_info(head_flight_global);
		//printf("��������ɹ�\n\n");

		//printf("��������...\n");
		//push_flight_info();
		//printf("���ݱ���ɹ�\n\n");
	}


	printf("Done\n");

	return 0;
}