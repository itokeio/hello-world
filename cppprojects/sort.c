// Exercise on linear representation and implementation of linear lists

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//引用我另行制作的文件中的函数
#include "Prefunction.h"

//提供帮助菜单
int sqlist_help()
{
    printf("===================== HELP MENU ======================\n");
    printf("| Number |         Operation Description             |\n");
    printf("|--------|-------------------------------------------|\n");
    printf("|   0    | expand the help menu                      |\n");
    printf("|   1    | Add a new student's information           |\n");
    printf("|        | (Include ID, name, maths/chinese/english) |\n");
    printf("|   2    | Query student information (by ID)         |\n");
    printf("|   3    | Modify student's scores                   |\n");
    printf("|   4    | Delete a student's information (by ID)    |\n");
    printf("|   5    | Display all students' information         |\n");
    printf("|   6    | Clear the list (keep program running)     |\n");
    printf("|   9    | Exit the program (also destroy the list)  |\n");
    printf("======================================================\n");
    printf("You can enter 0~9 to operate the list\n");
    return OK;
}

//初始化列表
int initlist(Sqlist *list)
{
    while (true)
    {
        int start = 0;
        scanf("%d", &start);
        int reinit = sqlist_init(start,list);

        if (reinit == OK)
        {
            printf("A list with a length of %d has been successfully created.\n", start);
            break;
        }

        else
        {
            printf("Creation failed. The length must be 1~1000. Please re-enter.\n");
        }
    }
    return OK;
}

//9：退出并销毁列表
int exit_9(Sqlist *list)
{
    printf("Are you sure you want to exit the program? Doing so will also destroy the list you have created,Enter Yes or No: ");
    while (true)
    {
        int exit_result = yes_or_no();
        if (exit_result == true)
        {
            sqlist_destory(list);
            printf("Program terminated.Thank you for your use.\n");
            return true;
        }
        if (exit_result == false)  
        {
            printf("Exit cancelled, return to main operation.\n");
            return false;
        }
        if (exit_result == INVALID) printf("Invalid input! Please enter Yes/No only.\n");
    }
}



/*查找线性表中的元素
int sqlist_find(char a)
{
    for(int i=0 ; i<)
}




//修改线性表中的元素
int sqlist_change(char a,)
{


} */

int main()
{

    Sqlist L;

    printf("Welcome to the system which I develop to manage the students' informations.\n");
    printf("The first thing that we must do is to create a empty list to save informations.\n");
    printf("Please enter the length which of the list you want to start creating.\n");

    initlist(&L);

    printf("Now you can perform various operations by entering numbers.\n");

    for (int i=0 ; ; i++)
    {
        if(i!=0) printf("Enter a number to operate: ");
        if(i==0) printf("Tip: Enter 0 to view help if you don't know how to operate.\n");
        int judge=0;
        scanf("%d",&judge);
        getchar();

        switch (judge)
        {
        case 0:
            sqlist_help();
            break;

        case 9:
        {
            int ex9 = exit_9(&L);
            if(ex9==true) return 0;
            else break;
        }
        default: 
            printf("Invalid input! Enter 0 to view help menu.\n");
            break;
        }
    }
}

// printf("Please enter the ID of student and what infomation you want to change");