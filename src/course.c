#include <stdio.h>
#include <string.h>
#include "course.h"
#include "utils.h" // 复用之前的 utils.h (清屏/暂停)

// 查找课程在数组中的下标，找不到返回 -1
int findCourseIndex(const CourseDB *db, int id)
{
    for (int i = 0; i < db->count; i++)
    {
        if (db->courses[i].id == id)
            return i;
    }
    return -1;
}

static void addCourse(CourseDB *db)
{
    if (db->count >= MAX_COURSES_POOL)
    {
        printf("课程库已满，无法添加！\n");
        return;
    }
    Course c;
    printf(">> 请输入课程编号: ");
    scanf("%d", &c.id);
    flushInput();

    if (findCourseIndex(db, c.id) != -1)
    {
        printf("错误：课程编号 %d 已存在！\n", c.id);
        return;
    }

    printf(">> 请输入课程名称: ");
    fgets(c.name, 20, stdin);
    c.name[strcspn(c.name, "\n")] = 0; // 去换行

    printf(">> 请输入学分 (0.5 - 6.0): ");
    scanf("%f", &c.credit);
    flushInput();

    if (c.credit < 0.5f || c.credit > 6.0f)
    {
        printf("错误：学分不合法！\n");
        return;
    }

    db->courses[db->count] = c;
    db->count++;
    printf("✅ 课程录入成功！\n");
}

static void modifyCourse(CourseDB *db)
{
    int id;
    printf("请输入要修改的课程ID: ");
    scanf("%d", &id);
    flushInput();

    int idx = findCourseIndex(db, id);
    if (idx == -1)
    {
        printf("课程不存在！\n");
        return;
    }

    printf("当前课程: %s (%.1f学分)\n", db->courses[idx].name, db->courses[idx].credit);

    printf(">> 输入新名称: ");
    fgets(db->courses[idx].name, 20, stdin);
    db->courses[idx].name[strcspn(db->courses[idx].name, "\n")] = 0;

    printf(">> 输入新学分: ");
    scanf("%f", &db->courses[idx].credit);
    flushInput();
    printf("✅ 修改成功！\n");
}

static void deleteCourse(CourseDB *db)
{
    int id;
    printf("请输入要删除的课程ID: ");
    scanf("%d", &id);
    flushInput();

    int idx = findCourseIndex(db, id);
    if (idx == -1)
    {
        printf("课程不存在！\n");
        return;
    }

    // 数组移位删除
    for (int i = idx; i < db->count - 1; i++)
    {
        db->courses[i] = db->courses[i + 1];
    }
    db->count--;
    printf("✅ 删除成功！\n");
}

static void listCourses(const CourseDB *db)
{
    printf("\n=== 课程列表 (共%d门) ===\n", db->count);
    printf("编号   名称             学分\n");
    printf("----------------------------\n");
    for (int i = 0; i < db->count; i++)
    {
        printf("%-6d %-16s %.1f\n", db->courses[i].id, db->courses[i].name, db->courses[i].credit);
    }
}

void handleCourseMenu(CourseDB *db)
{
    while (1)
    {
        printf("\n--- 课程信息维护 ---\n");
        printf("1. 录入课程\n2. 修改课程\n3. 删除课程\n4. 查看所有课程\n0. 返回上一级\n");
        printf("请选择: ");
        int op;
        scanf("%d", &op);
        flushInput();

        if (op == 0)
            break;
        switch (op)
        {
        case 1:
            addCourse(db);
            break;
        case 2:
            modifyCourse(db);
            break;
        case 3:
            deleteCourse(db);
            break;
        case 4:
            listCourses(db);
            pauseScreen();
            break;
        default:
            printf("无效输入\n");
        }
    }
}