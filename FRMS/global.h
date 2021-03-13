#pragma once
#ifndef _GLOBAL_H
#define _GLOBAL_H

//�������ʱ�̱���ͷ
void flight_info_title(void)
{
	printf("-----------------------------------------------------------------------------------------------------------\n");
	printf("                                               �� �� ʱ �� ��\n");
}

//�������Ԥ������ϵͳ��ͷ
void FRMS_title(void)
{
	printf("-----------------------------------------------------------------------------------------------------------\n\n");
	printf("                  ��        ��        Ԥ        ��        ��        ��        ϵ        ͳ\n\n");
}

//������Ϣ�ṹ��
typedef struct flight_info
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

//ȫ�ֱ���ͷ�ڵ��β�ڵ�
flight* head_flight, * end_flight;

//ȫ�ֱ���������Ϣ����
int flight_info_num;

#endif
