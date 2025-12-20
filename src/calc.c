#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "course.h" // 假设里面有 findCourseIndex 等辅助函数

// 内部函数：计算单个学生
static void calcStudent(Student *stu) {
    float sum = 0;
    int validCount = 0;

    for (int i = 0; i < stu->selectedCount; i++) {
        float s = stu->selectedCourses[i].score;
        // -1 代表只选了课，还没录入成绩，不计入统计
        if (s >= 0) {
            sum += s;
            validCount++;
        }
    }

    stu->totalScore = sum;
    stu->average = (validCount > 0) ? (sum / validCount) : 0.0f;
}

void calcAll(StudentDB *db) {
    for (int i = 0; i < db->count; i++) {
        calcStudent(&db->stu[i]);
    }
}

// 排序比较函数
static int compareStudentsByTotal(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    if (s2->totalScore > s1->totalScore) return 1;
    if (s2->totalScore < s1->totalScore) return -1;
    return 0;
}

void sortByTotal(StudentDB *db) {
    if (db->count > 1) {
        qsort(db->stu, db->count, sizeof(Student), compareStudentsByTotal);
        printf(">> 已按总分降序排列。\n");
    }
}

// 学科分析：这是最复杂的，需要双重循环
void courseAnalysis(const StudentDB *sDB, const CourseDB *cDB) {
    if (cDB->count == 0) {
        printf("暂无课程信息。\n");
        return;
    }

    printf("\n========= 学科分析报告 =========\n");
    printf("%-6s %-15s %-6s %-8s %-8s %-8s\n", 
           "ID", "课程名称", "选课人数", "平均分", "最高分", "及格率");
    printf("------------------------------------------------------------\n");

    // 1. 遍历每一门在这个系统里存在的课程
    for (int i = 0; i < cDB->count; i++) {
        int cId = cDB->courses[i].id;
        
        int count = 0;      // 选这门课并有成绩的人数
        float sum = 0;
        float max = -1;
        int pass = 0;

        // 2. 遍历所有学生，看谁选了这门课
        for (int j = 0; j < sDB->count; j++) {
            const Student *s = &sDB->stu[j];
            
            // 在该学生的选课列表里找这门课
            for (int k = 0; k < s->selectedCount; k++) {
                if (s->selectedCourses[k].courseId == cId) {
                    float val = s->selectedCourses[k].score;
                    if (val >= 0) { // 只有已考试的才统计
                        count++;
                        sum += val;
                        if (val > max) max = val;
                        if (val >= 60) pass++;
                    }
                    break; 
                }
            }
        }

        if (count > 0) {
            printf("%-6d %-15s %-6d %-8.1f %-8.1f %-5.1f%%\n",
                   cId, 
                   cDB->courses[i].name, 
                   count, 
                   sum / count, 
                   max, 
                   (float)pass / count * 100.0f);
        } else {
            // 无人选修或无人考试
            printf("%-6d %-15s %-6d %-8s %-8s %-8s\n", 
                   cId, cDB->courses[i].name, 0, "-", "-", "-");
        }
    }
    printf("------------------------------------------------------------\n");
}