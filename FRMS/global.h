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
	char people_num[6];			//����
	char price[6];				//�۸�
	//�������ִ�С112

	struct flight_info* next_global;	//���������������һ����Ա�ĵ�ַ
	struct flight_info* next_part;		//�����ѯ��������һ����Ա�ĵ�ַ

	//ʵ�ʲ��Դ�С120���ֽ�
}flight;

//ȫ�ֱ���ȫ��ͷ�ڵ�Ͳ���ͷ�ڵ�
flight* head_flight_global, * head_flight_part;

flight* secret;

//ȫ�ֱ���������Ϣ����
int flight_info_num,search_flight_info_num;







#endif
