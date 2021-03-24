#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"global.h"//输出类头文件

//菜单函数
void menu()
{
	int begin ;
	while (1)
	{
		begin = 0;
		show_FRMS_title();
		line();
		printf("                                            1.管 理 员 登 录\n");
		printf("                                            2.乘 客 登 录\n");
		printf("                                            3.退 出\n");
		line();
		printf("请输入对应序号访问功能（1-3）：");
		scanf_s("%d", &begin);//等待输入
		if (begin == 1 || begin == 2 || begin == 3)
		{
			switch (begin)
			{
			case 1:system("cls"); manager_login(); break;
			case 2:system("cls"); passenger(); break;
			case 3:return;//退出程序
			}
		}
		else
		{
			system("cls"); printf("请输入合法字符!\n"); 
		}
	}
}
//管理员界面
void manager_login()
{

	char password_real[7];
	char password_shuru[7];
	FILE* fp;
	fp = fopen("password_manager.txt", "r");
	fgets(password_real, 7, fp);
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            管 理 员 登 录\n");
		printf("                                            (按0返回)\n");
		line();
		printf("请输入密码：");
		scanf("%s", password_shuru);
		if (strcmp(password_real, password_shuru) == 0)
		{
			fclose(fp);
			printf("登录成功！\n");
			line();
			system("pause");
			system("cls");
			manager();
			return;
		}
		else
			if (strcmp("0", password_shuru) == 0)
			{
				fclose(fp); system("cls"); return;
			}
			else
			{
				system("cls"); printf("密码错误\n");
			}
	}
}
void manager_password_change()
{
	int i3 = 0;
	int choo_ma_ch;//返回选项
	char password_new[7];
	FILE* xiu;
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            请输入新密码（6位数字或字符）：\n");
		printf("                                            (按0返回)\n");
		scanf("%s", password_new);
		if (strcmp("0", password_new) == 0)
		{
			system("cls"); return;
		}
		else
		{
			if (strlen(password_new) != 6)
			{
				system("cls"); printf("密码长度必须为六位\a\n");
			}
			else
			{
				xiu = fopen("password_manager.txt", "w");
				for (i3 = 0; password_new[i3] != '\0'; i3++)
				{
					fputc(password_new[i3], xiu);
				}
				fclose(xiu);
				printf("密码修改成功\n");
				system("pause");
				system("cls");
				return;

			}
		}
	}
}
void manager()
{
	int begin_manager;//选项
	while (1)
	{
		begin_manager = 0;
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            1.飞 机 航 班\n");
		printf("                                            2.旅 客 信 息\n");
		printf("                                            3.管 理 员 信 息 修 改\n");
		printf("                                            4.数 据 管 理\n");
		printf("                                            5.退 出\n");
		line();
		scanf_s("%d", &begin_manager);//等待输入
		if (begin_manager == 1 || begin_manager == 2 || begin_manager == 3 || begin_manager == 4 || begin_manager == 5)
		{
			switch (begin_manager)
			{
				{
			case 1:system("cls"); manager_flight_info(); break;
			case 2: system("cls"); manager_passager(); break;
			case 3: system("cls"); manager_password(); break;
			case 4: system("cls"); file(); break;
			case 5: system("cls"); return;
				}
			}
		}
		else
		{
			system("cls"); printf("请输入合法字符!\n"); 
		}
	}
}
void manager_flight_info()
{
	//int begin_manager_flight_info = 0;//选项
	char begin_manager_flight_info[3];
	while(1)
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
		printf("                                               6.返 回\n");
		line();
		printf("请输入对应序号访问功能（1-6）：");
		//scanf_s("%d", &begin_manager_flight_info);//等待输入
		gets_s(begin_manager_flight_info, 3);
		if (begin_manager_flight_info[0] == '1' || begin_manager_flight_info[0] == '2' || begin_manager_flight_info[0] == '3' || begin_manager_flight_info[0] == '4' || begin_manager_flight_info[0] == '5' || begin_manager_flight_info[0] == '6')
		{
			switch (begin_manager_flight_info[0])
			{
			case '1':system("cls"); add_flight_info(); break;//航班信息 添加
			case '2':system("cls"); delete_flight_info(); break;//航班信息 删除
			case '3':system("cls"); modify_flight_info(); break;//航班信息 修改
			case '4':system("cls"); bridge_sort_flight_info(); break;//航班信息 排序
			case '5':system("cls"); break;//航班信息 查询
			case '6':system("cls"); return;
			}

		}
		else
		{
			system("cls"); printf("请输入合法字符!\n"); 
		}
	}
}
void manager_passager()
{
	int begin_manager_passager;//选项
	while (1)
	{
		begin_manager_passager = 0;
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                             旅 客 信 息\n");
		line();
		printf("                                               1.添 加\n");
		printf("                                               2.删 除\n");
		printf("                                               3.修 改\n");
		printf("                                               4.查 询\n");
		printf("                                               5.返 回\n");
		line();
		scanf_s("%d", &begin_manager_passager);//等待输入
		if (begin_manager_passager == 1 || begin_manager_passager == 2 || begin_manager_passager == 3 || begin_manager_passager == 4 || begin_manager_passager == 5)
		{
			switch (begin_manager_passager)
			{
			case 1:system("cls"); add_passenger(); break;
			case 2:system("cls"); delete_passenger();  break;
			case 3:system("cls"); mend_passenger();  break;
			case 4:system("cls"); seek_passenger(); break;
			case 5:system("cls"); return;
			}
		}


		else
		{
			system("cls"); printf("请输入合法字符!\n");
		}
	}
}
void manager_password()
{
	int begin_manager_password;//选项
	while (1)
	{
		begin_manager_password = 0;
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            1.密 码 修 改\n");
		printf("                                            2.返 回\n");
		line();
		scanf_s("%d", &begin_manager_password);//等待输入
		if (begin_manager_password == 2 || begin_manager_password == 1)
		{
			switch (begin_manager_password)
			{
			case 1:system("cls"); manager_password_change(); break;
			case 2:system("cls"); return;
			}
		}
		else
		{
			system("cls"); printf("请输入合法字符!\n");
		}
	}
}
void file()
{
	int choo;//选项
	while (1)
	{
		choo = 0;
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                        请选择对文件进行的的操作\n");
		printf("                                               1.备 份\n");
		printf("                                               2.恢 复\n");
		printf("                                               3.返 回\n");
		line();
		scanf("%d", &choo);

		if (choo == 1 || choo == 2 || choo == 3)
		{
			switch (choo)
			{
			case 1:system("cls"); file_backup(); break;
			case 2: system("cls"); file_recover(); break;
			case 3:system("cls"); return;
			}
		}
		else
		{
			system("cls"); printf("请输入合法字符!\n");
		}
	}
}
int file_backup()
{
	int choo_backup;
	char yuan_name[50];//源头文件名
	char bei_name[50];//备份文件名
	char ch;
	while (1)
	{
		printf("请输入要备份的文件名(按0返回）\n");
		scanf("%s", yuan_name);
		if (strcmp(yuan_name, "0") == 0)
		{
			system("cls"); return;
		}
		else
		{
			printf("请输入备份路径\n");
			scanf("%s", bei_name);
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
			return;
		}
	}
}
int file_recover()
{
	int choo_file_recover;
	char bei_ex_name[50];//文件备份名
	char hui_name[50];//要恢复的文件
	char ch;
	while (1)
	{
		printf("请输入文件备份名(按0返回)\n");
		scanf("%s", bei_ex_name);
		if (strcmp(bei_ex_name, "0") == 0)
		{
			system("cls"); return;
		}
		else
		{
			printf("请输入要恢复的文件名\n");
			scanf("%s", hui_name);

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
			return;
		}
	}
}
//旅客界面
void passenger()
{
	int begin_passenger;//选项
	while (1)
	{
		begin_passenger = 0;
		show_FRMS_title();
		line();
		printf("                                            乘 客 模 式\n");
		line();
		printf("                                            1.飞 机 航 班\n");
		printf("                                            2.旅 客 信 息\n");
		printf("                                            3.退 出\n");
		line();
		scanf_s("%d", &begin_passenger);//等待输入
		if (begin_passenger == 1 || begin_passenger == 2 || begin_passenger == 3)
		{
			switch (begin_passenger)
			{
			case 1:system("cls"); passenger_flight_info(); break;
			case 2:system("cls"); passenger_info(); break;
			case 3:system("cls"); return;
			}
		}
		else
		{
			system("cls"); printf("请输入合法字符!\n");
		}
	}
}
void passenger_flight_info()
{
	int begin_passenger_flight_info;//选项
	while (1)
	{
		begin_passenger_flight_info = 0;
		show_FRMS_title();
		line();
		printf("                                            乘 客 模 式\n");
		line();
		printf("                                            1.排 序\n");
		printf("                                            2.查 询\n");
		printf("                                            3.订 票\n");
		printf("                                            4.返 回\n");
		line();
		scanf_s("%d", &begin_passenger_flight_info);//等待输入
		if (begin_passenger_flight_info == 1 || begin_passenger_flight_info == 2 || begin_passenger_flight_info == 3 || begin_passenger_flight_info == 4)
		{
			switch (begin_passenger_flight_info)
			{
			case 1:system("cls"); break;
			case 2:system("cls"); break;
			case 3:system("cls"); break;
			case 4:system("cls"); return;
			}
		}
		else
		{
			system("cls");  printf("请输入合法字符!\n");
		}
	}
}
void passenger_info()
{
	int begin_passenger_info;//选项
	while (1)
	{
		begin_passenger_info = 0;
		show_FRMS_title();
		line();
		printf("                                            乘 客 模 式\n");
		line();
		printf("                                            1.添加\n");
		printf("                                            2.删除\n");
		printf("                                            3.修改\n");
		printf("                                            4.返 回\n");
		line();
		scanf_s("%d", &begin_passenger_info);//等待输入
		if (begin_passenger_info == 1 || begin_passenger_info == 2 || begin_passenger_info == 3 || begin_passenger_info == 4)
		{
			switch (begin_passenger_info)
			{
			case 1:system("cls"); add_passenger(); break;
			case 2:system("cls"); delete_passenger(); break;
			case 3:system("cls"); mend_passenger(); break;
			case 4:system("cls"); return;
			}



		}
		else
		{
			system("cls"); printf("请输入合法字符!\n"); 
		}
	}
}

