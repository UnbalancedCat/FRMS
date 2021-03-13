#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<malloc.h>


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
flight* head, * end;//���干�õ�ͷ�ڵ��β�ڵ�

void get_flight_info(void)//��ȡflight_info.txt������Ϣ
{
	FILE* fp;//�����ļ�ָ��
	fp = fopen("flight_info.txt", "r");//��flight_info.txt�ļ�
	if (fp == NULL)printf("������Ϣȱʧ��\n");//��ʾ�ļ��Ƿ�ȱʧ
	else{
		flight * node;//����ṹ��ͷ�ڵ㡢��ͨ�ڵ㡢β�ڵ�
		node = (flight*)malloc(sizeof(flight));//����ռ�
		head = node;//����ͷ�ڵ�
		if (node == NULL)printf("�ڴ����ʧ�ܣ�\n");//��ʾ�ռ��Ƿ���䲻��
		else{
			if (fscanf(fp, "%s %s %s %s %s %s %d %d", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)printf("�ļ���дʧ�ܣ�\n");
			while (1)
			{
				node->next = (flight*)malloc(sizeof(flight));//����ռ�
				if (node->next == NULL)printf("�ڴ����ʧ�ܣ�\n");//��ʾ�ռ��Ƿ���䲻��
				else {
					end = node;//����β�ڵ�
					node = node->next;//�����ƶ��ڵ�
					if (fscanf(fp, "%s %s %s %s %s %s %d %d", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)//��ȡһ�����ݱ����ڵ�ǰ�ڵ�,���ж��Ƿ��д���
					{
						node = NULL;
						break;
					}
						
				}
			}
			rewind(fp);
		}
	}
}

