#pragma once
#ifndef OUTPUT_H_
#define OUTPUT_H_


//�������ʱ�̱���ͷ
void flight_info_title(void)
{
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("                                            �� �� ʱ �� ��\n");
}

//�������Ԥ������ϵͳ��ͷ
void FRMS_title(void)
{
	printf("-----------------------------------------------------------------------------------------------------\n\n");
	printf("                      ��      ��      Ԥ      ��      ��      ��      ϵ      ͳ\n\n");
}

//�������ʱ�̱������
void flight_info_subtitle(void)
{
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("|No|%20s|%20s|%12s|%7s|%9s|%9s|%6s|%6s|\n", "Aʼ����", "BĿ�ĵ�", "C���չ�˾", "D�����", "E���ʱ��", "F����ʱ��", "G�ؿ�", "HƱ��");
}

//function plays music
#include <Windows.h>
#pragma comment(lib,"Winmm.lib")
void music(void)
{
	char* point;
	int i = 0;
	char q = 'a';
	char no_use = '\n';
	char sentence[] =        "Loading Knock Me Out. . .\nEnter q to stop the music and start the rael project         ;)\nPlease enter a letter:\0";
	char sentence_reload[] = "Reloading Knock Me Out...\nWhy don't you LISTEN TO ME to continue!?                     :(\nEnter q!:\0";
	while (q != 'q')
	{
		if (i == 0)
		{
			point = sentence;
			i++;
		}
		else point = sentence_reload;


		PlaySound(TEXT("Knock Me Out.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

		while (*point != '\0')
		{
			printf("%c", *point);
			if (*point == '\n')Sleep(1500);
			else Sleep(100);
			point++;
		}

		q = getchar();
		no_use = getchar();
		system("cls");
	}

	return;
}

#endif
