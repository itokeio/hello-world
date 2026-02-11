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
    printf("|   1    | change a student's score                  |\n");
    printf("|   2    | insert a student's information            |\n");
    printf("|        | (in which you want)                       |\n");
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
        int reinit = sqlist_init(start, list);

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

// 1: 改变学生成绩
int change_1(Sqlist *list)
{
    int n = 0, s = 0;
    printf("Please enter the id of student: ");
    scanf("%d", &n);
    printf("Please enter the score of student:");
    scanf("%d", &s);
    sqlist_change(list, n - DIFFERENCE, s);
    printf("Change succedd.Now,%s's score is %d(ID:%d).\n", list->elem[n - DIFFERENCE - 1].name, &list->elem[n - DIFFERENCE - 1].scores, &list->elem[n - DIFFERENCE - 1].id);
    return OK;
}

// 2: 插入学生信息
int insert_2(Sqlist *list)
{
    while (true)
    {
        student new = {0, "", 0};
        printf("Please enter the place you want insert in: ");
        scanf("%d", &new.id);
        getchar();
        new.id += DIFFERENCE;
        printf("Please enter the name of student:");
        read_line(new.name, MAX_LETTER);
        printf("Please enter the score of student:");
        scanf("%d", &new.scores);

        int result = sqlist_insert(list, new.id - DIFFERENCE, new);

        if (result == OVER)
            printf("The place should be from 1 to the last place,please re-enter again.\n");

        if (result == FATAL)
            printf("Insertion failed.The room is not enough.");

        if (result == OK)
        {
            printf("Insert succedd. Information:\nName: ");
            print_line(list->elem[new.id - DIFFERENCE - 1].name, MAX_LETTER);
            printf("\nID: %d\nScores: %d\n", list->elem[new.id - DIFFERENCE - 1].id, list->elem[new.id - DIFFERENCE - 1].scores); //这里的数字为数组位置,是id减掉固定差和数组差位之后的结果。
            return OK;
        }
    }
}

// 9：退出并销毁列表
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
        if (exit_result == INVALID)
            printf("Invalid input! Please enter Yes/No only.\n");
    }
}

int main()
{

    Sqlist L;

    printf("Welcome to the system which I develop to manage the students' informations.\n");
    printf("The first thing that we must do is to create a empty list to save informations.\n");
    printf("Please enter the length which of the list you want to start creating.\n");

    initlist(&L);

    printf("Now you can perform various operations by entering numbers.\n");

    for (int i = 0;; i++)
    {
        if (i != 0)
            printf("Enter a number to operate: ");
        if (i == 0)
            printf("Tip: Enter 0 to view help if you don't know how to operate.\n");
        int judge = 0;
        scanf("%d", &judge);
        getchar();

        switch (judge)
        {
        case 0:
            sqlist_help();
            break;
        case 1:
            change_1(&L);
            break;
        case 2:
            insert_2(&L);
            break;
        case 9:
        {
            int ex9 = exit_9(&L);
            if (ex9 == true)
                return 0;
            else
                break;
        }
        default:
            printf("Invalid input! Enter 0 to view help menu.\n");
            break;
        }
    }
}

// printf("Please enter the ID of student and what infomation you want to change");