#pragma once
#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <time.h>
time_t timep;
struct tm* init_time;
char get_time[8];
char flight_info_path[50];
//����
typedef struct flight_info//������Ϣ�ṹ��
{

	char start_place[32];	//ʼ����
	char end_place[32];		//Ŀ�ĵ�
	char company[16];		//���չ�˾
	char flight_num[8];		//�����
	char start_time[8];		//���ʱ��
	char end_time[8];		//����ʱ��
	char people_num[6];		//��λ
	char price[6];			//�۸�
	//�������ִ�С112
	struct flight_info* next_global;	//���������������һ����Ա�ĵ�ַ
	struct flight_info* next_part;		//�����ѯ��������һ����Ա�ĵ�ַ
	//ʵ�ʲ��Դ�С120���ֽ�
}flight;
flight* head_flight_global, * head_flight_part, * secret_flight_info;//ȫ�ֱ���ȫ��ͷ�ڵ�Ͳ���ͷ�ڵ�
int flight_info_num, search_flight_info_num;//ȫ�ֱ���������Ϣ����
flight* located_flight_info_global;

typedef struct passenger_info//�ÿ���Ϣ�ṹ��
{

	char nickname[50];	//�û���
	char password[50];	//�û�����
	char name[50];		//����
	char id_num[30];	//���֤��
	char phone_num[30];	//��ϵ��ʽ
	//�������ִ�С210
	struct passenger_info* next_global;		//���������������һ����Ա�ĵ�ַ
	struct passenger_info* next_part;		//�����ѯ��������һ����Ա�ĵ�ַ
	//ʵ�ʲ��Դ�Сδ����
}passenger;
passenger* head_passenger_global, * head_passenger_part, * secret_passenger_info;//ȫ�ֱ���ȫ��ͷ�ڵ�Ͳ���ͷ�ڵ�
int passenger_info_num, search_passenger_info_num;//ȫ�ֱ����ÿ���Ϣ����
passenger* located_passenger_info_global;



//����
void init(void);
void full_screen(void);
void shut_down(void);
void line(void);
void show_flight_info_title(void);
void show_FRMS_title(void);
void show_flight_info_subtitle(void);
void show_manager_title(void);
void show_passenger_histroy_title(void);
void show_passenger_title(void);
void show_passenger_info_title(void);
void show_passenger_info_subtitle(void);
void play_music(void);

void pull_flight_info(void);
void push_flight_info(void);
void show_flight_info(flight* head);
flight* sort_flight_info(char direction, int option_num, char* option_info, int loop_num, flight* head);
void bridge_sort_flight_info();//�������νӺ���
void refine_search_flight_info(int option_num, char* option_info, char refer_info[][32], flight* head);
void bridge_refine_search_sort_flight_info(void);
void passenger_item(flight* fp_person);
void add_flight_info(void);
void modify_flight_info();
void delete_flight_info(void);
void reserve_flight_ticket(void);
void menu_passenger_histroy(void);

void login_passenger(void);
void pull_passenger_info(void);
void push_passenger_info(void);
void show_passenger_info(passenger* head);
passenger* sort_passenger_info(char direction, int option_num, char* option_info, int loop_num, passenger* head);
void bridge_sort_passenger_info(void);
void refine_search_passenger_info(int option_num, char* option_info, char refer_info[][50], passenger* head);
void bridge_refine_search_sort_passenger_info(void);
void add_passenger_info(void);
void modify_passenger_info(void);
void modify_passenger_info_passenger(void);
void delete_passenger_info(void);

void menu(void);//���˵�
void menu_manager(void);
void menu_manager_flight_info(void);//�ɻ�����
void menu_manager_passager(void);//�ÿ���Ϣ
void menu_manager_password(void);//����Ա�޸�
void menu_manager_login(void);//����Ա��¼����
void menu_manager_password_change(void);//����Ա�����޸�
void menu_passenger(void);
void menu_passenger_flight_info(void);//�ɻ�����
void menu_passenger_info(void);//�ÿ���Ϣ
void menu_file_backup(void);
void menu_file_backup_auto(void);
void menu_file_backup_to(void);
void menu_file_recover_to(void);
void menu_file(void);
void menu_passenger_pull(void);
void menu_file_recover(void);

#endif //GLOBAL_H_
