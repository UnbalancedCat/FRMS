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
flight* head_flight_global, * head_flight_part, * secret;//全局变量全局头节点和部分头节点
int flight_info_num, search_flight_info_num;//全局变量航班信息数量

struct Passenger //定义结构体_旅客
{
	char pname[20];	           //姓名
	char pid[20];	           //身份证
	char password[20];	       //密码
	char tell[15];	           //电话
	char count_num[50];        //记录这是第几个旅客
	struct Passenger* pnext;	//保存下一个地址
};
struct Passenger Passenger[50];
int flag_passenger_login;
int located_passenger;

int passenger_flight_info_num;
flight* head_flight_passenger;

//函数
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
char passenger_item(flight* fp_person);
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
void file_backup_auto();
void file_backup_to();
void file_recover();
void file();
void passenger_show();

void add_passenger(void);          //添加旅客信息
void delete_passenger(void);       //删除旅客信息
void mend_passenger(void);         //修改旅客信息
void seek_passenger(void);         //查询旅客信息
void read_passenger(void);          //读取旅客信息
void print_passenger(void);         //输出旅客信息
void match_passenger(void);         //匹配旅客电话与密码
int search_passenger(void);			//寻找对应的旅客,返回k值，对应Passenger[k]
void passenger_login(void);			//旅客登录

#endif	//OUTPUT_H_
