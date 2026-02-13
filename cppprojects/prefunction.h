#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define OK 1
#define OVER 2
#define INVALID -1
#define FATAL -2

//读取字符串的函数
int read_line(char place[], int n)
{
    int ch = 0, i = 0;
    // 先清空缓冲区的残留换行/空格（只清前置）
    while ((ch = getchar()) == '\n' || ch == ' ') ;
    // 再读有效输入
    while(ch != '\n' && ch != EOF && i < n-1)
    {
        place[i++] = ch;
        ch = getchar();
    }
    place[i] = '\0';
    return i;
}

//输出字符串的函数
int print_line(char place[], int n)
{
    for (int i = 0; place[i] != '\0'; i++)
    {
        printf("%c", place[i]);
    }
    return OK;
}

//判断用户输入的符号是Yes还是No
int yes_or_no()
{
    char exit[5];
    memset(exit, '\0', sizeof(exit));
    read_line(exit, sizeof(exit));
    int len = strlen(exit);

    // 转小写，兼容大小写
    for (int i=0; exit[i]!='\0'; i++) {
        exit[i] = tolower(exit[i]);
    }

    if (len == 3 && strcmp(exit, "yes") == 0)  return true; 
    else if (len == 2 && strcmp(exit, "no") == 0)  return false; 
    else  return INVALID; 

}

/*------------------线性表线性表示专用函数-----------------*/

//宏定义数字
#define MAX_LETTER 10
#define LISTINCREMENT 10
#define DIFFERENCE 1000

//定义单独学生信息的结构体
typedef struct
{
    int id;
    char name[MAX_LETTER];
    int scores;
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

    memset(list->elem, 0, sizeof(student) * n);
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

//将线性表置为空表
int sqlist_clear(Sqlist *list)
{
    list->length=0;
    return OK;
}

//求线性表长度
int sqlist_length(Sqlist *list)
{
    return list->length;
}

//查找线性表中的元素
int sqlist_find(Sqlist *list,int n)
{
    for(int i=0 ; i<list->length ; i++)
    {
        if(list->elem[i].id==n) return i+1;
    }
    return FATAL;
}

//修改线性表中的元素,这里简化为学生成绩
int sqlist_change(Sqlist *list, int n, int s)
{
    list->elem[n].scores = s;
    return OK;
}

//在指定位置插入线性表中的元素
int sqlist_insert(Sqlist *list, int i, student e) //这里的i为数组下标
{
    if (i < 0 || i > list->length)
        return OVER;

    if (list->length >= list->listsize)
    {
        student *newbase = NULL;
        newbase = realloc(list->elem, (list->listsize + LISTINCREMENT) * sizeof(student));
        if (newbase == NULL)
            return FATAL;
        list->elem = newbase;
        list->listsize += LISTINCREMENT;
    }

    for (int j = list->length - 1; j >= i ; j--)
    {
        list->elem[j + 1] = list->elem[j];
    }

    list->elem[i] = e;
    list->length += 1;
    return OK;
}

//在指定位置删除线性表中的元素
int sqlist_delete(Sqlist *list, int i) //这里的i为数组下标
{
    if (i < 0 || i > list->length-1)
        return OVER;

    for (int j=i+1 ; j<=list->length-1 ; j++)
    {
        list->elem[j-1] = list->elem[j];
    }

    list->length--;
    return OK;
}

/*------------------线性表链式表示专用函数-----------------*/

//链式结构体
typedef struct node
{
    int data;
    struct node * next;
}node , *linklist ;

// 单链表初始化
int chlist_init(linklist *L) 
{

    *L = malloc(sizeof(node)); 
    if (*L == NULL) return OVER; 

    (*L)->next = NULL;
    return OK;
}