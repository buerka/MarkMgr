#include <stdio.h>
#include <string.h>
#include "grade.h"

char evaluateGrade(float avg)
{
    // 等级评定规则：A(90-100)、B(80-89)、C(70-79)、D(60-69)、F(0-59)，异常分数返回'?'
    if (avg >= 90.0f && avg <= 100.0f) {
        return 'A';
    } else if (avg >= 80.0f && avg < 90.0f) {
        return 'B';
    } else if (avg >= 70.0f && avg < 80.0f) {
        return 'C';
    } else if (avg >= 60.0f && avg < 70.0f) {
        return 'D';
    } else if (avg >= 0.0f && avg < 60.0f) {
        return 'F';
    } else {
        return '?'; // 处理超出0-100的异常分数
    }
}

void generateComment(Student *stu)
{
    if (stu == NULL) return; // 避免空指针访问

    // 根据等级生成个性化评语，确保不超出comment数组长度
    switch (stu->grade) {
        case 'A':
            strncpy(stu->comment, "优秀！学习能力突出，知识掌握扎实，继续保持领先优势！", sizeof(stu->comment)-1);
            break;
        case 'B':
            strncpy(stu->comment, "良好！基础稳固，具备较强的应用能力，针对性提升可冲刺优秀！", sizeof(stu->comment)-1);
            break;
        case 'C':
            strncpy(stu->comment, "中等！掌握核心知识点，但存在薄弱环节，需加强练习巩固基础！", sizeof(stu->comment)-1);
            break;
        case 'D':
            strncpy(stu->comment, "及格！基本达到课程要求，需重点攻克薄弱科目，提升综合实力！", sizeof(stu->comment)-1);
            break;
        case 'F':
            strncpy(stu->comment, "不及格！知识掌握存在较大缺口，建议查漏补缺，加强基础学习，主动寻求帮助！", sizeof(stu->comment)-1);
            break;
        default:
            strncpy(stu->comment, "成绩异常，无法生成评语，请检查成绩数据！", sizeof(stu->comment)-1);
            break;
    }
    stu->comment[sizeof(stu->comment)-1] = '\0'; // 确保字符串结束符，防止溢出
}

void evaluateAll(StudentDB *db)
{
    if (db == NULL || db->count <= 0) {
        printf("❌ 无学生数据，无法进行等级评定！\n");
        return;
    }

    for (int i = 0; i < db->count; i++)
    {
        db->stu[i].grade = evaluateGrade(db->stu[i].average);
        generateComment(&db->stu[i]);
    }

    printf("✅ 所有学生等级评定和评语生成完成！\n");
}

void gradeDistribution(const StudentDB *db)
{
    if (db == NULL || db->count <= 0) {
        printf("❌ 无学生数据，无法统计等级分布！\n");
        return;
    }

    // 初始化各等级计数器
    int countA = 0, countB = 0, countC = 0, countD = 0, countF = 0, countErr = 0;
    int total = db->count;

    // 统计各等级人数
    for (int i = 0; i < total; i++) {
        switch (db->stu[i].grade) {
            case 'A': countA++; break;
            case 'B': countB++; break;
            case 'C': countC++; break;
            case 'D': countD++; break;
            case 'F': countF++; break;
            default: countErr++; break;
        }
    }

    // 计算各等级占比（保留1位小数）
    float rateA = (float)countA / total * 100.0f;
    float rateB = (float)countB / total * 100.0f;
    float rateC = (float)countC / total * 100.0f;
    float rateD = (float)countD / total * 100.0f;
    float rateF = (float)countF / total * 100.0f;
    float rateErr = (float)countErr / total * 100.0f;

    // 计算及格率（A-D为及格）
    int passCount = countA + countB + countC + countD;
    float passRate = (float)passCount / total * 100.0f;

    // 格式化输出统计结果
    printf("\n===========================================\n");
    printf("           学生成绩等级分布统计\n");
    printf("===========================================\n");
    printf("等级   分数范围   人数   占比\n");
    printf("-------------------------------------------\n");
    printf("A等    90-100     %-4d  %.1f%%\n", countA, rateA);
    printf("B等    80-89      %-4d  %.1f%%\n", countB, rateB);
    printf("C等    70-79      %-4d  %.1f%%\n", countC, rateC);
    printf("D等    60-69      %-4d  %.1f%%\n", countD, rateD);
    printf("F等    0-59       %-4d  %.1f%%\n", countF, rateF);
    if (countErr > 0) {
        printf("异常   -          %-4d  %.1f%%\n", countErr, rateErr);
    }
    printf("-------------------------------------------\n");
    printf("总人数：%d人\n", total);
    printf("及格率（A-D等）：%.1f%%\n", passRate);
    printf("不及格率（F等）：%.1f%%\n", rateF);
    printf("===========================================\n");
}
