#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"global.h"//�����ͷ�ļ�

//�˵�����
void menu()
{
	char begin[4] ;
	while (1)
	{
		
		show_FRMS_title();
		line();
		printf("                                            1.�� �� Ա �� ¼\n");
		printf("                                            2.�� �� �� ¼\n");
		//���ٲ�ѯ����
		printf("                                            0.�� ��\n");
		line();
		printf("�������Ӧ��ŷ��ʹ��ܣ�0-2����");
		{
			rewind(stdin);
			fgets(begin, 3, stdin);
			rewind(stdin);
			if ('\n' == begin[strlen(begin) - 1]) begin[strlen(begin) - 1] = 0;
		}
		while (begin[1]!='\0'||(begin[0] != '1' && begin[0] != '2' && begin[0] != '0'))
		{
			printf("���зǷ��ַ������������룡\a\n");
			printf("�������Ӧ��ŷ��ʹ��ܣ�0-2����");
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
			case '2':system("cls"); match_passenger(); break;
			case '0':return;//�˳�����
			}
	}
}
//����Ա����
void manager_login()
{
	int i = 6;
	char password_real[8];
	char password_input[8];
	FILE* fp;
	fp = fopen("password_manager.txt", "r");
	fgets(password_real, 7, fp);
	while (1)
	{
		{
			show_FRMS_title();
			show_manager_title();
			line();
			printf("                                            �� �� Ա �� ¼\n");
			printf("                                            (��0����)\n");
			line();
		}
		printf("���������룺");
		{
			rewind(stdin);
			fgets(password_input, 8, stdin);
			rewind(stdin);
			if ('\n' == password_input[strlen(password_input) - 1]) password_input[strlen(password_input) - 1] = 0;
		}
		if (password_input[0] == '0' && password_input[1] == '\0')break;
		while (i)
		{
			if (password_input[6] != '\0' || password_input[i - 1] != password_real[i - 1])
			{
				if (password_input[0] == '0' && password_input[1] == '\0')break;
				printf("�������\a\n");
				printf("�������������룺");
				{
					rewind(stdin);
					fgets(password_input, 8, stdin);
					rewind(stdin);
					if ('\n' == password_input[strlen(password_input) - 1]) password_input[strlen(password_input) - 1] = 0;
				}
				i = 6;
			}
			else i--;
		}
		if (password_input[0] == '0' && password_input[1] == '\0')break;
		{
			fclose(fp);
			printf("��¼�ɹ���\n");
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
	char begin_manager[4];//ѡ��
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            1.�� �� �� ��\n");
		printf("                                            2.�� �� �� Ϣ\n");
		printf("                                            3.�� �� Ա �� Ϣ �� ��\n");
		printf("                                            4.�� �� �� ��\n");
		printf("                                            0.�� ��\n");
		line();
		printf("�������Ӧ��ŷ��ʹ��ܣ�0-4����");
		{
			rewind(stdin);
			fgets(begin_manager, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_manager[strlen(begin_manager) - 1]) begin_manager[strlen(begin_manager) - 1] = 0;
		}
		while (begin_manager[1] != '\0' || (begin_manager[0] < '0' && begin_manager[0] >'4' ))
		{
			printf("���зǷ��ַ������������룡\a\n");
			printf("�������Ӧ��ŷ��ʹ��ܣ�0-2����");
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
	//ѡ��
	char begin_manager_flight_info[4];
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
		printf("                                               0.�� ��\n");
		line();
		
		printf("�������Ӧ��ŷ��ʹ��ܣ�0-5����");
		{
			rewind(stdin);
			fgets(begin_manager_flight_info, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_manager_flight_info[strlen(begin_manager_flight_info) - 1]) begin_manager_flight_info[strlen(begin_manager_flight_info) - 1] = 0;
		}
		while (begin_manager_flight_info[1] != '\0' || (begin_manager_flight_info[0] < '0' && begin_manager_flight_info[0] > '5'))
		{
			printf("���зǷ��ַ������������룡\a\n");
			printf("�������Ӧ��ŷ��ʹ��ܣ�0-2����");
			{
				rewind(stdin);
				fgets(begin_manager_flight_info, 3, stdin);
				rewind(stdin);
				if ('\n' == begin_manager_flight_info[strlen(begin_manager_flight_info) - 1]) begin_manager_flight_info[strlen(begin_manager_flight_info) - 1] = 0;
			}
		}
		switch (begin_manager_flight_info[0])
		{
		case '1':system("cls"); add_flight_info(); break;//������Ϣ ���
		case '2':system("cls"); delete_flight_info(); break;//������Ϣ ɾ��
		case '3':system("cls"); modify_flight_info(); break;//������Ϣ �޸�
		case '4':system("cls"); bridge_sort_flight_info(); break;//������Ϣ ����
		case '5':system("cls"); bridge_refine_search_sort_flight_info(); break;//������Ϣ ��ѯ
		case '0':system("cls"); return;
		}
		
	}
}
void manager_passager()
{
	char begin_manager_passager[4];//ѡ��
	while (1)
	{
		
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                             �� �� �� Ϣ\n");
		line();
		printf("                                               1.�� ��\n");
		printf("                                               2.ɾ ��\n");
		printf("                                               3.�� ��\n");
		printf("                                               4.�� ѯ\n");
		printf("                                               0.�� ��\n");
		line();
		printf("�������Ӧ��ŷ��ʹ��ܣ�0-4����");
		{
			rewind(stdin);
			fgets(begin_manager_passager, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_manager_passager[strlen(begin_manager_passager) - 1]) begin_manager_passager[strlen(begin_manager_passager) - 1] = 0;
		}
		while (begin_manager_passager[1] != '\0' || (begin_manager_passager[0] < '0' && begin_manager_passager[0] > '4' ))
		{
			printf("���зǷ��ַ������������룡\a\n");
			printf("�������Ӧ��ŷ��ʹ��ܣ�0-2����");
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
    char begin_manager_password[4];//ѡ��
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            1.�� �� �� ��\n");
		printf("                                            0.�� ��\n");
		line();
		printf("�������Ӧ��ŷ��ʹ��ܣ�0-1����");
		{
			rewind(stdin);
			fgets(begin_manager_password, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_manager_password[strlen(begin_manager_password) - 1]) begin_manager_password[strlen(begin_manager_password) - 1] = 0;
		}
		while (begin_manager_password[1] != '\0' || (begin_manager_password[0] != '1' && begin_manager_password[0] != '0'))
		{
			printf("���зǷ��ַ������������룡\a\n");
			printf("�������Ӧ��ŷ��ʹ��ܣ�0-2����");
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
	char choo[4];//ѡ��
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                        ��ѡ����ļ����еĵĲ���\n");
		printf("                                               1.�� ��\n");
		printf("                                               2.�� ��\n");
		printf("                                               0.�� ��\n");
		line();
		printf("�������Ӧ��ŷ��ʹ��ܣ�0-2����");
		{
			rewind(stdin);
			fgets(choo, 3, stdin);
			rewind(stdin);
			if ('\n' == choo[strlen(choo) - 1]) choo[strlen(choo) - 1] = 0;
		}
		while (choo[1] != '\0' || (choo[0] != '1' && choo[0] != '2' && choo[0] != '0'))
		{
			printf("���зǷ��ַ������������룡\a\n");
			printf("�������Ӧ��ŷ��ʹ��ܣ�0-2����");
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
	char begin_passenger[4];//ѡ��
	while (1)
	{
		show_FRMS_title();
		line();
		printf("                                            �� �� ģ ʽ\n");
		line();
		printf("                                            1.�� �� �� ��\n");
		printf("                                            2.�� �� �� Ϣ\n");
		printf("                                            0.�� ��\n");
		line();
		printf("�������Ӧ��ŷ��ʹ��ܣ�0-2����");
		{
			rewind(stdin);
			fgets(begin_passenger, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_passenger[strlen(begin_passenger) - 1])  begin_passenger[strlen(begin_passenger) - 1] = 0;
		}
		while (begin_passenger[1] != '\0' || (begin_passenger[0] != '1' && begin_passenger[0] != '2' && begin_passenger[0] != '0'))
		{
			printf("���зǷ��ַ������������룡\a\n");
			printf("�������Ӧ��ŷ��ʹ��ܣ�0-2����");
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
	char begin_passenger_flight_info[4];//ѡ��
	while (1)
	{
		show_FRMS_title();
		line();
		printf("                                            �� �� ģ ʽ\n");
		line();
		printf("                                            1.�� ��\n");
		printf("                                            2.�� ѯ\n");
		printf("                                            3.�� Ʊ\n");
		printf("                                            0.�� ��\n");
		line();
		printf("�������Ӧ��ŷ��ʹ��ܣ�0-3����");
		{
			rewind(stdin);
			fgets(begin_passenger_flight_info, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_passenger_flight_info[strlen(begin_passenger_flight_info) - 1]) begin_passenger_flight_info[strlen(begin_passenger_flight_info) - 1] = 0;
		}
		while (begin_passenger_flight_info[1] != '\0' || (begin_passenger_flight_info[0] < '0' && begin_passenger_flight_info[0] > '3' ))
		{
			printf("���зǷ��ַ������������룡\a\n");
			printf("�������Ӧ��ŷ��ʹ��ܣ�0-2����");
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
	char begin_passenger_info[4];//ѡ��
	while (1)
	{
		show_FRMS_title();
		line();
		printf("                                            �� �� ģ ʽ\n");
		line();
		printf("                                            1.���\n");
		printf("                                            2.ɾ��\n");
		printf("                                            3.�޸�\n");
		printf("                                            0.�� ��\n");
		line();
		printf("�������Ӧ��ŷ��ʹ��ܣ�0-3����");
		{
			rewind(stdin);
			fgets(begin_passenger_info, 3, stdin);
			rewind(stdin);
			if ('\n' == begin_passenger_info[strlen(begin_passenger_info) - 1]) begin_passenger_info[strlen(begin_passenger_info) - 1] = 0;
		}
		while (begin_passenger_info[1] != '\0' || (begin_passenger_info[0]  <'0' && begin_passenger_info[0] > '3' ))
		{
			printf("���зǷ��ַ������������룡\a\n");
			printf("�������Ӧ��ŷ��ʹ��ܣ�0-2����");
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
