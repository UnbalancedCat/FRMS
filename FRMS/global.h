#pragma once
#ifndef GLOBAL_H_
#define GLOBAL_H_

//������Ϣ�ṹ��
typedef struct flight_info
{

	char start_place[32];	//��ɵ�
	char end_place[32];		//Ŀ�ĵ�
	char company[16];		//���չ�˾
	char flight_num[8];		//�����
	char start_time[8];		//���ʱ��
	char end_time[8];		//����ʱ��
	char people_num[8];			//����
	char price[6];				//�۸�

	struct flight_info* next;	//������һ����ַ

}flight;//ʵ�ʲ��Դ�С124���ֽ�

//ȫ�ֱ���ͷ�ڵ��β�ڵ�
flight* head_flight, * end_flight;

//ȫ�ֱ���������Ϣ����
int flight_info_num;

#endif
