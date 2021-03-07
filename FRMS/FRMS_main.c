#include<stdio.h>
#include<Windows.h>	//移植代码时请注意！！！
int main(void)
{

	void flight_menu(void);
	void reservation_menu(void);
	void passenger_info(void);
	void admin_menu(void);

	char std_in;	//存储输入区缓存
	int option;		


	printf("\n");	//预留位置，显示错误信息
	while (1)
	{
		
		printf("==========================================\n");
		printf("欢 迎 使 用 飞 机 航 班 预 定 管 理 系 统 \n");
		printf("==========================================\n");
		printf("*         1        航 班 查 询           *\n");
		printf("*         2        预 定 机 票           *\n");
		printf("*         3        旅 客 信 息           *\n");
		printf("*         4        管 理 模 式           *\n");
		printf("*         0        退 出 系 统           *\n");
		printf("==========================================\n");
		printf("     键 入 对 应 数 字 以 访 问 功 能     \n");
		printf("==========================================\n");
		printf("请选择（0-4）：");
		
		scanf_s("%d", &option);
		
		while ((std_in = getchar()) != EOF && std_in != '\n');//清空因非法输入而产生的输入区缓存
		
		switch (option)//功能选择
		{
		case 1:flight_menu(); break;			//航班查询菜单
		case 2:reservation_menu(); break;		//机票预定菜单
		case 3:passenger_info(); break;			//旅客信息菜单
		case 4:admin_menu(); break;				//管理员菜单
		case 0:return 0;
		default: {system("cls"); printf("指令错误,请重新输入\n\a"); } break;
		}
	}
	return 0;
}
