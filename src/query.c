#include <stdio.h>
#include <string.h>
#include "query.h"
#include "utils.h"
#include "course.h" // 需要 findCourseIndex

// 内部函数：打印单个学生的详细成绩单
static void printTranscript(const Student *stu, const CourseDB *cDB)
{
    printf("\n========================================\n");
    printf(" 姓名: %-12s  学号: %d\n", stu->name, stu->id);
    printf("----------------------------------------\n");
    printf(" %-8s %-16s %-6s %-8s\n", "课程ID", "课程名称", "学分", "成绩");
    printf("----------------------------------------\n");

    for (int i = 0; i < stu->selectedCount; i++)
    {
        int cId = stu->selectedCourses[i].courseId;
        float sc = stu->selectedCourses[i].score;

        // 查找课程详情
        int cIdx = findCourseIndex(cDB, cId);
        char cName[20] = "未知课程";
        float credit = 0.0;

        if (cIdx != -1)
        {
            strcpy(cName, cDB->courses[cIdx].name);
            credit = cDB->courses[cIdx].credit;
        }

        printf(" %-8d %-16s %-6.1f ", cId, cName, credit);
        if (sc >= 0)
            printf("%-8.1f\n", sc);
        else
            printf("%-8s\n", "未录入");
    }

    printf("----------------------------------------\n");
    printf(" 总分: %-8.1f 平均分: %-8.1f 等级: %c\n",
           stu->totalScore, stu->average, stu->grade);
    printf(" 评语: %s\n", stu->comment);
    printf("========================================\n");
}

void queryById(const StudentDB *sDB, const CourseDB *cDB)
{
    int id;
    printf("请输入要查询的学生ID: ");
    if (scanf("%d", &id) != 1)
    {
        flushInput();
        return;
    }
    flushInput();

    for (int i = 0; i < sDB->count; i++)
    {
        if (sDB->stu[i].id == id)
        {
            printTranscript(&sDB->stu[i], cDB);
            return;
        }
    }
    printf("未找到学号为 %d 的学生。\n", id);
}

void displayAll(const StudentDB *sDB)
{
    if (sDB->count == 0)
    {
        printf("无学生数据。\n");
        return;
    }

    printf("\n=== 学生成绩总表 ===\n");
    char *header = "%-6s %-10s %-16s %-8s %-8s %-8s %-6s\n";
    char *row = "%-6d %-10d %-16s %-8d %-8.1f %-8.1f %-6c\n";

    printf(header, "排名", "学号", "姓名", "选课", "总分", "平均", "等级");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < sDB->count; i++)
    {
        const Student *s = &sDB->stu[i];
        printf(row,
               i + 1,
               s->id,
               s->name,
               s->selectedCount,
               s->totalScore,
               s->average,
               s->grade);
    }
    printf("----------------------------------------------------------------------\n");
}