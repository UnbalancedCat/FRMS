#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"global.h"//�Զ���ͷ�ļ�
#include"output.h"//�����ͷ�ļ�

//��ȡ������Ϣ�ļ�
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
		head_flight = node;//����ͷ�ڵ�

		if (node == NULL)
		{
			printf("�ڴ����ʧ�ܣ�\a\n");//��ʾ�ռ��Ƿ���䲻��
			return;//��ֹ����
		}
		else
		{
			//��һ��¼��
			if (fscanf(fp, "%s %s %s %s %s %s %d %d", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)
			{
				printf("�ļ���дʧ�ܣ�\a\n");//��ʾ�ļ��Ƿ��д�ɹ�
				return;//��ֹ����
			}
			//ʣ��¼��
			while (1)
			{
				flight_info_num++;//������Ϣ��������
				node->next_global = (flight*)malloc(sizeof(flight));//����ռ�

				if (node->next_global == NULL)
				{
					printf("�ڴ����ʧ�ܣ�\a\n");//��ʾ�ռ��Ƿ���䲻��
					return;//��ֹ����
				}
				else
				{
					end_flight = node;//����β�ڵ�
					node = node->next_global;//�����ƶ��ڵ�

					if (fscanf(fp, "%s %s %s %s %s %s %d %d", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)//��ȡһ�����ݱ����ڵ�ǰ�ڵ�,���ж��Ƿ��д���
					{
						{	//��ʼ�����ÿռ�
							strcpy(node->start_place, "Airport muggle can not found");
							strcpy(node->end_place, "Airport can not be landed at");
							strcpy(node->company, "Hogwarts Co.");
							strcpy(node->flight_num, "HE5972");
							strcpy(node->start_time, "notoday");
							strcpy(node->end_time, "anytime");
							node->people_num = 0;
							node->price = 0;
							node->next_global = NULL;
							node->next_part = NULL;
						}
						break;
					}				
				}
			}
			fclose(fp);//�ر��ļ�
		}
	}
}

//���溽����Ϣ�ļ�
void push_flight_info(void)
{
	flight* node = head_flight;
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
			fprintf(fp, "%s %s %s %s %s %s %d %d\n", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
			node = node->next_global;
		}
	}
	fclose(fp);
}

//��ʾ������Ϣ
void show_flight_info(flight* head)//��Ҫ ��ʾ��������׵�ַ
{
	int i = 0;//����ѭ������
	flight* node = head;//���岢��ʼ����ͨ�ڵ�

	FRMS_title();//�����������Ԥ������ϵͳ��ͷ����
	flight_info_title();//��������������Ԥ������ϵͳ��ͷ����
	flight_info_subtitle();//�����������ʱ�̱����������

	printf("-----------------------------------------------------------------------------------------------------\n");
	while (node->next_global != NULL)
	{
		printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6d|%6d|\n", ++i, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
		node = node->next_global;
	}
	printf("-----------------------------------------------------------------------------------------------------\n");
}

//��ؼ������򺽰���Ϣ
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

	//һ���ؼ���
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
	default: printf("���ݲ�����������ؼ��ִ���\n\a"); return head;
	}

	for (i = 0; i < loop_num - 1; i++)
	{
		node = head;//��ʼ����ͨ�ڵ�
		lag = head;//��ʼ���ͺ�ڵ�
		for (j = 0; j < loop_num - 1 - i; j++)
		{
			buffer = node;//��ʼ������ڵ�

			if (*option_info == 'G' || *option_info == 'H')
			{
				if (*option_info == 'G')bool = ((node->people_num > node->next_global->people_num) == bool_direction);
				if (*option_info == 'H')bool = ((node->price > node->next_global->price) == bool_direction);
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
					if (*option_info == 'G')bool = (node->people_num == node->next_global->people_num);
					if (*option_info == 'H')bool = (node->price == node->next_global->price);
				}
				else
				{
					bool = (strcmp(node->start_place + offset, node->next_global->start_place + offset) == 0);
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














//������������
int main()
{
	char option[9] = { 'A','D','G','B','C','E','H','F' };
	int option_num = 8;
	char direction = 'B';
	int i = 1;

	music();//careful!

	PlaySound(TEXT("Knock Me Out.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	printf("��ȡ����...\n");
	pull_flight_info();
	printf("���ݶ�д�ɹ�\n\n");

	printf("�������...\n");
	show_flight_info(head_flight);
	printf("��������ɹ�\n\n");

	//���ڲ���������
	{
		
		printf("��������...\n");
		head_flight = sort_flight_info(direction, option_num, option, flight_info_num, head_flight);
		printf("����ؼ���:%s\n", option);
		printf("��������ɹ�\n\n");
		

		printf("�������...\n");
		show_flight_info(head_flight);
		printf("��������ɹ�\n\n");

		printf("��������...\n");
		push_flight_info();
		printf("���ݱ���ɹ�\n\n");
	}


	printf("Done\n");

	return 0;
}