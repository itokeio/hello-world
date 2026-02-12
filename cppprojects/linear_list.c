// Exercise on linear representation and implementation of linear lists

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
//引用我另行制作的文件中的函数
#include "Prefunction.h"

//提供帮助菜单
int sqlist_help()
{
    printf("===================== HELP MENU =========================\n");
    printf("| Number |         Operation Description                |\n");
    printf("|--------|----------------------------------------------|\n");
    printf("|   0    | Show the help menu                           |\n"); 
    printf("|   1    | Modify a student's score                     |\n"); 
    printf("|   2    | Insert a student's information               |\n");
    printf("|        | (at the specified position)                  |\n"); 
    printf("|   3    | Delete a student's information               |\n"); 
    printf("|   4    | Show the list of students                    |\n");
    printf("|   5    | Query a specific student's information       |\n"); 
    printf("|   6    | Statistics of students' scores (avg/max/min) |\n");
    printf("|   7    | Query the length of the list.                |\n");
    printf("|   8    | Clear the list to empty                      |\n");
    printf("|   9    | Exit the program (also destroy the list)     |\n");
    printf("=========================================================\n");
    printf("You can enter a number from 0 to 9 to operate the list\n"); 
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
            printf("A list with an initial capacity of %d has been created successfully.\n", start);
            break;
        }

        else
        {
            printf("Creation failed. The length must be between 1 and 1000. Please re-enter\n");
        }
    }
    return OK;
}

// 1: 改变学生成绩（修正版）
int change_1(Sqlist *list)
{

    if (list == NULL) {
        printf("Error: The list pointer is null!\n"); 
        return OVER;
    }

    int n=0,s=0;
    printf("Please enter the student's ID: "); 
    while (scanf("%d", &n) != 1)
    { 
        while (getchar() != '\n');
        printf("Invalid input! Please enter a numeric ID: "); 
    }

    int place = sqlist_find(list,n);
    if (place == FATAL) { 
        printf("Modification failed! No student found with ID: %d.\n", n); 
        return FATAL;
    }

    printf("Please enter the student's new score:"); 
    while (scanf("%d", &s) != 1 || s < 0 || s > 100) 
    { 
        while (getchar() != '\n');
        printf("Invalid score! Please enter a number between 0 and 100: "); 
    }

    sqlist_change(list, place-1, s);
    printf("Modification successful. Now, %s's score is %d (ID: %d).\n", 
           list->elem[place-1].name, 
           list->elem[place-1].scores, 
           list->elem[place-1].id);
    return OK;
}

// 2: 插入学生信息
int insert_2(Sqlist *list,int *id)
{
    while (true)
    {
        int place=0;
        student new = {0, "", 0};
        printf("Please enter the position to insert: "); 
        scanf("%d", &place);
        getchar();
        new.id = *id ;
        (*id) ++;
        printf("Please enter the student's name:"); 
        read_line(new.name, MAX_LETTER);
        printf("Please enter the student's score:"); 
        scanf("%d", &new.scores);

        int result = sqlist_insert(list, place-1 ,new);

        if (result == OVER)
        {
            printf("Invalid position! Please enter a position between 1 and the last valid position, and try again.\n");
            (*id) --;
        }   
        if (result == FATAL)
            printf("Insertion failed: Insufficient memory space.\n"); 
        if (result == OK)
        {
            printf("Insertion successful. Information:\nName: "); 
            print_line(list->elem[place-1].name, MAX_LETTER);
            printf("\nID: %d\nScore: %d\n", list->elem[place-1].id, list->elem[place-1].scores); 
            return OK;
        }
    }
}

// 3: 删除学生信息
int delete_3(Sqlist *list)
{
    int n=0;
    printf("Please enter the student's ID: "); 
    scanf("%d",&n);
    int result = sqlist_find(list,n);
    if(result!=FATAL)
    {
        sqlist_delete(list,result-1);
        printf("Deletion successful.\n"); 
        return OK;
    }else 
    {
        printf("Query failed: No student found with this ID.\n"); 
        return FATAL;
    }
}

// 4: 打印学生列表
int print_4(Sqlist *list)
{
    if (list == NULL || list->length == 0) {
        printf("The list is empty.\n");
        return OK;
    }

    printf("%-6s   %-10s %5s\n", "ID", "Name", "Score");
    printf("------------------------------------\n");

    for(int i = 0; i < list->length; i++)
    {
        printf("%-6d   %-10s %5d\n",
               list->elem[i].id,
               list->elem[i].name,
               list->elem[i].scores);
    }
    return OK;
}

// 5：查找指定学生
int find_5(Sqlist* list)
{
    int n=0;
    printf("Please enter the student's ID: "); 
    scanf("%d",&n);
    int result = sqlist_find(list,n);
    if(result!=FATAL)
    {
        printf("Query successful. Information:\nName: "); 
        print_line(list->elem[result-1].name, MAX_LETTER);
        printf("\nID: %d\nScore: %d\n", list->elem[result-1].id, list->elem[result-1].scores); 
        return OK;
    }else 
    {
        printf("Query failed: No student found with this ID.\n"); 
        return FATAL;
    }
}

// 6: 统计学生成绩（平均分、最高分、最低分）
int stat_6(Sqlist *list)
{
    
    if (list == NULL) {
        printf("Error: The list pointer is null!\n");
        return OVER;
    }
    
    if (list->length == 0) {
        printf("Statistics failed: The list is empty, no student scores to calculate.\n");
        return OVER;
    }

    int sum = 0;
    int max_score = list->elem[0].scores;
    int min_score = list->elem[0].scores;

    // 遍历计算总分、最高分、最低分
    for (int i = 0; i < list->length; i++) {
        sum += list->elem[i].scores;
        if (list->elem[i].scores > max_score) {
            max_score = list->elem[i].scores;
        }
        if (list->elem[i].scores < min_score) {
            min_score = list->elem[i].scores;
        }
    }

    float avg_score = (float)sum / list->length;

    printf("===================== SCORE STATISTICS =====================\n");
    printf("| Total students: %-3d                                  |\n", list->length);
    printf("| Highest score:  %-3d                                  |\n", max_score);
    printf("| Lowest score:   %-3d                                  |\n", min_score);
    printf("| Average score:  %.1f                                 |\n", avg_score);
    printf("============================================================\n");

    return OK;
}

// 7: 查看线性表的长度
int length_7(Sqlist *list)
{
    printf("The current length of the list is %d.\n",list->length); 
    return OK ;
}

// 8: 将线性表置为空表
int clear_8(Sqlist *list,int* id)
{
    sqlist_clear(list);
    (*id) = 1001;
    printf("Cleared successfully. The list is now empty.\n"); 
    return OK;
}

// 9：退出并销毁列表
int exit_9(Sqlist *list)
{
    printf("Are you sure you want to exit the program? This action will destroy the created list. Please enter Yes or No: "); 
    while (true)
    {
        int exit_result = yes_or_no();
        if (exit_result == true)
        {
            sqlist_destory(list);
            printf("Program terminated. Thank you for using this system.\n"); 
            return true;
        }
        if (exit_result == false)
        {
            printf("Exit cancelled. Returning to the main operation menu.\n"); 
            return false;
        }
        if (exit_result == INVALID)
            printf("Invalid input! Please enter only Yes or No.\n"); 
    }
}

int main()           //data structure is a waste of the life! fuck !
{

    Sqlist L;
    int ID=1001;

    printf("Welcome to the Student Information Management System.\n"); 
    printf("First, we need to create an empty list to store student information.\n"); 
    printf("Please enter the initial capacity of the list: \n"); 

    initlist(&L);

    printf("You can now perform various operations by entering numbers.\n"); 

    for (int i = 0;; i++)
    {
        if (i != 0)
            printf("Enter an operation number: "); 
        if (i == 0)
            printf("Tip: Enter 0 to view the help menu if you are unsure how to operate.\n"); 
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
            insert_2(&L,&ID);
            break;
        case 3:
            delete_3(&L);
            break;
        case 4:
            print_4(&L);
            break;
        case 5:
            find_5(&L);
            break;
        case 6:
            stat_6(&L);
            break;
        case 7:
            length_7(&L);
            break;
        case 8:
            clear_8(&L,&ID);
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
            printf("Invalid input! Enter 0 to view the help menu.\n"); 
            break;
        }
    }
}