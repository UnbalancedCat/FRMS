#include<stdio.h>
#include<Windows.h>	//��ֲ����ʱ��ע�⣡����
int main(void)
{

	void flight_menu(void);
	void reservation_menu(void);
	void passenger_info(void);
	void admin_menu(void);

	char std_in;	//�洢����������
	int option;		


	printf("\n");	//Ԥ��λ�ã���ʾ������Ϣ
	while (1)
	{
		
		printf("==========================================\n");
		printf("�� ӭ ʹ �� �� �� �� �� Ԥ �� �� �� ϵ ͳ \n");
		printf("==========================================\n");
		printf("*         1        �� �� �� ѯ           *\n");
		printf("*         2        Ԥ �� �� Ʊ           *\n");
		printf("*         3        �� �� �� Ϣ           *\n");
		printf("*         4        �� �� ģ ʽ           *\n");
		printf("*         0        �� �� ϵ ͳ           *\n");
		printf("==========================================\n");
		printf("     �� �� �� Ӧ �� �� �� �� �� �� ��     \n");
		printf("==========================================\n");
		printf("��ѡ��0-4����");
		
		scanf_s("%d", &option);
		
		while ((std_in = getchar()) != EOF && std_in != '\n');//�����Ƿ����������������������
		
		switch (option)//����ѡ��
		{
		case 1:flight_menu(); break;			//�����ѯ�˵�
		case 2:reservation_menu(); break;		//��ƱԤ���˵�
		case 3:passenger_info(); break;			//�ÿ���Ϣ�˵�
		case 4:admin_menu(); break;				//����Ա�˵�
		case 0:return 0;
		default: {system("cls"); printf("ָ�����,����������\n\a"); } break;
		}
	}
	return 0;
}
