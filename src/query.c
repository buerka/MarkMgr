#include <stdio.h>
#include "query.h"
#include "utils.h"

static const Student *findStudentById(const StudentDB *db, int id)
{
    for (int i = 0; i < db->count; i++)
    {
        if (db->stu[i].id == id)
        {
            return &db->stu[i];
        }
    }
    return NULL;
}

void queryById(const StudentDB *db)
{
    int id;
    printf("请输入要查询的学生ID: ");
    if (scanf("%d", &id) != 1)
    {
        printf("输入无效！\n");
        flushInput();
        pauseScreen();
        return;
    }
    flushInput(); // 清除回车

    const Student *stu = findStudentById(db, id);

    if (stu != NULL)
    {
        // 找到学生，显示详细成绩单
        printTranscript(stu);
    }
    else
    {
        printf("未找到ID为 %d 的学生记录。\n", id);
    }

    pauseScreen();
    clearScreen();
}

void displayStudent(const Student *stu)
{
    // 打印表格中的一行
    // 格式：ID(8) 姓名(15) 总分(8) 平均分(8) 等级(6)
    printf("%-8d %-15s %-8.1f %-8.1f %-6c %s\n",
           stu->id,
           stu->name,
           stu->total,
           stu->average,
           stu->grade ? stu->grade : '-', // 如果还没评级显示 -
           stu->comment[0] ? "已评" : "-");
}

void displayAll(const StudentDB *db)
{
    if (db->count == 0)
    {
        printf("数据库为空，暂无学生信息。\n");
        pauseScreen();
        clearScreen();
        return;
    }

    // 1. 修改表头：前面增加 "排名"
    printf("\n%-6s %-8s %-15s %-8s %-8s %-6s %s\n", "排名", "ID", "姓名", "总分", "平均分", "等级", "状态");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < db->count; i++)
    {
        // 2. 打印时增加序号 (i + 1)
        const Student *stu = &db->stu[i];
        printf("%-6d %-8d %-15s %-8.1f %-8.1f %-6c %s\n",
               i + 1, // <--- 排名
               stu->id,
               stu->name,
               stu->total,
               stu->average,
               stu->grade ? stu->grade : '-',
               stu->comment[0] ? "已评" : "-");
    }

    printf("-----------------------------------------------------------------------\n");
    printf("共找到 %d 条记录。\n", db->count);

    pauseScreen();
    clearScreen();
}

void printTranscript(const Student *stu)
{
    // 显示详细的单人成绩单
    printf("\n========= 学生成绩报告 =========\n");
    printf(" 学号 : %-10d  姓名 : %s\n", stu->id, stu->name);
    printf("------------------------------\n");

    printf("【各科成绩】\n");
    for (int i = 0; i < COURSE_COUNT; i++)
    {
        printf("  课程 %d : \t%5.1f 分\n", i + 1, stu->score[i]);
    }

    printf("------------------------------\n");
    printf(" 总分   : \t%5.1f\n", stu->total);
    printf(" 平均分 : \t%5.1f\n", stu->average);
    printf(" 等级   : \t[ %c ]\n", stu->grade ? stu->grade : '-'); // 防止空字符
    printf(" 评语   : \t%s\n", stu->comment[0] ? stu->comment : "暂无评语");
    printf("==============================\n");
}
