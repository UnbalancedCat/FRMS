#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"global.h"//�����ͷ�ļ�

//�˵�����
void menu()
{
	int begin ;
	while (1)
	{
		begin = 0;
		show_FRMS_title();
		line();
		printf("                                            1.�� �� Ա �� ¼\n");
		printf("                                            2.�� �� �� ¼\n");
		printf("                                            3.�� ��\n");
		line();
		printf("�������Ӧ��ŷ��ʹ��ܣ�1-3����");
		scanf_s("%d", &begin);//�ȴ�����
		if (begin == 1 || begin == 2 || begin == 3)
		{
			switch (begin)
			{
			case 1:system("cls"); manager_login(); break;
			case 2:system("cls"); passenger(); break;
			case 3:return;//�˳�����
			}
		}
		else
		{
			system("cls"); printf("������Ϸ��ַ�!\n"); 
		}
	}
}
//����Ա����
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
		printf("                                            �� �� Ա �� ¼\n");
		printf("                                            (��0����)\n");
		line();
		printf("���������룺");
		scanf("%s", password_shuru);
		if (strcmp(password_real, password_shuru) == 0)
		{
			fclose(fp);
			printf("��¼�ɹ���\n");
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
				system("cls"); printf("�������\n");
			}
	}
}
void manager_password_change()
{
	int i3 = 0;
	int choo_ma_ch;//����ѡ��
	char password_new[7];
	FILE* xiu;
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            �����������루6λ���ֻ��ַ�����\n");
		printf("                                            (��0����)\n");
		scanf("%s", password_new);
		if (strcmp("0", password_new) == 0)
		{
			system("cls"); return;
		}
		else
		{
			if (strlen(password_new) != 6)
			{
				system("cls"); printf("���볤�ȱ���Ϊ��λ\a\n");
			}
			else
			{
				xiu = fopen("password_manager.txt", "w");
				for (i3 = 0; password_new[i3] != '\0'; i3++)
				{
					fputc(password_new[i3], xiu);
				}
				fclose(xiu);
				printf("�����޸ĳɹ�\n");
				system("pause");
				system("cls");
				return;

			}
		}
	}
}
void manager()
{
	int begin_manager;//ѡ��
	while (1)
	{
		begin_manager = 0;
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            1.�� �� �� ��\n");
		printf("                                            2.�� �� �� Ϣ\n");
		printf("                                            3.�� �� Ա �� Ϣ �� ��\n");
		printf("                                            4.�� �� �� ��\n");
		printf("                                            5.�� ��\n");
		line();
		scanf_s("%d", &begin_manager);//�ȴ�����
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
			system("cls"); printf("������Ϸ��ַ�!\n"); 
		}
	}
}
void manager_flight_info()
{
	//int begin_manager_flight_info = 0;//ѡ��
	char begin_manager_flight_info[3];
	while(1)
	{
		show_FRMS_title();
		show_manager_title();
		show_flight_info_title();
		show_flight_info(head_flight_global);
		line();
		printf("                                             �� �� �� ��\n");
		line();
		printf("                                               1.�� ��\n");
		printf("                                               2.ɾ ��\n");
		printf("                                               3.�� ��\n");
		printf("                                               4.�� ��\n");
		printf("                                               5.�� ѯ\n");
		printf("                                               6.�� ��\n");
		line();
		printf("�������Ӧ��ŷ��ʹ��ܣ�1-6����");
		//scanf_s("%d", &begin_manager_flight_info);//�ȴ�����
		gets_s(begin_manager_flight_info, 3);
		if (begin_manager_flight_info[0] == '1' || begin_manager_flight_info[0] == '2' || begin_manager_flight_info[0] == '3' || begin_manager_flight_info[0] == '4' || begin_manager_flight_info[0] == '5' || begin_manager_flight_info[0] == '6')
		{
			switch (begin_manager_flight_info[0])
			{
			case '1':system("cls"); add_flight_info(); break;//������Ϣ ���
			case '2':system("cls"); delete_flight_info(); break;//������Ϣ ɾ��
			case '3':system("cls"); modify_flight_info(); break;//������Ϣ �޸�
			case '4':system("cls"); bridge_sort_flight_info(); break;//������Ϣ ����
			case '5':system("cls"); break;//������Ϣ ��ѯ
			case '6':system("cls"); return;
			}

		}
		else
		{
			system("cls"); printf("������Ϸ��ַ�!\n"); 
		}
	}
}
void manager_passager()
{
	int begin_manager_passager;//ѡ��
	while (1)
	{
		begin_manager_passager = 0;
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                             �� �� �� Ϣ\n");
		line();
		printf("                                               1.�� ��\n");
		printf("                                               2.ɾ ��\n");
		printf("                                               3.�� ��\n");
		printf("                                               4.�� ѯ\n");
		printf("                                               5.�� ��\n");
		line();
		scanf_s("%d", &begin_manager_passager);//�ȴ�����
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
			system("cls"); printf("������Ϸ��ַ�!\n");
		}
	}
}
void manager_password()
{
	int begin_manager_password;//ѡ��
	while (1)
	{
		begin_manager_password = 0;
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            1.�� �� �� ��\n");
		printf("                                            2.�� ��\n");
		line();
		scanf_s("%d", &begin_manager_password);//�ȴ�����
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
			system("cls"); printf("������Ϸ��ַ�!\n");
		}
	}
}
void file()
{
	int choo;//ѡ��
	while (1)
	{
		choo = 0;
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                        ��ѡ����ļ����еĵĲ���\n");
		printf("                                               1.�� ��\n");
		printf("                                               2.�� ��\n");
		printf("                                               3.�� ��\n");
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
			system("cls"); printf("������Ϸ��ַ�!\n");
		}
	}
}
int file_backup()
{
	int choo_backup;
	char yuan_name[50];//Դͷ�ļ���
	char bei_name[50];//�����ļ���
	char ch;
	while (1)
	{
		printf("������Ҫ���ݵ��ļ���(��0���أ�\n");
		scanf("%s", yuan_name);
		if (strcmp(yuan_name, "0") == 0)
		{
			system("cls"); return;
		}
		else
		{
			printf("�����뱸��·��\n");
			scanf("%s", bei_name);
			FILE* fp1_1 = fopen(yuan_name, "r");//Դ�ļ���
			FILE* fp2_1 = fopen(bei_name, "w");//Ŀ���ļ���

			if (fp1_1 == NULL)
			{
				system("cls");
				printf("�Ҳ���ָ���ļ�\n");
				return;

			}
			if (fp2_1 == NULL)
			{
				system("cls");
				printf("�Ҳ���ָ���ļ�\n");//����ļ��Ƿ�Ϊ��
				return;

			}

			//���ϵĴ�Դ�ļ��ж�ȡ�ַ���д��Ŀ���ļ��У�ֱ������EOF�����������
			while ((ch = fgetc(fp1_1)) != EOF)//EOF���ļ�������־
			{
				fputc(ch, fp2_1);
			}
			//�ر�����ʹ��������ǵùرգ�����ռ����Դ
			fclose(fp1_1);
			fclose(fp2_1);
			printf("���ݳɹ�\n");
			system("pause");
			return;
		}
	}
}
int file_recover()
{
	int choo_file_recover;
	char bei_ex_name[50];//�ļ�������
	char hui_name[50];//Ҫ�ָ����ļ�
	char ch;
	while (1)
	{
		printf("�������ļ�������(��0����)\n");
		scanf("%s", bei_ex_name);
		if (strcmp(bei_ex_name, "0") == 0)
		{
			system("cls"); return;
		}
		else
		{
			printf("������Ҫ�ָ����ļ���\n");
			scanf("%s", hui_name);

			FILE* fp1 = fopen(bei_ex_name, "r");//�ļ�������
			FILE* fp2 = fopen(hui_name, "w");//Ҫ�ָ����ļ�

			if (fp1 == NULL)
			{
				system("cls");
				printf("�Ҳ���ָ���ļ�\n");
				return;
			}
			if (fp2 == NULL)
			{
				system("cls");
				printf("�Ҳ���ָ���ļ�\n");
				return;
			}

			//���ϵĴ�Դ�ļ��ж�ȡ�ַ���д��Ŀ���ļ��У�ֱ������EOF�����������
			while ((ch = fgetc(fp1)) != EOF)//EOF���ļ�������־
			{
				fputc(ch, fp2);
			}
			//�ر�����ʹ��������ǵùرգ�����ռ����Դ
			fclose(fp1);
			fclose(fp2);
			printf("�ָ��ɹ�\n");
			system("pause");
			return;
		}
	}
}
//�ÿͽ���
void passenger()
{
	int begin_passenger;//ѡ��
	while (1)
	{
		begin_passenger = 0;
		show_FRMS_title();
		line();
		printf("                                            �� �� ģ ʽ\n");
		line();
		printf("                                            1.�� �� �� ��\n");
		printf("                                            2.�� �� �� Ϣ\n");
		printf("                                            3.�� ��\n");
		line();
		scanf_s("%d", &begin_passenger);//�ȴ�����
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
			system("cls"); printf("������Ϸ��ַ�!\n");
		}
	}
}
void passenger_flight_info()
{
	int begin_passenger_flight_info;//ѡ��
	while (1)
	{
		begin_passenger_flight_info = 0;
		show_FRMS_title();
		line();
		printf("                                            �� �� ģ ʽ\n");
		line();
		printf("                                            1.�� ��\n");
		printf("                                            2.�� ѯ\n");
		printf("                                            3.�� Ʊ\n");
		printf("                                            4.�� ��\n");
		line();
		scanf_s("%d", &begin_passenger_flight_info);//�ȴ�����
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
			system("cls");  printf("������Ϸ��ַ�!\n");
		}
	}
}
void passenger_info()
{
	int begin_passenger_info;//ѡ��
	while (1)
	{
		begin_passenger_info = 0;
		show_FRMS_title();
		line();
		printf("                                            �� �� ģ ʽ\n");
		line();
		printf("                                            1.���\n");
		printf("                                            2.ɾ��\n");
		printf("                                            3.�޸�\n");
		printf("                                            4.�� ��\n");
		line();
		scanf_s("%d", &begin_passenger_info);//�ȴ�����
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
			system("cls"); printf("������Ϸ��ַ�!\n"); 
		}
	}
}

