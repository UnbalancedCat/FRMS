#pragma once
#ifndef OUTPUT_H_
#define OUTPUT_H_

#include"flight_info.h"



void init(void);
void line(void);
void show_flight_info_title(void);
void show_FRMS_title(void);
void show_flight_info_subtitle(void);
void show_manager_title(void);

void pull_flight_info(void);
void push_flight_info(void);
void show_flight_info(flight* head);
flight* sort_flight_info(char direction, int option_num, char* option_info, int loop_num, flight* head);
void refine_search_flight_info(int option_num, char* option_info, char refer_info[][32], flight* head);
void add_flight_info(void);
void modify_flight_info();
void delete_flight_info(void);

void menu();//���˵�
void manager();
void manager_1();//�ɻ�����
void manager_2();//�ÿ���Ϣ
void manager_3();//����Ա�޸�
void manager_login();//����Ա��¼����
void manager_ch();//����Ա�����޸�
void passenger();
void passenger_1();//�ɻ�����
void passenger_2();//�ÿ���Ϣ
int beifen();
int huifu();
void wenjian();

int person_passenger(void);
int person_manager(void);
void add_passenger(void);          //����ÿ���Ϣ
void delete_passenger(void);       //ɾ���ÿ���Ϣ
void mend_passenger(void);         //�޸��ÿ���Ϣ
void seek_passenger(void);         //��ѯ�ÿ���Ϣ
void read_passenger(void);          //��ȡ�ÿ���Ϣ
void print_passenger(void);         //����ÿ���Ϣ
void match_passenger(void);         //ƥ���ÿ͵绰������
int search_passenger(void);

#endif	//OUTPUT_H_
