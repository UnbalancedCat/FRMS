#pragma once
#ifndef OUTPUT_H_
#define OUTPUT_H_

#include"flight_info.h"

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

void menu();//主菜单
void manager();
void manager_1();//飞机航班
void manager_2();//旅客信息
void manager_3();//管理员修改
void manager_login();//管理员登录界面
void manager_ch();//管理员密码修改
void passenger();
void passenger_1();//飞机航班
void passenger_2();//旅客信息
int beifen();
int huifu();
void wenjian();

int person_passenger(void);
int person_manager(void);
void add_passenger(void);          //添加旅客信息
void delete_passenger(void);       //删除旅客信息
void mend_passenger(void);         //修改旅客信息
void sort_passenger(void);         //排序旅客信息，按身份证号或年龄
void seek_passenger(void);         //查询旅客信息
void read_passenger(void);          //读取旅客信息
void print_passenger(void);         //输出旅客信息
void match_passenger(void);         //匹配旅客电话与密码
void name_sort(void);               //依据旅客姓名排序
void mix_sort(void);                //依据旅客姓名及身份证号排序
int search_passenger(void);        //寻找对应的旅客

#endif	//OUTPUT_H_
