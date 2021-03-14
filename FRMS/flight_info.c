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

	fp = fopen("flight_info.txt", "r");//��flight_info.txt�ļ�

	if (fp == NULL)printf("������Ϣ�ļ�ȱʧ��\a\n");//��ʾ�ļ��Ƿ�ȱʧ				//����༭
	else
	{
		flight * node;//������ͨ�ڵ�
		node = (flight*)malloc(sizeof(flight));//����ռ�
		head_flight = node;//����ͷ�ڵ�

		if (node == NULL)printf("�ڴ����ʧ�ܣ�\a\n");//��ʾ�ռ��Ƿ���䲻��		//����༭
		else
		{
			//��һ��¼��
			if (fscanf(fp, "%s %s %s %s %s %s %s %s", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)printf("�ļ���дʧ�ܣ�\a\n");//��ʾ�ļ��Ƿ��д�ɹ�
			//ʣ��¼��
			while (1)
			{
				flight_info_num++;//������Ϣ��������
				node->next = (flight*)malloc(sizeof(flight));//����ռ�

				if (node->next == NULL)printf("�ڴ����ʧ�ܣ�\a\n");//��ʾ�ռ��Ƿ���䲻��//����༭
				else
				{
					end_flight = node;//����β�ڵ�
					node = node->next;//�����ƶ��ڵ�

					if (fscanf(fp, "%s %s %s %s %s %s %s %s", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price) != 8)//��ȡһ�����ݱ����ڵ�ǰ�ڵ�,���ж��Ƿ��д���
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
		printf("|%02d|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", ++i, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
		node = node->next;
	}
	printf("-----------------------------------------------------------------------------------------------------\n");
}

/*
while ((std_in = getchar()) != EOF && std_in != '\n');//�����Ƿ����������������������
*/

//���򺽰���Ϣ�����ؼ��֣�//Ŀǰ�����ֲ��У���������
void sort_flight_info(char option)
{
	int offset;//����ƫ����
	int i, j;//����ѭ����������������

	switch(option)
	{
	case 'A':offset = 0; break;
	case 'B':offset = 32; break;
	case 'C':offset = 64; break;
	case 'D':offset = 80; break;
	case 'E':offset = 88; break;
	case 'F':offset = 96; break;
	case 'G':offset = 104; break;
	case 'H':offset = 112; break;
	default: printf("����ָ��,����������\n\a"); return;
	}


	flight* node, * buffer, * lag;//������ͨ�ڵ㡢����ڵ㡢�ͺ�ڵ�

	for (i = 0; i < flight_info_num-1; i++)
	{
		node = head_flight;//��ʼ����ͨ�ڵ�
		lag = head_flight;//��ʼ���ͺ�ڵ�
		for (j = 0; j < flight_info_num - 1 - i; j++)
		{		
			buffer = node;//��ʼ������ڵ�
			if (strcmp(node->start_place + offset, node->next->start_place + offset) == 1)
			{
				node = node->next;
				buffer->next = node->next;
				node->next = buffer;
				if (j == 0)
				{
					head_flight = node;
					lag = head_flight;//��ʼ���ͺ�ڵ�
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
}


int main()
{
	get_flight_info();
	show_flight_info();
	/*flight* node;
	node = head_flight;
	while (node->next != NULL)
	{
		printf("%s ", node->start_place + 0);
		printf("%s ", node->start_place + 32);
		printf("%s ", node->start_place + 64);
		printf("%s ", node->start_place + 80);
		printf("%s ", node->start_place + 88);
		printf("%s ", node->start_place + 96);
		printf("%s ", node->start_place + 104);
		printf("%s\n", node->start_place + 112);
		node = node->next;
	}*/
	printf("����֮ǰ\n");
	sort_flight_info('F');
	printf("����֮��\n");
	show_flight_info();
	printf("Done\n");
	return 0;
}