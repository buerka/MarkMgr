#include <stdio.h>
#include "enroll.h"
#include "course.h" // 需要用到 findCourseIndex
#include "input.h"  // 需要用到 findStudentIndex (在 input.h 中声明)
#include "utils.h"

static void enrollStudent(StudentDB *sDB, const CourseDB *cDB)
{
    int sId, cId;

    printf("请输入学生学号: ");
    scanf("%d", &sId);
    int sIdx = findStudentIndex(sDB, sId); // 需在 input.c 实现并暴露
    if (sIdx == -1)
    {
        printf("❌ 学生不存在。\n");
        return;
    }

    printf("请输入课程编号: ");
    scanf("%d", &cId);
    flushInput();

    // 1. 检查课程是否存在
    int cIdx = findCourseIndex(cDB, cId);
    if (cIdx == -1)
    {
        printf("❌ 课程不存在。\n");
        return;
    }

    Student *stu = &sDB->stu[sIdx];

    // 2. 检查选课上限
    if (stu->selectedCount >= MAX_STUDENT_COURSES)
    {
        printf("❌ 该学生选课数已达上限 (%d门)！\n", MAX_STUDENT_COURSES);
        return;
    }

    // 3. 检查是否重复
    for (int i = 0; i < stu->selectedCount; i++)
    {
        if (stu->selectedCourses[i].courseId == cId)
        {
            printf("❌ 学生已选过该课程，无需重复。\n");
            return;
        }
    }

    // 4. 执行选课
    int pos = stu->selectedCount;
    stu->selectedCourses[pos].courseId = cId;
    stu->selectedCourses[pos].score = -1.0f; // 初始无成绩
    stu->selectedCount++;

    printf("✅ 选课成功！%s 目前已选 %d 门课。\n", stu->name, stu->selectedCount);
}

static void dropStudent(StudentDB *sDB)
{
    int sId, cId;
    printf("请输入学生学号: ");
    scanf("%d", &sId);
    int sIdx = findStudentIndex(sDB, sId);
    if (sIdx == -1)
    {
        printf("❌ 学生不存在。\n");
        return;
    }

    printf("请输入要退掉的课程编号: ");
    scanf("%d", &cId);
    flushInput();

    Student *stu = &sDB->stu[sIdx];
    int foundInList = -1;

    // 查找已选列表
    for (int i = 0; i < stu->selectedCount; i++)
    {
        if (stu->selectedCourses[i].courseId == cId)
        {
            foundInList = i;
            break;
        }
    }

    if (foundInList == -1)
    {
        printf("❌ 该学生未选修此课程，无法退课。\n");
        return;
    }

    // 移位删除
    for (int i = foundInList; i < stu->selectedCount - 1; i++)
    {
        stu->selectedCourses[i] = stu->selectedCourses[i + 1];
    }
    stu->selectedCount--;
    printf("✅ 退课成功。\n");
}

void handleEnrollMenu(StudentDB *stuDB, const CourseDB *courseDB)
{
    while (1)
    {
        printf("\n--- 学生选课管理 ---\n");
        // 新增选项 3
        printf("1. 学生选课\n2. 学生退课\n3. 录入成绩(补丁)\n0. 返回上一级\n");
        printf("请选择: ");
        int op;
        scanf("%d", &op);
        flushInput();

        if (op == 0)
            break;
        switch (op)
        {
        case 1:
            enrollStudent(stuDB, courseDB);
            break;
        case 2:
            dropStudent(stuDB);
            break;
        case 3:
            registerScore(stuDB, courseDB);
            break; // 调用新函数
        default:
            printf("无效输入\n");
        }
    }
}

void registerScore(StudentDB *sDB, const CourseDB *cDB)
{
    int sId, cId;
    float score;

    printf(">> 成绩录入模式 <<\n");
    printf("请输入学生学号: ");
    scanf("%d", &sId);
    int sIdx = findStudentIndex(sDB, sId);
    if (sIdx == -1)
    {
        printf("❌ 学生不存在。\n");
        return;
    }

    printf("请输入课程编号: ");
    scanf("%d", &cId);
    flushInput();

    // 在该学生的选课列表中查找课程
    Student *stu = &sDB->stu[sIdx];
    int foundIdx = -1;
    for (int i = 0; i < stu->selectedCount; i++)
    {
        if (stu->selectedCourses[i].courseId == cId)
        {
            foundIdx = i;
            break;
        }
    }

    if (foundIdx == -1)
    {
        printf("❌ 该学生未选修此课程，无法录入成绩。\n");
        return;
    }

    printf("请输入成绩 (0-100): ");
    scanf("%f", &score);
    flushInput();

    if (score < 0 || score > 100)
    {
        printf("❌ 成绩不合法。\n");
        return;
    }

    stu->selectedCourses[foundIdx].score = score;
    printf("✅ 成绩录入成功！\n");
}