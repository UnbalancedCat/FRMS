#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#define _CRT_SECURE_NO_WARNINGS

//定义结构体_旅客
struct Passenger {
    char pname[20];	           //姓名
    char pid[20];	           //身份证
    char password[20];	       //密码
    char tell[15];	           //电话
    char count_num[50];        //记录这是第几个旅客
    struct Passenger* pnext;	//保存下一个地址
};
struct Passenger Passenger[50];
struct Passenger* phead, * pnode, * pend;              //定义旅客类型结构体 头节点、普通节点、尾节点
char count_passenger[60] = { 0 };      //旅客的总人数
int cp = 0;                             //旅客的总人数


//void read_passenger(void);          //读取旅客信息，要在对旅客信息进行操作前调用一次      
void read_passenger(void) {
    FILE* frp;          //frp 即 file_read_passenger
    frp = fopen("data\\passenger.txt", "r");
    if (frp == NULL) { printf("passenger.txt 的旅客文件打开失败!\n"); exit(-1); }
    else {
        pnode = (struct Passenger*)malloc(sizeof(struct Passenger));//分配空间
        phead = pnode;//保存首节点
        if (pnode == NULL) {
            printf("旅客内存分配不足！\n");//提示空间是否分配不足
            exit(1);
        }
        else {
            if (fscanf(frp, "%s %s %s %s", pnode->pid, pnode->pname, pnode->password, pnode->tell) != 4) {
                printf("旅客文件数据读取错误！\n");
                exit(1);
            }
            while (1) {
                cp = cp + 1;
                strcpy(Passenger[cp].count_num, count_passenger);  //从1开始为旅客计数
                pnode->pnext = (struct Passenger*)malloc(sizeof(struct Passenger));//分配空间
                if (pnode->pnext == NULL) {
                    printf("内存分配失败！\n");//提示空间是否分配不足
                    exit(1);
                }
                else {
                    pend = pnode;//保存尾节点
                    pnode = pnode->pnext;//向下移动节点
                    //读取一行数据保存在当前节点,并判断是否读写完毕
                    if (fscanf(frp, "%s %s %s %s", pnode->pid, pnode->pname, pnode->password, pnode->tell) != 4) {
                        pnode = NULL;
                        break;
                    }
                }
            }       fclose(frp);
        }
    }
}

//void mend_passenger(void);         //修改旅客信息
void mend_passenger(void) {
    char linedata[100] = { 0 };
    FILE* f_mend = fopen("data\\passenger.txt", "r");
    FILE* fpw = fopen("data\\tmp.txt", "w");
    int k = search_passenger();
    printf("修改姓名请按1\n  身份证号请按2\n  密码请按3\n  电话请按4\n");
    int a = getchar() - 48;
    switch (a) {
    case 1:while (fgets(linedata, sizeof(linedata) - 1, f_mend)) {
        if (strcmp(linedata, Passenger[k].pname) == 0) {
            char x[100] = { 0 };
            printf("请输入你想要修改后的数据！\n");
            scanf("%s", x);
            fputs(x, fpw);
        }
        else    fputs(linedata, fpw);
    }break;
    case 2:while (fgets(linedata, sizeof(linedata) - 1, f_mend)) {
        if (strcmp(linedata, Passenger[k].pid) == 0) {
            char x[100] = { 0 };
            printf("请输入你想要修改后的数据！\n");
            scanf("%s", x);
            fputs(x, fpw);
        }
        else   fputs(linedata, fpw);
    }break;
    case 3:while (fgets(linedata, sizeof(linedata) - 1, f_mend)) {
        if (strcmp(linedata, Passenger[k].password) == 0) {
            char x[100] = { 0 };
            printf("请输入你想要修改后的数据！\n");
            scanf("%s", x);
            fputs(x, fpw);
        }
        else    fputs(linedata, fpw);
    }break;
    case 4:while (fgets(linedata, sizeof(linedata) - 1, f_mend)) {
        if (strcmp(linedata, Passenger[k].tell) == 0) {
            char x[100];
            printf("请输入你想要修改后的数据！\n");
            scanf("%s", x);
            fputs(x, fpw);
        }
        else    fputs(linedata, fpw);
    }break;
    default: {printf("你输入了错误的数字！\n"); exit(1); }
    }
    fclose(f_mend);                          //关闭文件并重命名
    fclose(fpw);                             //关闭文件并重命名
    system("del passenger.txt");             //删除原文件
    system("rename tmp.txt passenger.txt");
}

//void print_passenger(void)                        //输出旅客信息        调用：printf_passenger();     
void print_passenger(void) {                         //输出旅客信息
    FILE* f_print = fopen("data\\passenger.txt", "r");
    printf("每行四个数据，依次是英文姓名    身份证号    密码  电话\n");
    for (int i = 0; i < cp; i++) {
        char array_print[600] = { 0 };
        fgets(array_print, 600, f_print);
        printf("%s", array_print);
    }
}

//void seek_passenger(void);         //查询旅客信息      
void seek_passenger(void) {
    int  flag_seek = 0;
    char seek_passenger_tell[13] = { 0 };
    FILE* f_seek;            f_seek = fopen("data\\passenger.txt", "r");
    printf("查询方式：\n1.身份证号请按1。\n2.电话号码请按2。\n姓请按3\n姓名和电话号组合查询请按4\n");
    scanf("%d", &flag_seek);
    switch (flag_seek) {
    case 1: {
        printf("请输入身份证号：     \n");
        char seek_passenger_id[19] = { 0 };
        scanf("%s", &seek_passenger_id);
        int i;
        for (i = 0; i <= cp; i++) {
            if (strcmp(Passenger[cp].pid, seek_passenger_id) == 0) {
                printf("姓名：     %s\n", Passenger[i + 1].pname);
                printf("身份证号：     %s\n", Passenger[i + 1].pid);
                printf("电话：     %s\n", Passenger[i + 1].tell);
                break;
            }
            if (i == cp) { printf("没有匹配的旅客身份证号！\n请重新来过\n"); break; }
        }break; }
    case 2: {
        printf("请输入电话号码：        \n");
        char seek_passenger_tell[15] = { 0 };
        scanf("%s", &seek_passenger_tell);
        int j;
        for (j = 0; j <= cp; j++) {
            if (strcmp(Passenger[cp].tell, seek_passenger_tell) == 0) {
                printf("姓名：     %s\n", Passenger[j + 1].pname);
                printf("身份证号：     %s\n", Passenger[j + 1].pid);
                printf("电话：     %s\n", Passenger[j + 1].tell);
                break;
            }
            if (j == cp) { printf("没有匹配的旅客电话号码！\n请重新来过\n"); break; }
        }break; }
    case 3: {
        printf("请输入姓：        \n");
        char seek_passenger_fname[15] = { 1 };
        scanf("%s", &seek_passenger_fname);
        int j;
        for (j = 0; j <= cp; j++) {
            if (strcmp(Passenger[cp].pname, seek_passenger_fname) == 0) {
                printf("姓名：     %s\n", Passenger[j + 1].pname);
                printf("身份证号：     %s\n", Passenger[j + 1].pid);
                printf("电话：     %s\n", Passenger[j + 1].tell);
                break;
            }
            if (j == cp) { printf("没有匹配的旅客的姓！\n请重新来过\n"); break; }
        }break;
    }
    case 4: {
        printf("请输入姓名：        \n");
        char seek_passenger_name[15] = { 1 }; char seek_passenger_password[20] = { 1 };
        scanf("%s", &seek_passenger_name);
        printf("请输入密码：        \n");
        scanf("%s", &seek_passenger_password);
        int j;
        for (j = 0; j <= cp; j++) {
            if (strcmp(Passenger[cp].pname, seek_passenger_name) == 0 && strcmp(Passenger[cp].password, seek_passenger_password) == 0) {
                printf("姓名：     %s\n", Passenger[j + 1].pname);
                printf("身份证号：     %s\n", Passenger[j + 1].pid);
                printf("电话：     %s\n", Passenger[j + 1].tell);
                break;
            }
            if (j == cp) { printf("没有匹配的旅客电话号码！\n请重新来过\n"); break; }
        }break; }
    default:printf("非法输入！！！\n");
    }fclose(f_seek);
}

//void match_passenger(void);         //匹配旅客电话与密码       
//void match_passenger(void);         //匹配旅客电话与密码       有问题还要改
void match_passenger(void) {
    FILE* f_match;
    f_match = fopen("data\\passenger.txt", "r");
    printf("请输入要查询旅客的电话号码。\n");
    int k;          char match_passenger_tell[15] = { 0 };
    scanf("%s", match_passenger_tell);
    for (k = 0; k <= cp; k++) {
        if (strcmp(Passenger[cp].pid, match_passenger_tell) == 0) {
            char match_passenger_password[20] = { 0 };
            printf("请输入对应的旅客密码。\n");
            scanf("%s", match_passenger_password);
            if (strcmp(Passenger[k + 1].password, match_passenger_password) == 0) {
                printf("姓名：     %s\n", Passenger[k + 1].pname);
                printf("身份证号：     %s\n", Passenger[k + 1].pid);
                printf("电话：     %s\n", Passenger[k + 1].tell);
            }break;
        }
        if (k == cp) { printf("没有匹配的旅客电话号码！\n请重新来过\n");  break; }
    }
    fclose(f_match);
}

//void add_passenger(void);          //添加旅客信息     
void add_passenger(void) {
    cp = cp + 1;      int j = 0;        FILE* f_add;
    f_add = fopen("data\\passenger.txt", "a");
    char a[5] = { "\n" };        fwrite(a, 1, strlen(a), f_add);
    switch (j) {
    case 0: {printf("请输入旅客姓名：\n");
        char n[10] = { 0 };
        scanf("%s", n);
        fprintf(f_add, "%s   ", n);
        strcpy(Passenger[cp].pname, n); }
    case 1: {printf("请输入旅客身份证号：\n");
        char nq[20] = { 0 };
        scanf("%s", nq);
        fprintf(f_add, "%s   ", nq);
        strcat(nq, " ");
        strcpy(Passenger[cp].pid, nq); }
    case 2: {printf("请输入旅客密码：\n");
        char nw[20] = { 0 };
        scanf("%s", nw);
        fprintf(f_add, "%s   ", nw);
        strcat(nw, " ");
        strcpy(Passenger[cp].pid, nw); }
    case 3: {printf("请输入旅客电话：\n");
        char ne[20] = { 0 };
        scanf("%s", ne);
        fprintf(f_add, "%s   ", ne);
        strcpy(Passenger[cp].pid, ne);
        strcpy(Passenger[cp].count_num, count_passenger);
        break;  }
    default: {printf("添加旅客信息过程中出现错误！\n");
        break; }
    } fclose(f_add);
}

//void delete_passenger(void);       //删除旅客信息
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

//int search_passenger(void)       寻找对应的旅客,返回k值，对应Passenger[k]    已检查没问题，就是会要输2次电话号
int search_passenger() {
    FILE* f_search;
    f_search = fopen("data\\passenger.txt", "r");
    printf("请输入要查询旅客的电话号码。\n");
    int k;
    int qwe = 0;//储存返回值
    char search_passenger_tell[25] = { 0 };            //储存输入的电话号
    int flag = 0;           //判断是否查询匹配成功。进而跳出for循环
    scanf("%s", search_passenger_tell);
    for (k = 0; k <= cp; k++) {                        //注意k从0开始，同数组
        char save_passenger_tell[600] = { 0 };                                //读取文件数据，进行储存
        fgets(save_passenger_tell, 599, f_search);
        if (strstr(save_passenger_tell, search_passenger_tell) != NULL) {
            qwe = k;           flag = 1;         break;
        }
        if (flag == 1)break;                                                   //跳出for循环
        if (k == cp) {
            printf("没有匹配的旅客电话号码！\n请重新来过\n");
            break;
        }
    }
    return qwe;
    fclose(f_search);
}

void passenger_login() {                                /*旅客登录*/
    int flag_passenger_login = 0;
    while (flag_passenger_login == 0) {
        char passenger_password[21] = { 0 };
        char passenger_log_password[21] = { 0 };
        int flag = search_passenger();
        located_passenger = flag;
        strncpy(passenger_password, Passenger[flag].password, 20);
        printf("%s", Passenger[flag].password);
        printf("请输入对应的密码\n");
        scanf_s("%s", passenger_log_password, 20);
        if (strncmp(passenger_password, passenger_log_password, max(sizeof(passenger_password), sizeof(passenger_log_password))) != 0) {
            printf("你输入了错误的密码！\n"); printf("%s", passenger_password);
        }
        else flag_passenger_login = 1;
    }
    if (flag_passenger_login != 1)passenger_login();
    else if (flag_passenger_login == 1)passenger();
}