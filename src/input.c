#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input.h"
#include "utils.h"

#define COURSE_FILE "courses.dat"
#define STUDENT_FILE "students.dat"

// 查找学生索引
int findStudentIndex(const StudentDB *db, int id)
{
    for (int i = 0; i < db->count; i++)
    {
        if (db->stu[i].id == id)
            return i;
    }
    return -1;
}

static void inputStudentInfo(StudentDB *db)
{
    if (db->count >= MAX_STUDENTS)
    {
        printf("❌ 学生人数已达上限，无法注册！\n");
        return;
    }

    Student newStu = {0};

    // 1. 学号录入与去重
    while (1)
    {
        printf("请输入学号 (数字): ");
        if (scanf("%d", &newStu.id) != 1)
        {
            printf("输入格式错误。\n");
            flushInput();
            continue;
        }
        flushInput();

        if (findStudentIndex(db, newStu.id) != -1)
        {
            printf("⚠️ 学号 %d 已存在，请重新输入。\n", newStu.id);
        }
        else
        {
            break; // 学号可用
        }
    }

    // 2. 姓名
    printf("请输入姓名: ");
    fgets(newStu.name, 20, stdin);
    newStu.name[strcspn(newStu.name, "\n")] = 0;
    if (strlen(newStu.name) == 0)
        strcpy(newStu.name, "Unknown");

    // 3. 密码 (新增)
    printf("请设置登录密码: ");
    fgets(newStu.password, 20, stdin);
    newStu.password[strcspn(newStu.password, "\n")] = 0;

    // 初始化选课
    newStu.selectedCount = 0;

    db->stu[db->count] = newStu;
    db->count++;
    printf("✅ 学生注册成功！\n");
}

// 简单的学生列表显示 (用于调试)
static void listStudents(const StudentDB *db)
{
    printf("\n--- 学生列表 ---\n");
    for (int i = 0; i < db->count; i++)
    {
        printf("ID:%-8d 姓名:%-10s 已选课:%d门\n",
               db->stu[i].id, db->stu[i].name, db->stu[i].selectedCount);
    }
}

void handleStudentInfoMenu(StudentDB *db)
{
    while (1)
    {
        printf("\n--- 学生信息管理 ---\n");
        printf("1. 录入新生\n2. 查看所有学生\n0. 返回\n请选择: ");
        int op;
        scanf("%d", &op);
        flushInput();
        if (op == 0)
            break;
        if (op == 1)
            inputStudentInfo(db);
        if (op == 2)
            listStudents(db);
    }
}

// === 数据保存功能 ===
void saveData(const StudentDB *db, const CourseDB *cdb)
{
    // 1. 保存课程数据
    FILE *fp = fopen(COURSE_FILE, "wb");
    if (fp == NULL)
    {
        printf("⚠️ 错误：无法保存课程数据！\n");
    }
    else
    {
        // 先写入数量，再写入数组内容
        fwrite(&cdb->count, sizeof(int), 1, fp);
        if (cdb->count > 0)
        {
            fwrite(cdb->courses, sizeof(Course), cdb->count, fp);
        }
        fclose(fp);
        printf(">> 课程数据已保存。\n");
    }

    // 2. 保存学生数据
    fp = fopen(STUDENT_FILE, "wb");
    if (fp == NULL)
    {
        printf("⚠️ 错误：无法保存学生数据！\n");
    }
    else
    {
        fwrite(&db->count, sizeof(int), 1, fp);
        if (db->count > 0)
        {
            fwrite(db->stu, sizeof(Student), db->count, fp);
        }
        fclose(fp);
        printf(">> 学生数据已保存。\n");
    }
}

// === 数据加载功能 ===
void loadData(StudentDB *db, CourseDB *cdb)
{
    // 1. 加载课程数据
    FILE *fp = fopen(COURSE_FILE, "rb");
    if (fp != NULL)
    {
        fread(&cdb->count, sizeof(int), 1, fp);
        if (cdb->count > 0)
        {
            fread(cdb->courses, sizeof(Course), cdb->count, fp);
        }
        fclose(fp);
        printf(">> 系统初始化：已加载 %d 门课程。\n", cdb->count);
    }
    else
    {
        printf(">> 系统初始化：无课程记录，将建立新库。\n");
        cdb->count = 0;
    }

    // 2. 加载学生数据
    fp = fopen(STUDENT_FILE, "rb");
    if (fp != NULL)
    {
        fread(&db->count, sizeof(int), 1, fp);
        if (db->count > 0)
        {
            fread(db->stu, sizeof(Student), db->count, fp);
        }
        fclose(fp);
        printf(">> 系统初始化：已加载 %d 名学生记录。\n", db->count);
    }
    else
    {
        printf(">> 系统初始化：无学生记录，将建立新库。\n");
        db->count = 0;
    }
}