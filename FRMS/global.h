#pragma once
#ifndef OUTPUT_H_
#define OUTPUT_H_

#include"flight_info.h"

void init(void);
void backup_files(void);
void line(void);
void show_flight_info_title(void);
void show_FRMS_title(void);
void show_flight_info_subtitle(void);
void show_manager_title(void);
void play_music(void);

void pull_flight_info(void);
void push_flight_info(void);
void show_flight_info(flight* head);
flight* sort_flight_info(char direction, int option_num, char* option_info, int loop_num, flight* head);
void bridge_sort_flight_info();//�������νӺ���
void refine_search_flight_info(int option_num, char* option_info, char refer_info[][32], flight* head);
void add_flight_info(void);
void modify_flight_info();
void delete_flight_info(void);

void menu();//���˵�
void manager();
void manager_flight_info();//�ɻ�����
void manager_passager();//�ÿ���Ϣ
void manager_password();//����Ա�޸�
void manager_login();//����Ա��¼����
void manager_password_change();//����Ա�����޸�
void passenger();
void passenger_flight_info();//�ɻ�����
void passenger_info();//�ÿ���Ϣ
void file_backup();
void file_recover();
void file();

void add_passenger(void);          //����ÿ���Ϣ
void delete_passenger(void);       //ɾ���ÿ���Ϣ
void mend_passenger(void);         //�޸��ÿ���Ϣ
void seek_passenger(void);         //��ѯ�ÿ���Ϣ
void read_passenger(void);          //��ȡ�ÿ���Ϣ
void print_passenger(void);         //����ÿ���Ϣ
void match_passenger(void);         //ƥ���ÿ͵绰������
int search_passenger(void);

int flag_passenger_login;

#endif	//OUTPUT_H_
