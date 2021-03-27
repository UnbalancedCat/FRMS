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
void bridge_sort_flight_info();//排序函数衔接函数
void refine_search_flight_info(int option_num, char* option_info, char refer_info[][32], flight* head);
void add_flight_info(void);
void modify_flight_info();
void delete_flight_info(void);

void menu();//主菜单
void manager();
void manager_flight_info();//飞机航班
void manager_passager();//旅客信息
void manager_password();//管理员修改
void manager_login();//管理员登录界面
void manager_password_change();//管理员密码修改
void passenger();
void passenger_flight_info();//飞机航班
void passenger_info();//旅客信息
void file_backup();
void file_recover();
void file();

void add_passenger(void);          //添加旅客信息
void delete_passenger(void);       //删除旅客信息
void mend_passenger(void);         //修改旅客信息
void seek_passenger(void);         //查询旅客信息
void read_passenger(void);          //读取旅客信息
void print_passenger(void);         //输出旅客信息
void match_passenger(void);         //匹配旅客电话与密码
int search_passenger(void);

int flag_passenger_login;

#endif	//OUTPUT_H_
