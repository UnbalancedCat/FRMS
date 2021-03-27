#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"global.h"//输出类头文件

extern struct Passenger Passenger[50];

//菜单函数
void menu()
{
	char begin[4];
	while (1)
	{

		show_FRMS_title();
		line();
		printf("                                            1.管 理 员 登 录\n");
		printf("                                            2.乘 客 登 录\n");
		//快速查询界面
		printf("                                            0.退 出\n");
		line();
		printf("请输入对应序号访问功能（0-2）：");
		{
			rewind(stdin);
			fgets(begin, 3, stdin);
			rewind(stdin);
			if ('\n' == begin[strlen(begin) - 1]) begin[strlen(begin) - 1] = 0;
		}
		while (begin[1] != '\0' || (begin[0] != '1' && begin[0] != '2' && begin[0] != '0'))
		{
			printf("含有非法字符，请重新输入！\a\n");
			printf("请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(begin, 3, stdin);
				rewind(stdin);
				if ('\n' == begin[strlen(begin) - 1]) begin[strlen(begin) - 1] = 0;
			}
		}

		switch (begin[0])
		{
		case '1':system("cls"); manager_login(); break;
		case '2':system("cls"); passenger_login(); break;
		case '0':return;//退出程序
		}
	}
}
//管理员界面
void manager_login()
{
	char password_real[8];
	char password_input[8];
	FILE* fp;
	fp = fopen("data\\password_manager.txt", "r");
	fgets(password_real, 7, fp);
	while (1)
	{
		{
			show_FRMS_title();
			show_manager_title();
			line();
			printf("                                            管 理 员 登 录\n");
			printf("                                            (按0返回)\n");
			line();
		}
		printf("请输入密码：");
		{
			rewind(stdin);
			fgets(password_input, 8, stdin);
			rewind(stdin);
			if ('\n' == password_input[strlen(password_input) - 1]) password_input[strlen(password_input) - 1] = 0;
		}
		if (password_input[0] == '0' && password_input[1] == '\0')break;
		while (strcmp(password_input, password_real) != 0)
		{
			printf("密码错误！\a\n");
			printf("请重新输入密码：");
			{
				memset(password_input, 0, sizeof(password_input));
				rewind(stdin);
				fgets(password_input, 8, stdin);
				rewind(stdin);
				if ('\n' == password_input[strlen(password_input) - 1]) password_input[strlen(password_input) - 1] = 0;
			}
			if (password_input[0] == '0' && password_input[1] == '\0')break;
		}
		{
			fclose(fp);
			printf("登录成功！\n");
			line();
			system("pause");
			system("cls");
			manager();
			return;
		}
	}
}
void manager_password_change()
{
	int i3 = 0;
	char password_new[11] = { 0 };
	FILE* xiu;
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            请输入新密码（6位数字或字符）：\n");
		printf("                                            (按0返回)\n");
		//{
			//rewind(stdin);
			//fgets(password_new, 8, stdin);
			//rewind(stdin);
			//if ('\n' == password_new[strlen(password_new) - 1]) password_new[strlen(password_new) - 1] = 0;
		//}
		if (strcmp("0", password_new) == 0)//返回
		{
			system("cls"); return;
		}
		else
		{
			{
				rewind(stdin);
				fgets(password_new, 8, stdin);
				rewind(stdin);
				if ('\n' == password_new[strlen(password_new) - 1]) password_new[strlen(password_new) - 1] = 0;
			}

			while (strlen(password_new) != 6)
			{
				{
					printf("密码长度必须为六位！\n");
					rewind(stdin);
					fgets(password_new, 8, stdin);//检查输入长度
					rewind(stdin);
					if ('\n' == password_new[strlen(password_new) - 1]) password_new[strlen(password_new) - 1] = 0;
				}
			}


			xiu = fopen("data\\password_manager.txt", "w");

			fputs(password_new, xiu);

			fclose(xiu);
			printf("密码修改成功\n");
			system("pause");
			system("cls");
			return;
		}
	}
}
void manager()
{
	char begin_manager[4] = { 0 };//选项
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            1.飞 机 航 班\n");
		printf("                                            2.旅 客 信 息\n");
		printf("                                            3.管 理 员 信 息 修 改\n");
		printf("                                            4.数 据 管 理\n");
		printf("                                            0.退 出\n");
		line();
		printf("请输入对应序号访问功能（0-4）：");
		{
			rewind(stdin);
			fgets(begin_manager, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_manager[strlen(begin_manager) - 1]) begin_manager[strlen(begin_manager) - 1] = 0;
		}
		while (begin_manager[1] != '\0' || (begin_manager[0] < '0' && begin_manager[0] >'4'))
		{
			printf("含有非法字符，请重新输入！\a\n");
			printf("请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(begin_manager, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_manager[strlen(begin_manager) - 1]) begin_manager[strlen(begin_manager) - 1] = 0;
			}
		}
		switch (begin_manager[0])
		{

		case '1':system("cls"); manager_flight_info(); break;
		case '2': system("cls"); manager_passager(); break;
		case '3': system("cls"); manager_password(); break;
		case '4': system("cls"); file(); break;
		case '0': system("cls"); return;

		}

	}
}
void manager_flight_info()
{
	//选项
	char begin_manager_flight_info[4] = { 0 };
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		show_flight_info_title();
		show_flight_info(head_flight_global);
		line();
		printf("                                             飞 机 航 班\n");
		line();
		printf("                                               1.添 加\n");
		printf("                                               2.删 除\n");
		printf("                                               3.修 改\n");
		printf("                                               4.排 序\n");
		printf("                                               5.查 询\n");
		printf("                                               0.返 回\n");
		line();

		printf("请输入对应序号访问功能（0-5）：");
		{
			rewind(stdin);
			fgets(begin_manager_flight_info, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_manager_flight_info[strlen(begin_manager_flight_info) - 1]) begin_manager_flight_info[strlen(begin_manager_flight_info) - 1] = 0;
		}
		while (begin_manager_flight_info[1] != '\0' || (begin_manager_flight_info[0] < '0' && begin_manager_flight_info[0] > '5'))
		{
			printf("含有非法字符，请重新输入！\a\n");
			printf("请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(begin_manager_flight_info, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_manager_flight_info[strlen(begin_manager_flight_info) - 1]) begin_manager_flight_info[strlen(begin_manager_flight_info) - 1] = 0;
			}
		}
		switch (begin_manager_flight_info[0])
		{
		case '1':system("cls"); add_flight_info(); break;//航班信息 添加
		case '2':system("cls"); delete_flight_info(); break;//航班信息 删除
		case '3':system("cls"); modify_flight_info(); break;//航班信息 修改
		case '4':system("cls"); bridge_sort_flight_info(); break;//航班信息 排序
		case '5':system("cls"); bridge_refine_search_sort_flight_info(); break;//航班信息 查询
		case '0':system("cls"); return;
		}

	}
}
void manager_passager()
{
	char begin_manager_passager[4] = { 0 };//选项
	while (1)
	{

		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                             旅 客 信 息\n");
		line();
		printf("                                               1.添 加\n");
		printf("                                               2.删 除\n");
		printf("                                               3.修 改\n");
		printf("                                               4.查 询\n");
		printf("                                               0.返 回\n");
		line();
		printf("请输入对应序号访问功能（0-4）：");
		{
			rewind(stdin);
			fgets(begin_manager_passager, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_manager_passager[strlen(begin_manager_passager) - 1]) begin_manager_passager[strlen(begin_manager_passager) - 1] = 0;
		}
		while (begin_manager_passager[1] != '\0' || (begin_manager_passager[0] < '0' && begin_manager_passager[0] > '4'))
		{
			printf("含有非法字符，请重新输入！\a\n");
			printf("请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(begin_manager_passager, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_manager_passager[strlen(begin_manager_passager) - 1]) begin_manager_passager[strlen(begin_manager_passager) - 1] = 0;
			}
		}
		switch (begin_manager_passager[0])
		{
		case '1':system("cls"); add_passenger(); break;
		case '2':system("cls"); delete_passenger();  break;
		case '3':system("cls"); mend_passenger();  break;
		case '4':system("cls"); seek_passenger(); break;
		case '0':system("cls"); return;
		}

	}
}
void manager_password()
{
	char begin_manager_password[4] = { 0 };//选项
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            1.密 码 修 改\n");
		printf("                                            0.返 回\n");
		line();
		printf("请输入对应序号访问功能（0-1）：");
		{
			rewind(stdin);
			fgets(begin_manager_password, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_manager_password[strlen(begin_manager_password) - 1]) begin_manager_password[strlen(begin_manager_password) - 1] = 0;
		}
		while (begin_manager_password[1] != '\0' || (begin_manager_password[0] != '1' && begin_manager_password[0] != '0'))
		{
			printf("含有非法字符，请重新输入！\a\n");
			printf("请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(begin_manager_password, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_manager_password[strlen(begin_manager_password) - 1]) begin_manager_password[strlen(begin_manager_password) - 1] = 0;
			}
		}
		switch (begin_manager_password[0])
		{
		case '1':system("cls"); manager_password_change(); break;
		case '0':system("cls"); return;
		}

	}
}
void file()
{
	char choo[4] = { 0 };//选项
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                        请选择对文件进行的的操作\n");
		printf("                                               1.备 份\n");
		printf("                                               2.恢 复\n");
		printf("                                               0.返 回\n");
		line();
		printf("请输入对应序号访问功能（0-2）：");
		{
			rewind(stdin);
			fgets(choo, 3, stdin);
			rewind(stdin);
			if ('\n' == choo[strlen(choo) - 1]) choo[strlen(choo) - 1] = 0;
		}
		while (choo[1] != '\0' || (choo[0] != '1' && choo[0] != '2' && choo[0] != '0'))
		{
			printf("含有非法字符，请重新输入！\a\n");
			printf("请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(choo, 3, stdin);
				rewind(stdin);
				if ('\n' == choo[strlen(choo) - 1]) choo[strlen(choo) - 1] = 0;
			}
		}
		switch (choo[0])
		{
		case '1':system("cls"); file_backup(); break;
		case '2': system("cls"); file_recover(); break;
		case '0':system("cls"); return;
		}

	}
}
void file_backup()
{
	char yuan_name[155] = { 0 };//源头文件名
	char bei_name[155] = { 0 };//备份文件名
	char ch;
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("请输入所要备份的文件路径,包含扩展名(按0返回）\n");
		printf("（示例：C:\\Users\\miku\\password_manager.txt）\n");
		{
			rewind(stdin);
			fgets(yuan_name, 150, stdin);
			rewind(stdin);
			if ('\n' == yuan_name[strlen(yuan_name) - 1]) yuan_name[strlen(yuan_name) - 1] = 0;
		}
		if (strcmp(yuan_name, "0") == 0)
		{
			system("cls"); return;
		}
		else
		{
			printf("请输入备份路径\n");
			{
				rewind(stdin);
				fgets(bei_name, 150, stdin);
				rewind(stdin);
				if ('\n' == bei_name[strlen(bei_name) - 1]) bei_name[strlen(bei_name) - 1] = 0;
			}
			FILE* fp1_1 = fopen(yuan_name, "r");//源文件名
			FILE* fp2_1 = fopen(bei_name, "w");//目标文件名

			if (fp1_1 == NULL)
			{
				system("cls");
				printf("找不到指定文件\n");
				return;

			}
			if (fp2_1 == NULL)
			{
				system("cls");
				printf("找不到指定文件\n");//检查文件是否为空
				return;

			}

			//不断的从源文件中读取字符并写入目的文件中，直到遇到EOF结束这个过程
			while ((ch = fgetc(fp1_1)) != EOF)//EOF是文件结束标志
			{
				fputc(ch, fp2_1);
			}
			//关闭流，使用完流后记得关闭，避免占用资源
			fclose(fp1_1);
			fclose(fp2_1);
			printf("备份成功\n");
			system("pause");
			system("cls");
			return;
		}
	}
}
void file_recover()
{

	char bei_ex_name[155] = { 0 };//文件备份名
	char hui_name[155] = { 0 };//要恢复的文件
	char ch;
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("请输入文件备份名(按0返回)\n");
		printf("（示例：C:\\Users\\miku\\password_manager.txt)\n");
		{
			rewind(stdin);
			fgets(bei_ex_name, 150, stdin);
			rewind(stdin);
			if ('\n' == bei_ex_name[strlen(bei_ex_name) - 1]) bei_ex_name[strlen(bei_ex_name) - 1] = 0;
		}
		if (strcmp(bei_ex_name, "0") == 0)
		{
			system("cls"); return;
		}
		else
		{
			printf("请输入要恢复的文件名\n");
			{
				rewind(stdin);
				fgets(hui_name, 150, stdin);
				rewind(stdin);
				if ('\n' == hui_name[strlen(hui_name) - 1]) hui_name[strlen(hui_name) - 1] = 0;
			}

			FILE* fp1 = fopen(bei_ex_name, "r");//文件备份名
			FILE* fp2 = fopen(hui_name, "w");//要恢复的文件

			if (fp1 == NULL)
			{
				system("cls");
				printf("找不到指定文件\n");
				return;
			}
			if (fp2 == NULL)
			{
				system("cls");
				printf("找不到指定文件\n");
				return;
			}

			//不断的从源文件中读取字符并写入目的文件中，直到遇到EOF结束这个过程
			while ((ch = fgetc(fp1)) != EOF)//EOF是文件结束标志
			{
				fputc(ch, fp2);
			}
			//关闭流，使用完流后记得关闭，避免占用资源
			fclose(fp1);
			fclose(fp2);
			printf("恢复成功\n");
			system("pause");
			system("cls");
			return;
		}
	}
}
//旅客界面
void passenger()
{
	char begin_passenger[4] = { 0 };//选项
	while (1)
	{
		show_FRMS_title();
		line();
		printf("                                            乘 客 模 式\n");
		line();
		printf("                                            1.飞 机 航 班\n");
		printf("                                            2.旅 客 信 息\n");
		printf("                                            0.退 出\n");
		line();
		printf("请输入对应序号访问功能（0-2）：");
		{
			rewind(stdin);
			fgets(begin_passenger, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_passenger[strlen(begin_passenger) - 1])  begin_passenger[strlen(begin_passenger) - 1] = 0;
		}
		while (begin_passenger[1] != '\0' || (begin_passenger[0] != '1' && begin_passenger[0] != '2' && begin_passenger[0] != '0'))
		{
			printf("含有非法字符，请重新输入！\a\n");
			printf("请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(begin_passenger, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_passenger[strlen(begin_passenger) - 1])  begin_passenger[strlen(begin_passenger) - 1] = 0;
			}
		}
		switch (begin_passenger[0])
		{
		case '1':system("cls"); passenger_flight_info(); break;
		case '2':system("cls"); passenger_info(); break;
		case '0':system("cls"); return;
		}

	}
}
void passenger_flight_info()
{
	char begin_passenger_flight_info[4] = { 0 };//选项
	while (1)
	{
		show_FRMS_title();
		line();
		printf("                                            乘 客 模 式\n");
		line();
		printf("                                            1.排 序\n");
		printf("                                            2.查 询\n");
		printf("                                            3.订 票\n");
		printf("                                            0.返 回\n");
		line();
		printf("请输入对应序号访问功能（0-3）：");
		{
			rewind(stdin);
			fgets(begin_passenger_flight_info, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_passenger_flight_info[strlen(begin_passenger_flight_info) - 1]) begin_passenger_flight_info[strlen(begin_passenger_flight_info) - 1] = 0;
		}
		while (begin_passenger_flight_info[1] != '\0' || (begin_passenger_flight_info[0] < '0' && begin_passenger_flight_info[0] > '3'))
		{
			printf("含有非法字符，请重新输入！\a\n");
			printf("请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(begin_passenger_flight_info, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_passenger_flight_info[strlen(begin_passenger_flight_info) - 1]) begin_passenger_flight_info[strlen(begin_passenger_flight_info) - 1] = 0;
			}
		}
		switch (begin_passenger_flight_info[0])
		{
		case '1':system("cls"); bridge_sort_flight_info(); break;
		case '2':system("cls"); bridge_refine_search_sort_flight_info(); break;
		case '3':system("cls"); break;
		case '0':system("cls"); return;
		}

	}
}
void passenger_info()
{
	char begin_passenger_info[4] = { 0 };//选项
	while (1)
	{
		show_FRMS_title();
		line();
		printf("                                            乘 客 模 式\n");
		line();
		printf("                                            1.添加\n");
		printf("                                            2.删除\n");
		printf("                                            3.修改\n");
		printf("                                            0.返 回\n");
		line();
		printf("请输入对应序号访问功能（0-3）：");
		{
			rewind(stdin);
			fgets(begin_passenger_info, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_passenger_info[strlen(begin_passenger_info) - 1]) begin_passenger_info[strlen(begin_passenger_info) - 1] = 0;
		}
		while (begin_passenger_info[1] != '\0' || (begin_passenger_info[0] < '0' && begin_passenger_info[0] > '3'))
		{
			printf("含有非法字符，请重新输入！\a\n");
			printf("请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(begin_passenger_info, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_passenger_info[strlen(begin_passenger_info) - 1]) begin_passenger_info[strlen(begin_passenger_info) - 1] = 0;
			}
		}

		switch (begin_passenger_info[0])
		{
		case '1':system("cls"); add_passenger(); break;
		case '2':system("cls"); delete_passenger(); break;
		case '3':system("cls"); mend_passenger(); break;
		case '0':system("cls"); return;
		}
	}
}

