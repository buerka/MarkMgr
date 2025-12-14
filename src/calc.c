#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

static int compareStudents(const void *a, const void *b)
{
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;

    // 降序排列
    if (s2->total > s1->total) return 1;
    if (s2->total < s1->total) return -1;
    return 0;
}

void sortByTotal(StudentDB *db)
{
    if (db == NULL || db->count <= 1)
    {
        return;
    }
    qsort(db->stu, db->count, sizeof(Student), compareStudents);

    printf(">> 已按总分从高到低完成排序。\n");
}

float calcTotal(const Student *stu)
{
    float t = 0;
    for (int i = 0; i < COURSE_COUNT; i++)
        t += stu->score[i];
    return t;
}

float calcAverage(const Student *stu)
{
    return stu->total / COURSE_COUNT;
}

void calcAll(StudentDB *db)
{
    for (int i = 0; i < db->count; i++)
    {
        db->stu[i].total = calcTotal(&db->stu[i]);
        db->stu[i].average = calcAverage(&db->stu[i]);
    }
}

void courseAnalysis(const StudentDB *db)
{
    if (db == NULL || db->count == 0)
    {
        printf("数据库为空，无法进行学科分析。\n");
        return;
    }

    printf("\n========= 学科分析报告 (共 %d 人) =========\n", db->count);
    // 打印表头：课程 | 平均分 | 最高分 | 最低分 | 及格率
    printf("%-8s %-10s %-10s %-10s %-10s\n", "课程", "平均分", "最高分", "最低分", "及格率");
    printf("----------------------------------------------------\n");

    // 遍历每一门课程 (纵向遍历)
    for (int i = 0; i < COURSE_COUNT; i++)
    {
        float sum = 0;
        float maxScore = -1; // 初始设为极小值
        float minScore = 101; // 初始设为极大值 (成绩范围0-100)
        int passCount = 0;

        // 遍历所有学生
        for (int j = 0; j < db->count; j++)
        {
            float s = db->stu[j].score[i];
            
            sum += s;
            
            if (s > maxScore) maxScore = s;
            if (s < minScore) minScore = s;
            if (s >= 60) passCount++;
        }

        // 计算统计值
        float avg = sum / db->count;
        float passRate = (float)passCount / db->count * 100.0f;

        // 打印一行数据
        printf("课程 %d   %-10.1f %-10.1f %-10.1f %-5.1f%%\n", 
               i + 1, avg, maxScore, minScore, passRate);
    }
    
    printf("----------------------------------------------------\n");
    printf("分析完成。\n");
}
