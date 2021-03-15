#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"global.h"//�Զ���ͷ�ļ�
#include"output.h"//�����ͷ�ļ�

//��ȡflight_info.txt������Ϣ
void get_flight_info(void)
{
	flight_info_num = 0;//��ʼ��������Ϣ����
	FILE* fp;//�����ļ�ָ��

	fp = fopen("flight_info.test", "r");//��flight_info.txt�ļ�

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
				node->next = (flight*)malloc(sizeof(flight));//����ռ�

				if (node->next == NULL)
				{
					printf("�ڴ����ʧ�ܣ�\a\n");//��ʾ�ռ��Ƿ���䲻��
					return;//��ֹ����
				}
				else
				{
					end_flight = node;//����β�ڵ�
					node = node->next;//�����ƶ��ڵ�

					if (fscanf(fp, "%s %s %s %s %s %s %d %d", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)//��ȡһ�����ݱ����ڵ�ǰ�ڵ�,���ж��Ƿ��д���
					{
						node->next = NULL;
						break;
					}				
				}
			}
			fclose(fp);//�ر��ļ�
		}
	}
}

//��ʾ������Ϣ
void show_flight_info(void)
{
	int i = 0;//����ѭ������
	flight* node;//������ͨ�ڵ�
	node = head_flight;//��ʼ����ͨ�ڵ�
	
	FRMS_title();//�����������Ԥ������ϵͳ��ͷ����
	flight_info_title();//��������������Ԥ������ϵͳ��ͷ����
	flight_info_subtitle();//�����������ʱ�̱����������

	printf("-----------------------------------------------------------------------------------------------------\n");
	while (node->next != NULL)
	{
		printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6d|%6d|\n", ++i, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
		node = node->next;
	}
	printf("-----------------------------------------------------------------------------------------------------\n");
}

//���򺽰���Ϣ�����ؼ��֣�
flight* sort_flight_info(char direction, int option_num, char* option_info, int loop_num, flight* head)//��Ҫ�ؼ����ַ������׵�ַ�����������Ա���������������׵�ַ ����������׵�ַ
{
	int offset;//����������Առ�ó��Ȼ���ƫ����
	int i, j;//����ѭ������
	_Bool bool;
	flight* node, * buffer, * lag;//������ͨ�ڵ㡢����ڵ㡢�ͺ�ڵ�	

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
	default: printf("����ָ��,����������\n\a"); return head;
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
					lag = head;//��ʼ���ͺ�ڵ�
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
	
	//�����ؼ���
	if (option_num != 1)
	{
		flight* head_next, * buffer_next;//���崫�ݸ�Ƕ�׺����������׵�ַ
		int loop_num_next;//���崫�ݸ�Ƕ�׺����������Ա����
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

				if (bool)//ǰ���ԱԪ�رȶ���ͬ�������ȶ�
				{
					node = node->next;
					loop_num_next += 1;
				}
				else//ǰ���ԱԪ�ضԱȲ�ͬ����¼����ʼ�����ؼ�������,����������������ѭ��
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












//������������
int main()
{
	char option[9] = { 'F','H' };
	int option_num = 2;
	char direction = 'A';//δ����
	int i = 1;

	get_flight_info();
	show_flight_info();

	//���ڲ���������
	while (i--)
	{
		
		printf("##����֮ǰ##\n");
		
		head_flight = sort_flight_info(direction, option_num, option, flight_info_num, head_flight);
		
		
		printf("##����֮��##\n");
		printf("##����ؼ���:%s##\n", option);

		show_flight_info();
	}
	
	printf("##Done##\n");

	return 0;
}