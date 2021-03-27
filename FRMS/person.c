#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#define _CRT_SECURE_NO_WARNINGS

//����ṹ��_�ÿ�
struct Passenger {
    char pname[20];	           //����
    char pid[20];	           //���֤
    char password[20];	       //����
    char tell[15];	           //�绰
    char count_num[50];        //��¼���ǵڼ����ÿ�
    struct Passenger* pnext;	//������һ����ַ
};
struct Passenger Passenger[50];
struct Passenger* phead, * pnode, * pend;              //�����ÿ����ͽṹ�� ͷ�ڵ㡢��ͨ�ڵ㡢β�ڵ�
char count_passenger[60] = { 0 };      //�ÿ͵�������
int cp = 0;                             //�ÿ͵�������


//void read_passenger(void);          //��ȡ�ÿ���Ϣ��Ҫ�ڶ��ÿ���Ϣ���в���ǰ����һ��      
void read_passenger(void) {
    FILE* frp;          //frp �� file_read_passenger
    frp = fopen("data\\passenger.txt", "r");
    if (frp == NULL) { printf("passenger.txt ���ÿ��ļ���ʧ��!\n"); exit(-1); }
    else {
        pnode = (struct Passenger*)malloc(sizeof(struct Passenger));//����ռ�
        phead = pnode;//�����׽ڵ�
        if (pnode == NULL) {
            printf("�ÿ��ڴ���䲻�㣡\n");//��ʾ�ռ��Ƿ���䲻��
            exit(1);
        }
        else {
            if (fscanf(frp, "%s %s %s %s", pnode->pid, pnode->pname, pnode->password, pnode->tell) != 4) {
                printf("�ÿ��ļ����ݶ�ȡ����\n");
                exit(1);
            }
            while (1) {
                cp = cp + 1;
                strcpy(Passenger[cp].count_num, count_passenger);  //��1��ʼΪ�ÿͼ���
                pnode->pnext = (struct Passenger*)malloc(sizeof(struct Passenger));//����ռ�
                if (pnode->pnext == NULL) {
                    printf("�ڴ����ʧ�ܣ�\n");//��ʾ�ռ��Ƿ���䲻��
                    exit(1);
                }
                else {
                    pend = pnode;//����β�ڵ�
                    pnode = pnode->pnext;//�����ƶ��ڵ�
                    //��ȡһ�����ݱ����ڵ�ǰ�ڵ�,���ж��Ƿ��д���
                    if (fscanf(frp, "%s %s %s %s", pnode->pid, pnode->pname, pnode->password, pnode->tell) != 4) {
                        pnode = NULL;
                        break;
                    }
                }
            }       fclose(frp);
        }
    }
}

//void mend_passenger(void);         //�޸��ÿ���Ϣ
void mend_passenger(void) {
    char linedata[100] = { 0 };
    FILE* f_mend = fopen("data\\passenger.txt", "r");
    FILE* fpw = fopen("data\\tmp.txt", "w");
    int k = search_passenger();
    printf("�޸������밴1\n  ���֤���밴2\n  �����밴3\n  �绰�밴4\n");
    int a = getchar() - 48;
    switch (a) {
    case 1:while (fgets(linedata, sizeof(linedata) - 1, f_mend)) {
        if (strcmp(linedata, Passenger[k].pname) == 0) {
            char x[100] = { 0 };
            printf("����������Ҫ�޸ĺ�����ݣ�\n");
            scanf("%s", x);
            fputs(x, fpw);
        }
        else    fputs(linedata, fpw);
    }break;
    case 2:while (fgets(linedata, sizeof(linedata) - 1, f_mend)) {
        if (strcmp(linedata, Passenger[k].pid) == 0) {
            char x[100] = { 0 };
            printf("����������Ҫ�޸ĺ�����ݣ�\n");
            scanf("%s", x);
            fputs(x, fpw);
        }
        else   fputs(linedata, fpw);
    }break;
    case 3:while (fgets(linedata, sizeof(linedata) - 1, f_mend)) {
        if (strcmp(linedata, Passenger[k].password) == 0) {
            char x[100] = { 0 };
            printf("����������Ҫ�޸ĺ�����ݣ�\n");
            scanf("%s", x);
            fputs(x, fpw);
        }
        else    fputs(linedata, fpw);
    }break;
    case 4:while (fgets(linedata, sizeof(linedata) - 1, f_mend)) {
        if (strcmp(linedata, Passenger[k].tell) == 0) {
            char x[100];
            printf("����������Ҫ�޸ĺ�����ݣ�\n");
            scanf("%s", x);
            fputs(x, fpw);
        }
        else    fputs(linedata, fpw);
    }break;
    default: {printf("�������˴�������֣�\n"); exit(1); }
    }
    fclose(f_mend);                          //�ر��ļ���������
    fclose(fpw);                             //�ر��ļ���������
    system("del passenger.txt");             //ɾ��ԭ�ļ�
    system("rename tmp.txt passenger.txt");
}

//void print_passenger(void)                        //����ÿ���Ϣ        ���ã�printf_passenger();     
void print_passenger(void) {                         //����ÿ���Ϣ
    FILE* f_print = fopen("data\\passenger.txt", "r");
    printf("ÿ���ĸ����ݣ�������Ӣ������    ���֤��    ����  �绰\n");
    for (int i = 0; i < cp; i++) {
        char array_print[600] = { 0 };
        fgets(array_print, 600, f_print);
        printf("%s", array_print);
    }
}

//void seek_passenger(void);         //��ѯ�ÿ���Ϣ      
void seek_passenger(void) {
    int  flag_seek = 0;
    char seek_passenger_tell[13] = { 0 };
    FILE* f_seek;            f_seek = fopen("data\\passenger.txt", "r");
    printf("��ѯ��ʽ��\n1.���֤���밴1��\n2.�绰�����밴2��\n���밴3\n�����͵绰����ϲ�ѯ�밴4\n");
    scanf("%d", &flag_seek);
    switch (flag_seek) {
    case 1: {
        printf("���������֤�ţ�     \n");
        char seek_passenger_id[19] = { 0 };
        scanf("%s", &seek_passenger_id);
        int i;
        for (i = 0; i <= cp; i++) {
            if (strcmp(Passenger[cp].pid, seek_passenger_id) == 0) {
                printf("������     %s\n", Passenger[i + 1].pname);
                printf("���֤�ţ�     %s\n", Passenger[i + 1].pid);
                printf("�绰��     %s\n", Passenger[i + 1].tell);
                break;
            }
            if (i == cp) { printf("û��ƥ����ÿ����֤�ţ�\n����������\n"); break; }
        }break; }
    case 2: {
        printf("������绰���룺        \n");
        char seek_passenger_tell[15] = { 0 };
        scanf("%s", &seek_passenger_tell);
        int j;
        for (j = 0; j <= cp; j++) {
            if (strcmp(Passenger[cp].tell, seek_passenger_tell) == 0) {
                printf("������     %s\n", Passenger[j + 1].pname);
                printf("���֤�ţ�     %s\n", Passenger[j + 1].pid);
                printf("�绰��     %s\n", Passenger[j + 1].tell);
                break;
            }
            if (j == cp) { printf("û��ƥ����ÿ͵绰���룡\n����������\n"); break; }
        }break; }
    case 3: {
        printf("�������գ�        \n");
        char seek_passenger_fname[15] = { 1 };
        scanf("%s", &seek_passenger_fname);
        int j;
        for (j = 0; j <= cp; j++) {
            if (strcmp(Passenger[cp].pname, seek_passenger_fname) == 0) {
                printf("������     %s\n", Passenger[j + 1].pname);
                printf("���֤�ţ�     %s\n", Passenger[j + 1].pid);
                printf("�绰��     %s\n", Passenger[j + 1].tell);
                break;
            }
            if (j == cp) { printf("û��ƥ����ÿ͵��գ�\n����������\n"); break; }
        }break;
    }
    case 4: {
        printf("������������        \n");
        char seek_passenger_name[15] = { 1 }; char seek_passenger_password[20] = { 1 };
        scanf("%s", &seek_passenger_name);
        printf("���������룺        \n");
        scanf("%s", &seek_passenger_password);
        int j;
        for (j = 0; j <= cp; j++) {
            if (strcmp(Passenger[cp].pname, seek_passenger_name) == 0 && strcmp(Passenger[cp].password, seek_passenger_password) == 0) {
                printf("������     %s\n", Passenger[j + 1].pname);
                printf("���֤�ţ�     %s\n", Passenger[j + 1].pid);
                printf("�绰��     %s\n", Passenger[j + 1].tell);
                break;
            }
            if (j == cp) { printf("û��ƥ����ÿ͵绰���룡\n����������\n"); break; }
        }break; }
    default:printf("�Ƿ����룡����\n");
    }fclose(f_seek);
}

//void match_passenger(void);         //ƥ���ÿ͵绰������       
//void match_passenger(void);         //ƥ���ÿ͵绰������       �����⻹Ҫ��
void match_passenger(void) {
    FILE* f_match;
    f_match = fopen("data\\passenger.txt", "r");
    printf("������Ҫ��ѯ�ÿ͵ĵ绰���롣\n");
    int k;          char match_passenger_tell[15] = { 0 };
    scanf("%s", match_passenger_tell);
    for (k = 0; k <= cp; k++) {
        if (strcmp(Passenger[cp].pid, match_passenger_tell) == 0) {
            char match_passenger_password[20] = { 0 };
            printf("�������Ӧ���ÿ����롣\n");
            scanf("%s", match_passenger_password);
            if (strcmp(Passenger[k + 1].password, match_passenger_password) == 0) {
                printf("������     %s\n", Passenger[k + 1].pname);
                printf("���֤�ţ�     %s\n", Passenger[k + 1].pid);
                printf("�绰��     %s\n", Passenger[k + 1].tell);
            }break;
        }
        if (k == cp) { printf("û��ƥ����ÿ͵绰���룡\n����������\n");  break; }
    }
    fclose(f_match);
}

//void add_passenger(void);          //����ÿ���Ϣ     
void add_passenger(void) {
    cp = cp + 1;      int j = 0;        FILE* f_add;
    f_add = fopen("data\\passenger.txt", "a");
    char a[5] = { "\n" };        fwrite(a, 1, strlen(a), f_add);
    switch (j) {
    case 0: {printf("�������ÿ�������\n");
        char n[10] = { 0 };
        scanf("%s", n);
        fprintf(f_add, "%s   ", n);
        strcpy(Passenger[cp].pname, n); }
    case 1: {printf("�������ÿ����֤�ţ�\n");
        char nq[20] = { 0 };
        scanf("%s", nq);
        fprintf(f_add, "%s   ", nq);
        strcat(nq, " ");
        strcpy(Passenger[cp].pid, nq); }
    case 2: {printf("�������ÿ����룺\n");
        char nw[20] = { 0 };
        scanf("%s", nw);
        fprintf(f_add, "%s   ", nw);
        strcat(nw, " ");
        strcpy(Passenger[cp].pid, nw); }
    case 3: {printf("�������ÿ͵绰��\n");
        char ne[20] = { 0 };
        scanf("%s", ne);
        fprintf(f_add, "%s   ", ne);
        strcpy(Passenger[cp].pid, ne);
        strcpy(Passenger[cp].count_num, count_passenger);
        break;  }
    default: {printf("����ÿ���Ϣ�����г��ִ���\n");
        break; }
    } fclose(f_add);
}

//void delete_passenger(void);       //ɾ���ÿ���Ϣ
void delete_passenger(void) {
    cp = cp - 1;
    int x;
    x = search_passenger();
    if (x != cp) {
        for (int i = 0; i < cp; i++) {
            strcpy(Passenger[x].pnext, Passenger[x + 1].pnext);
            x++;
        }
    }
    else { Passenger[x - 1].pnext = NULL; }
}

//int search_passenger(void)       Ѱ�Ҷ�Ӧ���ÿ�,����kֵ����ӦPassenger[k]    �Ѽ��û���⣬���ǻ�Ҫ��2�ε绰��
int search_passenger() {
    FILE* f_search;
    f_search = fopen("data\\passenger.txt", "r");
    printf("������Ҫ��ѯ�ÿ͵ĵ绰���롣\n");
    int k;
    int qwe = 0;//���淵��ֵ
    char search_passenger_tell[25] = { 0 };            //��������ĵ绰��
    int flag = 0;           //�ж��Ƿ��ѯƥ��ɹ�����������forѭ��
    scanf("%s", search_passenger_tell);
    for (k = 0; k <= cp; k++) {                        //ע��k��0��ʼ��ͬ����
        char save_passenger_tell[600] = { 0 };                                //��ȡ�ļ����ݣ����д���
        fgets(save_passenger_tell, 599, f_search);
        if (strstr(save_passenger_tell, search_passenger_tell) != NULL) {
            qwe = k;           flag = 1;         break;
        }
        if (flag == 1)break;                                                   //����forѭ��
        if (k == cp) {
            printf("û��ƥ����ÿ͵绰���룡\n����������\n");
            break;
        }
    }
    return qwe;
    fclose(f_search);
}

void passenger_login() {                                /*�ÿ͵�¼*/
    int flag_passenger_login = 0;
    while (flag_passenger_login == 0) {
        char passenger_password[21] = { 0 };
        char passenger_log_password[21] = { 0 };
        int flag = search_passenger();
        located_passenger = flag;
        strncpy(passenger_password, Passenger[flag].password, 20);
        printf("%s", Passenger[flag].password);
        printf("�������Ӧ������\n");
        scanf_s("%s", passenger_log_password, 20);
        if (strncmp(passenger_password, passenger_log_password, max(sizeof(passenger_password), sizeof(passenger_log_password))) != 0) {
            printf("�������˴�������룡\n"); printf("%s", passenger_password);
        }
        else flag_passenger_login = 1;
    }
    if (flag_passenger_login != 1)passenger_login();
    else if (flag_passenger_login == 1)passenger();
}