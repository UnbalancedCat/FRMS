#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
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
			if (fscanf(fp, "%s %s %s %s %s %s %d %d", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)printf("�ļ���дʧ�ܣ�\a\n");//��ʾ�ļ��Ƿ��д�ɹ�
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
		printf("|%02d|%20s|%20s|%12s|%7s|%8s|%8s|%8d|%6d|\n", ++i, node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
		node = node->next;
	}
	printf("-----------------------------------------------------------------------------------------------------\n");
}

//���򺽰���Ϣ



int main()
{
	get_flight_info();
	show_flight_info();


	return 0;
}