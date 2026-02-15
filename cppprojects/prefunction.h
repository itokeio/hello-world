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

// 销毁单链表
int chlist_destory(linklist *L) 
{
    if(L==NULL || *L==NULL) return FATAL;
    linklist p = NULL;
    while ((*L)->next != NULL) 
    {
        p = *L;
        *L = (*L)->next;
        free(p);
    }
    free(*L);
    *L=NULL;
    return OK;
}

// 判断链表是否为空
int chlist_jdgempty(linklist L) 
{
    if (L == NULL) return 0; 
    else return 1;
}

// 将链表置为空表
int chlist_empty(linklist* L) 
{
    if(L==NULL || *L==NULL) return FATAL;
    linklist p = (*L)->next , q = NULL;
    while (p != NULL) 
    {
        q = p;
        p = p->next;
        free(q);
    }
    (*L)->next = NULL;
    return OK;
} 

//求链表表长
int chlist_length(linklist L) 
{
    if(L==NULL) return FATAL;
    int i=0;
    for( ; L->next != NULL ; i++ )
    {
        L = L->next;
    }
    return i;
} 

//取得链表第i个位置上的值
int chlist_value(linklist L,int n,int* data) 
{
    if(L ==NULL || data == NULL || n<=0) return FATAL;

    linklist p = L->next;
    for(int i=1 ; i<n ; i++ )
    {
        p = p->next;
        if(p==NULL) return OVER;
    }
    *data = p->data;
    return OK;
} 

/*另一个版本的取值函数
int chlist_value (linklist L,int n,int* data) 
{
    if(L==NULL) return FATAL;
    linklist p = L->next;
    int j=1;
    while(p && j<n)
    {
        p = p->next;
        j++;
    }
    if(!p || j>n) return OVER;
    *data = p->data;
    return OK;
} */

//根据指定数据获取所在位置
linklist chlist_find_node(linklist L,int data) 
{
    if(L == NULL) return NULL;

    linklist p = L->next;
    while(p && p->data!=data)
    {
        p = p->next;
    }
    
    return p;
}

//根据指定数据获取所在位置
int chlist_find_place(linklist L,int data) 
{
    if(L == NULL) return FATAL;
    linklist p = L->next;
    int i=1;
    for( ; p && p->data!=data ; i++)
    {
        p = p->next;
    }
    if(p) return i;
    else return 0;
} 

//在指定节点之前插入给定值的新节点
int chlist_insert(linklist L, int i, int e)
{
    if(L == NULL) return FATAL;
    linklist p = L;
    int j = 1;
    while (p != NULL && j < i)
    {
        p = p->next;  
        j++;          
    }

    if (p == NULL || j > i) return OVER;

    linklist s = malloc(sizeof(node));
    if (s == NULL) return FATAL;
    s->data = e;

    s->next = p->next;  // 新节点先指向原第i个节点
    p->next = s;        // 前驱节点再指向新节点

    return OK;
}

//删除指定位置的节点
int chlist_delete(linklist L, int i)
{
    if(L == NULL) return FATAL;
    linklist p = L;
    int j = 1;
    while (p != NULL && j < i)
    {
        p = p->next;  
        j++;          
    }
    if (p == NULL || p->next == NULL) return OVER;

    linklist s = p->next;
    p->next = p->next->next;
    free(s);
    return OK;
}

//头插法建立链表
int chlist_create_listH(linklist* L, int n)
{
    if(L == NULL) return FATAL;
    *L = malloc(sizeof(node));
    (*L)->next = NULL;

    linklist p;
    for(int i=n ; i>0 ; i--)
    {
        p = malloc(sizeof(node));
        scanf("%d",&p->data);
        p->next = (*L)->next;
        (*L)->next = p;
    }
    return OK;
}

//后插法建立链表
int chlist_create_listR(linklist* L, int n)
{
    if(L == NULL) return FATAL;
    *L = malloc(sizeof(node));
    (*L)->next = NULL;

    linklist p = *L , q;
    for(int i=0 ; i<n ; i++)
    {
        q = malloc(sizeof(node));
        scanf("%d",&q->data);
        q->next = NULL;
        p->next = q;
        p = q;
    }
    return OK;
}

//两个带尾指针的循环链表的合并
linklist chlist_connect_circle(linklist Ta, linklist Tb)
{
    if(Ta == NULL || Tb == NULL) return NULL;
    // ① 保存Ta链表的头节点（带尾指针的循环链表，尾指针的next就是头节点）
    linklist p = Ta->next;
    // ② 核心拼接：Ta表尾 直接连接 Tb链表的第一个数据节点（跳过Tb的头节点）
    Ta->next = Tb->next->next;
    // ③ 释放Tb的冗余头节点，避免内存泄漏（C语言用free，对应老师代码的C++ delete）
    free(Tb->next);
    // ④ 闭合循环：让新的尾指针Tb指向Ta的头节点，形成完整的循环链表
    Tb->next = p;
    // 返回合并后新链表的尾指针
    return Tb;
}

typedef struct dunode
{
    int data;
    struct dunode *prior,*next;
}dunode,dulinklist;
