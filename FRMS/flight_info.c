#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<malloc.h>
#include"global.h"

typedef struct flight_info//������Ϣ�ṹ��
{

	char start_place[32];	//��ɵ�
	char end_place[32];		//Ŀ�ĵ�
	char company[16];		//���չ�˾
	char flight_num[8];		//�����
	char start_time[8];		//���ʱ��
	char end_time[8];		//����ʱ��
	int people_num;			//����
	int price;				//�۸�

	struct flight_info* next;	//������һ����ַ

}flight;//ʵ�ʲ���ռ��116�ֽ�

flight* head_flight, * end_flight;//ȫ�ֱ���ͷ�ڵ��β�ڵ�
int flight_info_num;//ȫ�ֱ���������Ϣ����

void get_flight_info(void)//��ȡflight_info.txt������Ϣ
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
						node = NULL;
						break;
					}				
				}
			}
			fclose(fp);//�ر��ļ�
		}
	}
}

void show_flight_info(void)//��ʾ������Ϣ
{
	int i;//����ѭ������
	flight* node;//������ͨ�ڵ�
	node = head_flight;//��ʼ����ͨ�ڵ�

	printf("|%23s|%23s|%12s|%8s|%8s|%8s|%8s|%6s\n", "ʼ����", "Ŀ�ĵ�", "���չ�˾",  "�����" ,"���ʱ��", "����ʱ��", "��������", "Ʊ��");
	for (i = 0; i < flight_info_num; i++)
	{
		printf("|%23s|%23s|%12s|%8s|%8s|%8s|%8d|%6d\n", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price);
		node = node->next;
	}
}

int main()
{
	get_flight_info();
	show_flight_info();
	return 0;
}