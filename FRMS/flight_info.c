#include<stdio.h>
#include<malloc.h>
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


void get_flight_info(void)//��ȡflight_info.txt������Ϣ
{
	FILE* fp;//�����ļ�ָ��
	fp = fopen("flight_info.txt", "r");//��flight_info.txt�ļ�
	if (fp == NULL)printf("������Ϣȱʧ��\n");//��ʾ�ļ��Ƿ�ȱʧ
	else{
		flight* head, * node, * end;//����ṹ��ͷ�ڵ㡢��ͨ�ڵ㡢β�ڵ�
		node = (flight*)malloc(sizeof(flight));//����ռ�
		head = node;//�����׽ڵ�
		if (node == NULL)printf("�ڴ���䲻�㣡\n");//��ʾ�ռ��Ƿ���䲻��
		else{
			if (fscanf(fp, "%s %s %s %s %s %s %d %d",  node->start_place, node->start_time, node->company, node->flight_num, node->start_time, node->end_time, &node->people_num, &node->price) != 8)printf("���ݶ�д����\n");//��ȡһ�����ݱ����ڵ�ǰ�ڵ㣬����ʾ�Ƿ����ݶ�д����
			else{
			
			}
		}
	}
}

