#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"global.h"//�����ͷ�ļ�

//�˵�����
void menu()
{
	int begin = 0;
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
		case 2: system("cls"); passenger(); break;
		case 3:break;
		}
	}
	else
	{
		system("cls"); printf("������Ϸ��ַ�!\n"); menu();
	}
}
//����Ա����
void manager()
{
	int begin_manager = 0;//ѡ��
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
		case 1:system("cls"); manager_1(); break;
		case 2: system("cls"); manager_2(); break;
		case 3: system("cls"); manager_3(); break;
		case 4: system("cls"); wenjian(); break;
		case 5: system("cls"); menu(); break;
			}
		}
	}
	else
	{
		system("cls"); printf("������Ϸ��ַ�!\n"); manager();
	}
}
void manager_1()
{
	int begin_manager_1 = 0;//ѡ��
	show_FRMS_title();
	show_manager_title();
	line();
	printf("                                               1.�� ��\n");
	printf("                                               2.ɾ ��\n");
	printf("                                               3.�� ��\n");
	printf("                                               4.�� ��\n");
	printf("                                               5.�� ѯ\n");
	printf("                                               6.�� ��\n");
	line();
	scanf_s("%d", &begin_manager_1);//�ȴ�����
	if (begin_manager_1 == 1 || begin_manager_1 == 2 || begin_manager_1 == 3 || begin_manager_1 == 4 || begin_manager_1 == 5 || begin_manager_1 == 6)
	{
		switch (begin_manager_1)
		{
		case 1:system("cls"); break;
		case 2:system("cls"); break;
		case 3:system("cls"); break;
		case 4:system("cls"); break;
		case 5:system("cls"); break;
		case 6:system("cls"); manager(); break;
		}
	}
	else
	{
		system("cls"); printf("������Ϸ��ַ�!\n"); manager_1();
	}
}
void manager_2()
{
	int begin_manager_2 = 0;//ѡ��
	show_FRMS_title();
	show_manager_title();
	line();
	printf("                                               1.�� ��\n");
	printf("                                               2.ɾ ��\n");
	printf("                                               3.�� ��\n");
	printf("                                               4.�� ��\n");
	printf("                                               5.�� ѯ\n");
	printf("                                               6.�� ��\n");
	line();
	scanf_s("%d", &begin_manager_2);//�ȴ�����
	if (begin_manager_2 == 1 || begin_manager_2 == 2 || begin_manager_2 == 3 || begin_manager_2 == 4 || begin_manager_2 == 5 || begin_manager_2 == 6)
		switch (begin_manager_2)
		{
		case 1:system("cls"); break;
		case 2:system("cls"); break;
		case 3:system("cls"); break;
		case 4:system("cls"); break;
		case 5:system("cls"); break;
		case 6:system("cls"); manager(); break;
		}
	else
	{
		system("cls"); printf("������Ϸ��ַ�!\n"); manager_2();
	}
}
void manager_3()
{
	int begin_manager_3 = 0;//ѡ��
	show_FRMS_title();
	show_manager_title();
	line();
	printf("                                            1.�� �� �� ��\n");
	printf("                                            2.�� ��\n");
	line();
	scanf_s("%d", &begin_manager_3);//�ȴ�����
	if (begin_manager_3 == 2 || begin_manager_3 == 1)
	{
		switch (begin_manager_3)
		{
		case 1:system("cls"); manager_ch(); break;
		case 2:system("cls"); manager(); break;
		}
	}
	else
	{
		system("cls"); printf("������Ϸ��ַ�!\n"); manager_3();
	}
}
void passenger()
{
	int begin_passenger = 0;//ѡ��
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
		case 1:system("cls"); passenger_1(); break;
		case 2:system("cls"); passenger_2(); break;
		case 3:system("cls"); menu(); break;
		}
	}
	else
	{
		system("cls"); printf("������Ϸ��ַ�!\n"); passenger();
	}
}
void passenger_1()
{
	int begin_passenger_1 = 0;//ѡ��
	show_FRMS_title();
	line();
	printf("                                            �� �� ģ ʽ\n");
	line();
	printf("                                            1.�� ��\n");
	printf("                                            2.�� ѯ\n");
	printf("                                            3.�� Ʊ\n");
	printf("                                            4.�� ��\n");
	line();
	scanf_s("%d", &begin_passenger_1);//�ȴ�����
	if (begin_passenger_1 == 1 || begin_passenger_1 == 2 || begin_passenger_1 == 3 || begin_passenger_1 == 4)
	{
		switch (begin_passenger_1)
		{
		case 1:system("cls");  break;
		case 2:system("cls"); break;
		case 3:system("cls"); break;
		case 4:system("cls"); passenger(); break;
		}
	}
	else
	{
		system("cls");  printf("������Ϸ��ַ�!\n"); passenger_1();
	}
}
void passenger_2()
{
	int begin_passenger_2 = 0;//ѡ��
	show_FRMS_title();
	line();
	printf("                                            �� �� ģ ʽ\n");
	line();
	printf("                                            1.���\n");
	printf("                                            2.ɾ��\n");
	printf("                                            3.�޸�\n");
	printf("                                            4.�� ��\n");
	line();
	scanf_s("%d", &begin_passenger_2);//�ȴ�����
	if (begin_passenger_2 == 1 || begin_passenger_2 == 2 || begin_passenger_2 == 3 || begin_passenger_2 == 4)
	{
		switch (begin_passenger_2)
		{
		case 1:system("cls"); break;
		case 2:system("cls"); break;
		case 3:system("cls"); break;
		case 4:system("cls"); passenger(); break;
		}
	}
	else
	{
		system("cls"); printf("������Ϸ��ַ�!\n"); passenger_2();
	}
}
void manager_login()
{

	char password_real[7];
	char password_shuru[7];
	FILE* fp;
	show_FRMS_title();
	show_manager_title();
	line();
	printf("                                            �� �� Ա �� ¼\n");
	printf("                                            (��0����)\n");
	line();
	printf("���������룺");
	fp = fopen("password_manager.txt", "r");
	fgets(password_real, 7, fp);
	scanf("%s", password_shuru);
	if (strcmp(password_real, password_shuru) == 0)
	{
		printf("��¼�ɹ���\n");
		line();
		system("pause");
		system("cls");
		manager();
	}
	else if (strcmp("0", password_shuru) == 0)
	{
		system("cls"); menu();
	}
	else
	{
		system("cls"); printf("�������\n"); manager_login();
	}
}
void manager_ch()
{
	int i3 = 0;
	int choo_ma_ch;//����ѡ��
	char password_new[7];
	FILE* xiu;
	show_FRMS_title();
	show_manager_title();
	line();
	printf("                                            �����������루6λ���ֻ��ַ�����\n");
	printf("                                            (��0����)\n");
	scanf("%s", password_new);
	if (strcmp("0", password_new) == 0)
	{
		system("cls"); manager_3();
	}
	else
	{
		if (strlen(password_new) != 6)
		{
			system("cls"); printf("���볤�ȱ���Ϊ��λ\a\n"); manager_ch();
		}
		else
		{
			xiu = fopen("password_manager.txt", "w");
			for (i3 = 0; password_new[i3] != '\0'; i3++)
			{
				fputc(password_new[i3], xiu);
			}
			printf("�����޸ĳɹ�����0���أ�\n");
			system("pause");
			system("cls");
			manager();

		}
	}
}
void wenjian()
{
	int choo;//ѡ��
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
		case 1:system("cls"); beifen(); break;
		case 2: system("cls"); huifu(); break;
		case 3:system("cls"); manager(); break;
		}
	}
	else
	{
		system("cls"); printf("������Ϸ��ַ�!\n"); wenjian();
	}

}
int beifen()
{
	int choo_beifen;
	char yuan_name[50];//Դͷ�ļ���
	char bei_name[50];//�����ļ���
	char ch;

	printf("������Ҫ���ݵ��ļ���(��0���أ�\n");
	scanf("%s", yuan_name);
	if (strcmp(yuan_name, "0") == 0)
	{
		system("cls"); wenjian();
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
			wenjian();

		}
		if (fp2_1 == NULL)
		{
			system("cls");
			printf("�Ҳ���ָ���ļ�\n");//����ļ��Ƿ�Ϊ��
			wenjian();

		}

		//���ϵĴ�Դ�ļ��ж�ȡ�ַ���д��Ŀ���ļ��У�ֱ������EOF�����������
		while ((ch = fgetc(fp1_1)) != EOF)//EOF���ļ�������־
		{
			fputc(ch, fp2_1);
		}
		//�ر�����ʹ��������ǵùرգ�����ռ����Դ
		fclose(fp1_1);
		fclose(fp2_1);
		fp1_1 = NULL;
		fp2_1 = NULL;
		printf("���ݳɹ�\n");
		printf("��1����");
		scanf("%d", &choo_beifen);
		if (choo_beifen == 1)
		{
			system("cls"); wenjian();
		}
	}
}
int huifu()
{
	int choo_huifu;
	char bei_ex_name[50];//�ļ�������
	char hui_name[50];//Ҫ�ָ����ļ�
	char ch;

	printf("�������ļ�������(��0����)\n");
	scanf("%s", bei_ex_name);
	if (strcmp(bei_ex_name, "0") == 0)
	{
		system("cls"); wenjian();
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
			wenjian();
		}
		if (fp2 == NULL)
		{
			system("cls");
			printf("�Ҳ���ָ���ļ�\n");
			wenjian();
		}

		//���ϵĴ�Դ�ļ��ж�ȡ�ַ���д��Ŀ���ļ��У�ֱ������EOF�����������
		while ((ch = fgetc(fp1)) != EOF)//EOF���ļ�������־
		{
			fputc(ch, fp2);
		}
		//�ر�����ʹ��������ǵùرգ�����ռ����Դ
		fclose(fp1);
		fclose(fp2);
		fp1 = NULL;
		fp2 = NULL;
		printf("�ָ��ɹ�\n");
		printf("��1����");
		scanf("%d", &choo_huifu);
		if (choo_huifu == 1)
		{
			system("cls"); wenjian();
		}
	}
}