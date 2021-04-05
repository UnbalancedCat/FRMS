#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"global.h"

//菜单函数
void menu(void)
{
	char begin[4];
	while (1)
	{
		system("cls");
		show_FRMS_title();
		line();
	    printf("\n                                                                       1. 管 理 员 登 录\n\n");
		printf("                                                                       2. 乘 客 登 录\n\n");
		printf("                                                                       0. 退 出\n\n");
		line();
		printf("                             |请输入对应序号访问功能（0-2）：");
		{
			rewind(stdin);
			fgets(begin, 3, stdin);
			rewind(stdin);
			if ('\n' == begin[strlen(begin) - 1]) begin[strlen(begin) - 1] = 0;
		}
		while (begin[1] != '\0' || (begin[0] != '1' && begin[0] != '2' && begin[0] != '0'))
		{
			printf("                             |含有非法字符，请重新输入！\a\n");
			printf("                             |请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(begin, 3, stdin);
				rewind(stdin);
				if ('\n' == begin[strlen(begin) - 1]) begin[strlen(begin) - 1] = 0;
			}
		}

		switch (begin[0])
		{
		case '1':system("cls"); menu_manager_login(); break;
		case '2':system("cls"); login_passenger(); break;
		case '0':return;//退出程序
		}
	}
}
//管理员界面
void menu_manager_login(void)
{
	char password_real[8];
	char password_input[8];
	FILE* fp;
	fp = fopen("data\\password_manager.txt", "r");
	fgets(password_real, 7, fp);
	while (1)
	{
		system("cls");
		{
			show_FRMS_title();
			line();
			printf("\n                                                                        管 理 员 登 录\n\n");
			line();
		}
		printf("                             |键入c取消输入，返回上级菜单！\n");
		printf("                             |请输入密码：");
		{
			rewind(stdin);
			fgets(password_input, 8, stdin);
			rewind(stdin);
			if ('\n' == password_input[strlen(password_input) - 1]) password_input[strlen(password_input) - 1] = 0;
		}
		if (password_input[0] == 'c' && password_input[1] == '\0')break;
		while (strcmp(password_input, password_real) != 0)
		{
			printf("                             |密码错误！\a\n");
			printf("                             |请重新输入密码：");
			{
				memset(password_input, 0, sizeof(password_input));
				rewind(stdin);
				fgets(password_input, 8, stdin);
				rewind(stdin);
				if ('\n' == password_input[strlen(password_input) - 1]) password_input[strlen(password_input) - 1] = 0;
			}
			if (password_input[0] == 'c' && password_input[1] == '\0')break;
		}
		{
			fclose(fp);
			printf("                             |登录成功！\n");
			line();
			printf("                             |");
			system("pause");
			system("cls");
			menu_manager();
			return;
		}
	}
	system("cls");
}
void menu_manager_password_change(void)
{
	int i3 = 0;
	int i4 = 0,j1=0;//检查输入
	char password_new[11] = { 0 };
	FILE* xiu;
	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                             |请输入新密码(按0返回)：");
		{
			rewind(stdin);
			fgets(password_new, 8, stdin);
		    rewind(stdin);
			if ('\n' == password_new[strlen(password_new) - 1]) password_new[strlen(password_new) - 1] = 0;
		}
		
		if (strcmp("0", password_new) == 0)//返回
		{
			system("cls"); return;
		}
		else
		{
			
			for (i4 = 0; i4 < 6; i4++)
			{
			
				if (password_new[i4] < '0' || password_new[i4] > '9')
				{
					j1++;
				}
			}

			while (strlen(password_new) != 6 || j1 != 0)
			{
				{
					printf("                             |密码必须为六位数字!\a\n");
					printf("                             |请输入新密码(按0返回)：");

					rewind(stdin);
					fgets(password_new, 8, stdin);//检查输入长度
					rewind(stdin);
					if ('\n' == password_new[strlen(password_new) - 1]) password_new[strlen(password_new) - 1] = 0;
				}
				if (strcmp("0", password_new) == 0)//返回
				{
					system("cls"); return;
				}
				j1 = 0;
				for (i4 = 0; i4 < 6; i4++)
				{
					
					if (password_new[i4] < '0' || password_new[i4] > '9')
					{
						j1++;
					}
				}
			}
			
			{

				xiu = fopen("data\\password_manager.txt", "w");

			    fputs(password_new, xiu);

			    fclose(xiu);
			    printf("                             |密码修改成功\n");
				printf("                             |");
				system("pause");
			    system("cls");
			    return;
		     }
		}	
	}
}
void menu_manager(void)
{
	char begin_manager[4];//选项
	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                                                        1. 航 班 信 息\n");
		printf("                                                                        2. 旅 客 信 息\n");
		printf("                                                                        3. 管 理 员 信 息 修 改\n");
		printf("                                                                        4. 数 据 管 理\n");
		printf("                                                                        0. 退 出\n");
		line();
		printf("                             |请输入对应序号访问功能（0-4）：");
		{
			rewind(stdin);
			fgets(begin_manager, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_manager[strlen(begin_manager) - 1]) begin_manager[strlen(begin_manager) - 1] = 0;
		}
		while (begin_manager[1] != '\0' || (begin_manager[0] < '0' || begin_manager[0] >'4'))
		{
			printf("                             |含有非法字符，请重新输入！\a\n");
			printf("                             |请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(begin_manager, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_manager[strlen(begin_manager) - 1]) begin_manager[strlen(begin_manager) - 1] = 0;
			}
		}
		switch (begin_manager[0])
		{

		case '1':system("cls");  menu_manager_flight_info(); break;
		case '2': system("cls"); menu_manager_passager(); break;
		case '3': system("cls"); menu_manager_password(); break;
		case '4': system("cls"); menu_file(); break;
		case '0': system("cls"); return;
		}

	}
}
void menu_manager_flight_info(void)
{
	//选项
	char begin_manager_flight_info[4] = { 0 };
	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_flight_info_title();
		show_flight_info(head_flight_global);
		show_manager_title();
		line();
		printf("                                                                          航 班 信 息\n");
		line();
		printf("                                                                           1. 添 加\n");
		printf("                                                                           2. 删 除\n");
		printf("                                                                           3. 修 改\n");
		printf("                                                                           4. 排 序\n");
		printf("                                                                           5. 查 询\n");
		printf("                                                                           0. 返 回\n");
		line();

		printf("                             |请输入对应序号访问功能（0-5）：");
		{
			rewind(stdin);
			fgets(begin_manager_flight_info, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_manager_flight_info[strlen(begin_manager_flight_info) - 1]) begin_manager_flight_info[strlen(begin_manager_flight_info) - 1] = 0;
		}
		while (begin_manager_flight_info[1] != '\0' || (begin_manager_flight_info[0] < '0' || begin_manager_flight_info[0] > '5'))
		{
			printf("                             |含有非法字符，请重新输入！\a\n");
			printf("                             |请输入对应序号访问功能（0-2）：");
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
void menu_manager_passager(void)
{
	char begin_manager_passager[4] = { 0 };//选项
	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_passenger_info_title();
		show_passenger_info(head_passenger_global);
		show_manager_title();
		line();
		printf("                                                                           1. 添 加\n");
		printf("                                                                           2. 删 除\n");
		printf("                                                                           3. 修 改\n");
		printf("                                                                           4. 排 序\n");
		printf("                                                                           5. 查 询\n");
		printf("                                                                           0. 返 回\n");
		line();
		printf("                             |请输入对应序号访问功能（0-5）：");
		{
			rewind(stdin);
			fgets(begin_manager_passager, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_manager_passager[strlen(begin_manager_passager) - 1]) begin_manager_passager[strlen(begin_manager_passager) - 1] = 0;
		}
		while (begin_manager_passager[1] != '\0' || (begin_manager_passager[0] < '0' || begin_manager_passager[0] > '5'))
		{
			printf("                             |含有非法字符，请重新输入！\a\n");
			printf("                             |请输入对应序号访问功能（0-5）：");
			{
				rewind(stdin);
				fgets(begin_manager_passager, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_manager_passager[strlen(begin_manager_passager) - 1]) begin_manager_passager[strlen(begin_manager_passager) - 1] = 0;
			}
		}
		switch (begin_manager_passager[0])
		{
		case '1':system("cls"); add_passenger_info(); break;
		case '2':system("cls"); delete_passenger_info();  break;
		case '3':system("cls"); modify_passenger_info();  break;
		case '4':system("cls"); bridge_sort_passenger_info(); break;
		case '5':system("cls"); bridge_refine_search_sort_passenger_info(); break;
		case '0':system("cls"); return;
		}

	}
}
void menu_manager_password(void)
{
	char begin_manager_password[4] = { 0 };//选项
	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                                                        1. 密 码 修 改\n");
		printf("                                                                        0. 返 回\n");
		line();
		printf("                             |请输入对应序号访问功能（0-1）：");
		{
			rewind(stdin);
			fgets(begin_manager_password, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_manager_password[strlen(begin_manager_password) - 1]) begin_manager_password[strlen(begin_manager_password) - 1] = 0;
		}
		while (begin_manager_password[1] != '\0' || (begin_manager_password[0] != '1' && begin_manager_password[0] != '0'))
		{
			printf("                             |含有非法字符，请重新输入！\a\n");
			printf("                             |请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(begin_manager_password, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_manager_password[strlen(begin_manager_password) - 1]) begin_manager_password[strlen(begin_manager_password) - 1] = 0;
			}
		}
		switch (begin_manager_password[0])
		{
		case '1':system("cls");	menu_manager_password_change(); break;
		case '0':system("cls"); return;
		}

	}
}
void menu_file(void)
{
	char choo[4] = { 0 };//选项
	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                                                        1. 备 份 全 局 文 件\n");
		printf("                                                                        2. 自 定 义 备 份\n");
		printf("                                                                        3. 恢 复 全 局 文 件\n");
		printf("                                                                        4. 自 定 义 恢 复\n");
		printf("                                                                        0. 返 回\n");
		line();
		printf("                             |请输入对应序号访问功能（0-3）：");
		{
			rewind(stdin);
			fgets(choo, 3, stdin);
			rewind(stdin);
			if ('\n' == choo[strlen(choo) - 1]) choo[strlen(choo) - 1] = 0;
		}
		while (choo[1] != '\0' || (choo[0] != '1' && choo[0] != '2' &&choo[0] != '3' && choo[0] != '4' && choo[0] != '0'))
		{
			printf("                             |含有非法字符，请重新输入！\a\n");
			printf("                             |请输入对应序号访问功能（0-3）：");
			{
				rewind(stdin);
				fgets(choo, 3, stdin);
				rewind(stdin);
				if ('\n' == choo[strlen(choo) - 1]) choo[strlen(choo) - 1] = 0;
			}
		}
		switch (choo[0])
		{
		case '1':system("cls"); menu_file_backup(); break;
		case '2': system("cls"); menu_file_backup_to(); break;
		case '3': system("cls"); menu_file_recover(); break;
		case '4':system("cls"); menu_file_recover_to(); break;
		case '0':system("cls"); return;
		}

	}
}
void menu_file_backup_to(void)
{
	char yuan_name[155] = { 0 };//源头文件名
	char bei_name[155] = { 0 };//备份文件名
	char ch;
	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                             |示例：data\\file_name.txt\n");
		printf("                             |请输入所要备份的文件路径,包含扩展名(按c取消操作）：");
		
		{
			rewind(stdin);
			fgets(yuan_name, 150, stdin);
			rewind(stdin);
			if ('\n' == yuan_name[strlen(yuan_name) - 1]) yuan_name[strlen(yuan_name) - 1] = 0;
		}
		//if (strcmp(yuan_name, "0") == 0)
		//{
			//system("cls"); return;
		//}
		if (yuan_name[0] == 'c' && yuan_name[1] == '\0')
		{
			line();
			printf("                             |取消成功！\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
		else
		{
			printf("                             |示例：backup\\file_name.txt\n");
			printf("                             |请输入备份路径(按c取消操作）：");
			{
				rewind(stdin);
				fgets(bei_name, 150, stdin);
				rewind(stdin);
				if ('\n' == bei_name[strlen(bei_name) - 1]) bei_name[strlen(bei_name) - 1] = 0;
			}
			if (bei_name[0] == 'c' && bei_name[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			FILE* fp1_1 = fopen(yuan_name, "r");//源文件名
			FILE* fp2_1 = fopen(bei_name, "w");//目标文件名

			if (fp1_1 == NULL)
			{
				printf("                             |找不到指定文件!\a\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;

			}
			if (fp2_1 == NULL)
			{
				
				printf("                             |找不到指定文件!\a\n");
				printf("                             |");
				system("pause");
				system("cls");
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
			printf("                             |备份成功\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
	}
}
void menu_file_backup(void)
{
	push_flight_info();
	push_passenger_info();
	char ch;
	while(1)
	{
		system("cls");
		show_FRMS_title();
		show_manager_title();
		line();
		FILE* fp1_2 = fopen("data\\passenger_info.txt", "r");
		FILE* fp1_3 = fopen("data\\password_manager.txt", "r");
		
		if (fp1_2 == NULL|| fp1_3 == NULL )
		{
			system("cls");
			printf("                             |找不到指定文件!\a\n");
			return;
		}
		else
		{
			system("copy .\\data\\flight_info\\ .\\backup\\flight_info\\");
			FILE* fp2_2 = fopen("backup\\passenger_info.txt", "w");
			while ((ch = fgetc(fp1_2)) != EOF)//2
			{
				fputc(ch, fp2_2);
			}
			fclose(fp1_2);
			fclose(fp2_2);

			FILE* fp2_3 = fopen("backup\\password_manager.txt", "w");
			while ((ch = fgetc(fp1_3)) != EOF)//3
			{
				fputc(ch, fp2_3);
			}
			fclose(fp1_3);
			fclose(fp2_3);

			system("cls");
			show_FRMS_title();
			show_manager_title();
			line();
			printf("                             |已备份至 backup 文件夹!\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
		
	}

	
}
void menu_file_recover(void)
{
	char ch;
	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_manager_title();
		line();

		FILE* fp1_2 = fopen("backup\\passenger_info.txt", "r");//单独拷贝passenger_info
		FILE* fp1_3 = fopen("backup\\password_manager.txt", "r");//password_manager

		if ( fp1_2 == NULL || fp1_3 == NULL)
		{
			system("cls");
			printf("                             |找不到指定文件!\a\n");
			return;

		}
		else
		{
			system("copy .\\backup\\flight_info\\ .\\data\\flight_info\\");
			FILE* fp2_2 = fopen("data\\passenger_info.txt", "w");
			while ((ch = fgetc(fp1_2)) != EOF)//2
			{
				fputc(ch, fp2_2);
			}
			fclose(fp1_2);
			fclose(fp2_2);

			FILE* fp2_3 = fopen("data\\password_manager.txt", "w");
			while ((ch = fgetc(fp1_3)) != EOF)//3
			{
				fputc(ch, fp2_3);
			}
			fclose(fp1_3);
			fclose(fp2_3);

			system("cls");
			show_FRMS_title();
			show_manager_title();
			line();
			printf("                             |已恢复至 data 文件夹!\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}

	}
	pull_flight_info();
	pull_passenger_info();
}
void menu_file_backup_auto(void)
{
	push_flight_info();
	push_passenger_info();
	system("copy .\\data .\\backup");
	printf("                             |自动备份成功!\n");
}
void menu_file_recover_to(void)
{

	char bei_ex_name[155] = { 0 };//文件备份名
	char hui_name[155] = { 0 };//要恢复的文件
	char ch;
	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                             |示例：backup\\file_name.txt\n");
		printf("                             |请输入已备份文件路径(按c取消操作)：");

		{
			rewind(stdin);
			fgets(bei_ex_name, 150, stdin);
			rewind(stdin);
			if ('\n' == bei_ex_name[strlen(bei_ex_name) - 1]) bei_ex_name[strlen(bei_ex_name) - 1] = 0;
		}
		if (bei_ex_name[0] == 'c' && bei_ex_name[1] == '\0')
		{
			line();
			printf("                             |取消成功！\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
		else
		{
			printf("                             |示例：data\\file_name.txt\n");
			printf("                             |请输入需恢复文件路径(按c取消操作)：");
			{
				rewind(stdin);
				fgets(hui_name, 150, stdin);
				rewind(stdin);
				if ('\n' == hui_name[strlen(hui_name) - 1]) hui_name[strlen(hui_name) - 1] = 0;
			}
			if (hui_name[0] == 'c' && hui_name[1] == '\0')
			{
				line();
				printf("                             |取消成功！\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}

			FILE* fp1 = fopen(bei_ex_name, "r");//文件备份名
			FILE* fp2 = fopen(hui_name, "w");//要恢复的文件

			if (fp1 == NULL)
			{
		
	
				printf("                             |找不到指定文件!\a\n");
				printf("                             |");
				system("pause");
				system("cls");
				return;
			}
			if (fp2 == NULL)
			{
				
				printf("                             |找不到指定文件!\a\n");
				printf("                             |");
				system("pause");
				system("cls");
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
			printf("                             |恢复成功\n");
			printf("                             |");
			system("pause");
			system("cls");
			return;
		}
	}
}
//旅客界面
void menu_passenger(void)
{
	char begin_passenger[4] = { 0 };//选项
	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_passenger_title();
		line();
		printf("                                                                        1. 航 班 信 息\n");
		printf("                                                                        2. 旅 客 信 息\n");
		printf("                                                                        0. 退 出\n");
		line();
		printf("                             |请输入对应序号访问功能（0-2）：");
		{
			rewind(stdin);
			fgets(begin_passenger, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_passenger[strlen(begin_passenger) - 1])  begin_passenger[strlen(begin_passenger) - 1] = 0;
		}
		while (begin_passenger[1] != '\0' || (begin_passenger[0] != '1' && begin_passenger[0] != '2' && begin_passenger[0] != '0'))
		{
			printf("                             |含有非法字符，请重新输入！\a\n");
			printf("                             |请输入对应序号访问功能（0-2）：");
			{
				rewind(stdin);
				fgets(begin_passenger, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_passenger[strlen(begin_passenger) - 1])  begin_passenger[strlen(begin_passenger) - 1] = 0;
			}
		}
		switch (begin_passenger[0])
		{
		case '1':system("cls"); menu_passenger_flight_info(); break;
		case '2':system("cls"); menu_passenger_info(); break;
		case '0':system("cls"); located_passenger_info_global = NULL; located_flight_info_global = NULL; return;
		}

	}
}
void menu_passenger_flight_info(void)
{
	char begin_passenger_flight_info[4] = { 0 };//选项
	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_flight_info_title();
		show_flight_info(head_flight_global);
		show_passenger_title();
		line();
		printf("                                                                          1. 排 序\n");
		printf("                                                                          2. 查 询\n");
		printf("                                                                          3. 订 票\n");
		printf("                                                                          4. 历 史 订 单\n");
		printf("                                                                          0. 返 回\n");
		line();
		printf("                             |请输入对应序号访问功能（0-3）：");
		{
			rewind(stdin);
			fgets(begin_passenger_flight_info, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_passenger_flight_info[strlen(begin_passenger_flight_info) - 1]) begin_passenger_flight_info[strlen(begin_passenger_flight_info) - 1] = 0;
		}
		while (begin_passenger_flight_info[1] != '\0' || (begin_passenger_flight_info[0] < '0' || begin_passenger_flight_info[0] > '4'))
		{
			printf("                             |含有非法字符，请重新输入！\a\n");
			printf("                             |请输入对应序号访问功能（0-2）：");
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
		case '3':system("cls"); reserve_flight_ticket(); break;
		case '4':system("cls"); menu_passenger_histroy(); break;
		case '0':system("cls"); return;
		}

	}
}
void menu_passenger_info(void)
{
	char begin_passenger_info[4] = { 0 };//选项
	while (1)
	{
		system("cls");
		show_FRMS_title();
		show_passenger_title();
		show_passenger_info_subtitle();
		line();
		printf("                             |  |%20s|%20s|%12s|%23s|%17s|\n", located_passenger_info_global->nickname, located_passenger_info_global->password, located_passenger_info_global->name, located_passenger_info_global->id_num, located_passenger_info_global->phone_num);
		line();
		printf("                                                                           1. 修 改\n");
		printf("                                                                           0. 返 回\n");
		line();
		printf("                             |请输入对应序号访问功能（0-1）：");
		{
			rewind(stdin);
			fgets(begin_passenger_info, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_passenger_info[strlen(begin_passenger_info) - 1]) begin_passenger_info[strlen(begin_passenger_info) - 1] = 0;
		}
		while (begin_passenger_info[1] != '\0' || (begin_passenger_info[0] < '0' || begin_passenger_info[0] > '1'))
		{
			printf("                             |含有非法字符，请重新输入！\a\n");
			printf("                             |请输入对应序号访问功能（0-1）：");
			{
				rewind(stdin);
				fgets(begin_passenger_info, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_passenger_info[strlen(begin_passenger_info) - 1]) begin_passenger_info[strlen(begin_passenger_info) - 1] = 0;
			}
		}

		switch (begin_passenger_info[0])
		{
		case '1':system("cls"); modify_passenger_info_passenger(); break;
		case '0':system("cls"); return;
		}
	}
}
void menu_passenger_pull(void)
{
	char he[13] = { "data\\users\\" };//名尾巴
	char tail[8] = { ".txt" };//名头
	char total_file[120] = { 0 };//文件名，大点
	strcat(total_file, he);//接头
	strcat(total_file, located_passenger_info_global->nickname);//中间
	//strcat(total_file, "BHK");
	strcat(total_file, tail);//接尾
	FILE* fp = fopen(total_file, "r");//file pointer

	if (fp == NULL)
	{
		printf("                             |用户历史订票信息文件缺失！\a\n");//提示文件是否缺失
		return;
	}
	else
	{
		flight* node;//定义普通节点
		node = (flight*)malloc(sizeof(flight));//分配空间
		located_flight_info_global = node;//保存节点

		if (node == NULL)
		{
			printf("                             |内存分配失败！\a\n");//提示空间是否分配不足
			return;//中止函数
		}
		else
		{
			//第一次录入
			if (fscanf(fp, "%s %s %s %s %s %s %s %s", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price) != 8)
			{
				printf("                             |文件读写失败！\a\n");//提示文件是否读写成功
				return;//中止函数
			}
			//剩余录入
			while (1)
			{
				node->next_global = (flight*)malloc(sizeof(flight));//分配空间
				node->next_part = node->next_global;
				if (node->next_global == NULL)
				{
					printf("                             |内存分配失败！\a\n");//提示空间是否分配不足
					return;//中止函数
				}
				else
				{
					node = node->next_global;//向下移动节点

					if (fscanf(fp, "%s %s %s %s %s %s %s %s", node->start_place, node->end_place, node->company, node->flight_num, node->start_time, node->end_time, node->people_num, node->price) != 8)//读取一行数据保存在当前节点,并判断是否读写完毕
					{
						{	//初始化无用空间
							strcpy(node->start_place, "Airport muggle can not found");
							strcpy(node->end_place, "Airport can not be landed at");
							strcpy(node->company, "Hogwarts Co.");
							strcpy(node->flight_num, "HE5972");
							strcpy(node->start_time, "notoday");
							strcpy(node->end_time, "anytime");
							strcpy(node->people_num, "0");
							strcpy(node->price, "0");
							node->next_global = NULL;
							node->next_part = NULL;
							secret_flight_info = node;//保存最后成员的地址
						}
						break;
					}
				}
			}
			fclose(fp);//关闭文件
		}
	}


}
void menu_passenger_histroy(void)
{
	system("cls");
	menu_passenger_pull();
	show_FRMS_title();
	show_passenger_histroy_title();
	show_flight_info(located_flight_info_global);
	printf("                             |");
	system("pause");
}