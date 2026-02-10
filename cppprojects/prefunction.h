#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define OK 1
#define OVER 2
#define INVALID -1
#define FATAL -2

//读取字符串的函数
int read_line(char place[] , int n)
{
    int ch=0,i=0;
    while((ch=getchar())!='\n')
    {
        if(i<n) place[i++] = ch;
    }
    place[i] = '\0';
    return i;
}

//输出字符串的函数
int print_line(char place[] , int n)
{
    for(int i=0 ; place[i]!='\0' ; i++)
    {
        printf("%c",place[i]);
    }
    return OK;
}

//判断用户输入的符号是Yes还是No
int yes_or_no()
{
    char exit[5];
    memset(exit,'\0',sizeof(exit));
    read_line(exit,sizeof(exit));

    if(exit[3]!='\0') 
    {
        memset(exit,'\0',sizeof(exit));
        return INVALID;
    }else if(exit[0]=='Y'&&exit[1]=='e'&&exit[2]=='s') 
    {
        memset(exit,'\0',sizeof(exit));
        return true;
    }else if(exit[0]=='N'&&exit[1]=='o'&&exit[2]=='\0') 
    {
        memset(exit,'\0',sizeof(exit));
        return false;
    }else 
    {
        memset(exit,'\0',sizeof(exit));
        return INVALID;
    }
}


/*------------------线性表线性表示专用函数-----------------*/

//宏定义数字
#define MAX_LETTER 50

//定义单独学生信息的结构体
typedef struct
{
    int id;
    char name[MAX_LETTER];
    int maths;
    int chinese;
    int english;
} student;

//建立动态数组结构体
typedef struct
{
    student *elem;
    int length;
    int listsize;
} Sqlist;

//创建一个指定长度的线性表
int sqlist_init(int n, Sqlist *list)
{
    if (list == NULL || n <= 0 || n > 1000)
        return OVER;

    list->elem = malloc(sizeof(student) * n);
    if (list->elem == NULL)
        return OVER;

    memset(list->elem, 0, sizeof(student)*n);
    list->length = 0;
    list->listsize = n;
    return OK;
}

//销毁线性表
int sqlist_destory(Sqlist *list)
{
    if (list == NULL)
        return OVER;
    free(list->elem);
    list->elem = NULL;

    list->length = 0;
    list->listsize = 0;

    return OK;
}