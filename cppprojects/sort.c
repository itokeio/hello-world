//这是一个线性表，其中涉及了许多基本运算

#include<stdio.h>
#include<stdlib.h>
#include"Prefunction.h" 

//宏定义数字
#define MAX_NUMBER 10
#define MAX_LETTER 50

//定义单独学生信息的结构体
typedef struct{
    int id ;
    char name[MAX_LETTER];
    int maths;
    int chinese;
    int english;
} student;

//创建一个指定长度的线性表
int splist_init(int n)
{
    student list[n];
    return OK;
}



//查找线性表中的元素
int sqlist_find(char a)
{
    for(int i=0 ; i<)
}




//修改线性表中的元素
int sqlist_change(char a,)
{
    

}

int main()
{
    printf("Welcome to the system which I develop to manage the students' informations.\n");
    printf("The first thing that we must do is to create a empty list to save informations.\n");
    printf("Please enter the length which of the list you want to start creating.");

    int start=0;
    student sqlist[0];
    scanf("%d",&start);
    sqlist_init(start);


    return 0;
}


//printf("Please enter the ID of student and what infomation you want to change");