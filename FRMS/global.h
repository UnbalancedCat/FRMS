#pragma once
#ifndef OUTPUT_H_
#define OUTPUT_H_

//变量
typedef struct flight_info//航班信息结构体
{

	char start_place[32];	//始发地
	char end_place[32];		//目的地
	char company[16];		//航空公司
	char flight_num[8];		//航班号
	char start_time[8];		//起飞时间
	char end_time[8];		//到达时间
	char people_num[6];			//载客
	char price[6];				//价格
	//变量部分大小112
	struct flight_info* next_global;	//保存整体的链表下一个成员的地址
	struct flight_info* next_part;		//保存查询后链表下一个成员的地址
	//实际测试大小120个字节
}flight;
flight* head_flight_global, * head_flight_part, * secret_flight_info;//全局变量全局头节点和部分头节点
int flight_info_num, search_flight_info_num;//全局变量航班信息数量
flight* head_flight_passenger;

typedef struct passenger_info//航班信息结构体
{

	char nickname[50];	//用户昵称
	char password[50];	//用户密码
	char name[50];		//姓名
	char id_num[30];	//身份证号
	char phone_num[30];	//联系方式
	//变量部分大小210
	struct passenger_info* next_global;	//保存整体的链表下一个成员的地址
	struct passenger_info* next_part;		//保存查询后链表下一个成员的地址
	//实际测试大小未测试
}passenger;
passenger* head_passenger_global, * head_passenger_part, * secret_passenger_info;//全局变量全局头节点和部分头节点
int passenger_info_num, search_passenger_info_num;//全局变量航班信息数量

//函数
void init(void);
void backup_files(void);
void line(void);
void show_flight_info_title(void);
void show_FRMS_title(void);
void show_flight_info_subtitle(void);
void show_manager_title(void);
void show_passenger_histroy_title(void);
void show_passenger_info_title(void);
void show_passenger_info_subtitle(void);
void play_music(void);

void pull_flight_info(void);
void push_flight_info(void);
void show_flight_info(flight* head);
flight* sort_flight_info(char direction, int option_num, char* option_info, int loop_num, flight* head);
void bridge_sort_flight_info();//排序函数衔接函数
void refine_search_flight_info(int option_num, char* option_info, char refer_info[][32], flight* head);
void bridge_refine_search_sort_flight_info(void);
char passenger_item(flight* fp_person);
void add_flight_info(void);
void modify_flight_info();
void delete_flight_info(void);
void passenger_histroy(void);

void pull_passenger_info(void);
void push_passenger_info(void);
void show_passenger_info(passenger* head);
passenger* sort_passenger_info(char direction, int option_num, char* option_info, int loop_num, passenger* head);
void bridge_sort_passenger_info(void);
void refine_search_passenger_info(int option_num, char* option_info, char refer_info[][50], passenger* head);
void bridge_refine_search_sort_passenger_info(void);
void add_passenger_info(void);
void modify_passenger_info(void);
void delete_passenger_info(void);

void menu(void);//主菜单
void menu_manager(void);
void menu_manager_flight_info(void);//飞机航班
void menu_manager_passager(void);//旅客信息
void menu_manager_password(void);//管理员修改
void menu_manager_login(void);//管理员登录界面
void menu_manager_password_change(void);//管理员密码修改
void menu_passenger(void);
void menu_passenger_flight_info(void);//飞机航班
void menu_passenger_info(void);//旅客信息
void menu_file_backup(void);
void menu_file_backup_auto(void);
void menu_file_backup_to(void);
void menu_file_recover(void);
void menu_file(void);
void menu_passenger_pull(void);

//void add_passenger(void);          //添加旅客信息
//void delete_passenger(void);       //删除旅客信息
//void mend_passenger(void);         //修改旅客信息
//void seek_passenger(void);         //查询旅客信息
//void read_passenger(void);          //读取旅客信息
//void print_passenger(void);         //输出旅客信息
//void match_passenger(void);         //匹配旅客电话与密码
//int search_passenger(void);			//寻找对应的旅客,返回k值，对应Passenger[k]
//void passenger_login(void);			//旅客登录

#endif	//OUTPUT_H_
