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
		while (strcmp(password_input, password_real) != 0)
		{
			printf("�������\a\n");
			printf("�������������룺");
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
	int i4 = 0,j1=0;//�������
	char password_new[11] = { 0 };
	FILE* xiu;
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                            �����������루6λ���ֻ��ַ�����\n");
		printf("                                            (��0����)\n");
		{
			rewind(stdin);
			fgets(password_new, 8, stdin);
		    rewind(stdin);
			if ('\n' == password_new[strlen(password_new) - 1]) password_new[strlen(password_new) - 1] = 0;
		}
		
		if (strcmp("0", password_new) == 0)//����
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
					printf("���볤�ȱ���Ϊ��λ����ֻ������\n");
					rewind(stdin);
					fgets(password_new, 8, stdin);//������볤��
					rewind(stdin);
					if ('\n' == password_new[strlen(password_new) - 1]) password_new[strlen(password_new) - 1] = 0;
				}
				if (strcmp("0", password_new) == 0)//����
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
	char begin_manager[4] = { 0 };//ѡ��
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
	char begin_manager_flight_info[4] = { 0 };
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
	char begin_manager_passager[4] = { 0 };//ѡ��
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
    char begin_manager_password[4] = { 0 };//ѡ��
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
		case '1':system("cls");manager_password_change(); break;
		case '0':system("cls"); return;
		}
		
	}
}
void file()
{
	char choo[4] = { 0 };//ѡ��
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("                                        ��ѡ����ļ����еĵĲ���\n");
		printf("                                               1.�� �� �� �� �� backup �ļ���\n");
		printf("                                               2.�� �� �� �� �� �� �� · ��\n");
		printf("                                               3.�� ��\n");
		printf("                                               0.�� ��\n");
		line();
		printf("�������Ӧ��ŷ��ʹ��ܣ�0-3����");
		{
			rewind(stdin);
			fgets(choo, 3, stdin);
			rewind(stdin);
			if ('\n' == choo[strlen(choo) - 1]) choo[strlen(choo) - 1] = 0;
		}
		while (choo[1] != '\0' || (choo[0] != '1' && choo[0] != '2' &&choo[0] != '3' && choo[0] != '0'))
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
		case '1':system("cls"); file_backup_to(); break;
		case '2': system("cls"); file_backup(); break;
		case '3':system("cls"); file_recover(); break;
		case '0':system("cls"); return;
		}
		
	}
}
void file_backup()
{
	char yuan_name[155] = { 0 };//Դͷ�ļ���
	char bei_name[155] = { 0 };//�����ļ���
	char ch;
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("��������Ҫ���ݵ��ļ�·��,������չ��(��0���أ�\n");
		printf("��ʾ����C:\\Users\\miku\\password_manager.txt��\n");
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
			printf("�����뱸��·��\n");
			{
				rewind(stdin);
				fgets(bei_name, 150, stdin);
				rewind(stdin);
				if ('\n' == bei_name[strlen(bei_name) - 1]) bei_name[strlen(bei_name) - 1] = 0;
			}
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
			system("cls");
			return;
		}
	}
}

void file_backup_to()
{
	char ch;
	while(1)
	{
		
		show_FRMS_title();
		show_manager_title();
		line();
		FILE* fp1_1 = fopen("data\\flight_info.txt", "r");
		FILE* fp1_2 = fopen("data\\passenger.txt", "r");
		FILE* fp1_3 = fopen("data\\password_manager.txt", "r");
		
		if (fp1_1 == NULL|| fp1_2 == NULL|| fp1_3 == NULL )
		{
			system("cls");
			printf("�Ҳ���ָ���ļ�\n");
			return;

		}
		else
		{
			
			FILE* fp2_1 = fopen("backup\\flight_info.txt", "w");
			while ((ch = fgetc(fp1_1)) != EOF)//1
			{
				fputc(ch, fp2_1);
			}
			fclose(fp1_1);
			fclose(fp2_1);

			FILE* fp2_2 = fopen("backup\\passenger.txt", "w");
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

			printf("�ѱ�����backup�ļ���!\n");
			system("pause");
			system("cls");
			return;
		}
		
	}
	
}

void file_recover()
{
	
	char bei_ex_name[155] = {0};//�ļ�������
	char hui_name[155] = { 0 };//Ҫ�ָ����ļ�
	char ch;
	while (1)
	{
		show_FRMS_title();
		show_manager_title();
		line();
		printf("�������ļ�������(��0����)\n");
		printf("��ʾ����C:\\Users\\miku\\password_manager.txt)\n");
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
			printf("������Ҫ�ָ����ļ���\n");
			{
				rewind(stdin);
				fgets(hui_name, 150, stdin);
				rewind(stdin);
				if ('\n' == hui_name[strlen(hui_name) - 1]) hui_name[strlen(hui_name) - 1] = 0;
			}

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
			system("cls");
			return;
		}
	}
}
//�ÿͽ���
void passenger()
{
	char begin_passenger[4] = { 0 };//ѡ��
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
	char begin_passenger_flight_info[4] = { 0 };//ѡ��
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
	char begin_passenger_info[4] = { 0 };//ѡ��
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
