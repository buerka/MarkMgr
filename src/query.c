#include <stdio.h>
#include <string.h>
#include "query.h"
#include "utils.h"
#include "course.h" // 需要 findCourseIndex

// 内部函数：打印单个学生的详细成绩单
static void printTranscript(const Student *stu, const CourseDB *cDB) {
    printf("\n========================================\n");
    printf(" 姓名: %-10s  学号: %d\n", stu->name, stu->id);
    printf("----------------------------------------\n");
    printf(" 课程ID  课程名称        学分    成绩\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < stu->selectedCount; i++) {
        int cId = stu->selectedCourses[i].courseId;
        float sc = stu->selectedCourses[i].score;
        
        // 查找课程详情
        int cIdx = findCourseIndex(cDB, cId);
        
        char cName[20] = "未知课程";
        float credit = 0.0;
        
        if (cIdx != -1) {
            strcpy(cName, cDB->courses[cIdx].name);
            credit = cDB->courses[cIdx].credit;
        }

        printf(" %-7d %-14s %-4.1f   ", cId, cName, credit);
        if (sc >= 0) printf("%-5.1f\n", sc);
        else         printf("未录入\n");
    }

    printf("----------------------------------------\n");
    printf(" 总分: %-6.1f  平均分: %-6.1f  等级: %c\n", 
           stu->totalScore, stu->average, stu->grade);
    printf(" 评语: %s\n", stu->comment);
    printf("========================================\n");
}

void queryById(const StudentDB *sDB, const CourseDB *cDB) {
    int id;
    printf("请输入要查询的学生ID: ");
    if (scanf("%d", &id) != 1) {
        flushInput();
        return;
    }
    flushInput();

    for (int i = 0; i < sDB->count; i++) {
        if (sDB->stu[i].id == id) {
            printTranscript(&sDB->stu[i], cDB);
            pauseScreen();
            return;
        }
    }
    printf("未找到学号为 %d 的学生。\n", id);
    pauseScreen();
}

void displayAll(const StudentDB *sDB) {
    if (sDB->count == 0) {
        printf("无学生数据。\n");
        return;
    }

    printf("\n%-6s %-8s %-10s %-8s %-8s %-8s %-8s\n", 
           "排名", "ID", "姓名", "选课数", "总分", "平均分", "等级");
    printf("-------------------------------------------------------------\n");
    
    for (int i = 0; i < sDB->count; i++) {
        const Student *s = &sDB->stu[i];
        printf("%-6d %-8d %-10s %-8d %-8.1f %-8.1f %-8c\n",
               i+1, s->id, s->name, s->selectedCount, 
               s->totalScore, s->average, s->grade);
    }
    printf("-------------------------------------------------------------\n");
    pauseScreen();
}