#include <stdio.h>
#include <string.h>
#include "grade.h"

static char getGradeChar(float avg) {
    if (avg >= 90) return 'A';
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    if (avg >= 60) return 'D';
    if (avg >= 0)  return 'F';
    return '?';
}

static void generateComment(Student *stu) {
    switch (stu->grade) {
        case 'A': strcpy(stu->comment, "学霸认证！继续保持！"); break;
        case 'B': strcpy(stu->comment, "成绩良好，未来可期。"); break;
        case 'C': strcpy(stu->comment, "中规中矩，还需努力。"); break;
        case 'D': strcpy(stu->comment, "低空飘过，注意基础。"); break;
        case 'F': strcpy(stu->comment, "挂科警报！请及时补习。"); break;
        default:  strcpy(stu->comment, "暂无有效成绩。"); break;
    }
}

void evaluateAll(StudentDB *db) {
    for (int i = 0; i < db->count; i++) {
        // 如果一门课都没考，平均分可能是0，或者给特殊标记
        if (db->stu[i].selectedCount == 0) {
            db->stu[i].grade = '?';
        } else {
            db->stu[i].grade = getGradeChar(db->stu[i].average);
        }
        generateComment(&db->stu[i]);
    }
    printf(">> 等级评定完成。\n");
}

void gradeDistribution(const StudentDB *db) {
    int cnt[5] = {0}; // A, B, C, D, F
    int total = 0;

    for (int i = 0; i < db->count; i++) {
        switch(db->stu[i].grade) {
            case 'A': cnt[0]++; total++; break;
            case 'B': cnt[1]++; total++; break;
            case 'C': cnt[2]++; total++; break;
            case 'D': cnt[3]++; total++; break;
            case 'F': cnt[4]++; total++; break;
        }
    }

    if (total == 0) {
        printf("暂无有效等级数据。\n");
        return;
    }

    printf("\n=== 综合等级分布 (基于平均分) ===\n");
    printf("A (90-100): %d 人 (%.1f%%)\n", cnt[0], (float)cnt[0]/total*100);
    printf("B (80-89) : %d 人 (%.1f%%)\n", cnt[1], (float)cnt[1]/total*100);
    printf("C (70-79) : %d 人 (%.1f%%)\n", cnt[2], (float)cnt[2]/total*100);
    printf("D (60-69) : %d 人 (%.1f%%)\n", cnt[3], (float)cnt[3]/total*100);
    printf("F (0-59)  : %d 人 (%.1f%%)\n", cnt[4], (float)cnt[4]/total*100);
}