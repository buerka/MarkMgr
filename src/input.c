#include <stdio.h>
#include <string.h>
#include "input.h"
#include "calc.h"
#include "grade.h"
#include "utils.h"

float inputScore()
{
    float s;
    while (1)
    {
        if (scanf("%f", &s) != 1)
        {
            printf("输入格式错误！请重新输入数字: ");
            flushInput();
            continue;
        }
        if (validateScore(s))
        {
            return s;
        }
        printf("成绩必须在0-100之间！请重新输入: ");
    }
}

int validateScore(float s)
{
    return (s >= 0 && s <= 100);
}

static int isIdExists(const StudentDB *db, int id)
{
    for (int i = 0; i < db->count; i++)
    {
        if (db->stu[i].id == id)
        {
            return 1;
        }
    }
    return 0;
}

void inputStudentInfo(StudentDB *db)
{
    if (db->count >= STUDENT_COUNT)
    {
        printf("学生数量已达上限（%d人），无法添加！\n", STUDENT_COUNT);
        pauseScreen();
        clearScreen();
        return;
    }

    Student newStu = {0};
    flushInput();

    // 输入姓名
    printf("请输入学生姓名: ");
    fgets(newStu.name, sizeof(newStu.name), stdin);
    // 移除换行符
    newStu.name[strcspn(newStu.name, "\n")] = '\0';

    // 输入ID（确保唯一）
    while (1)
    {
        printf("请输入学生ID: ");
        if (scanf("%d", &newStu.id) != 1)
        {
            printf("ID必须是数字！\n");
            flushInput();
            continue;
        }
        if (isIdExists(db, newStu.id))
        {
            printf("该ID已存在！请重新输入: ");
            continue;
        }
        break;
    }

    // 输入各科目成绩
    printf("请输入%d门课程的成绩（0-100）:\n", COURSE_COUNT);
    for (int i = 0; i < COURSE_COUNT; i++)
    {
        printf("课程%d: ", i + 1);
        newStu.score[i] = inputScore();
    }

    // 添加到数据库
    db->stu[db->count] = newStu;
    db->count++;
    printf("学生信息添加成功！\n");
    pauseScreen();
    clearScreen();
}

void updateStudent(StudentDB *db)
{
    if (db->count == 0)
    {
        printf("暂无学生信息，无法修改！\n");
        pauseScreen();
        clearScreen();
        return;
    }

    int id;
    printf("请输入要修改的学生ID: ");
    scanf("%d", &id);
    flushInput();

    // 查找学生
    for (int i = 0; i < db->count; i++)
    {
        if (db->stu[i].id == id)
        {
            // 修改姓名
            printf("当前姓名: %s，请输入新姓名: ", db->stu[i].name);
            fgets(db->stu[i].name, sizeof(db->stu[i].name), stdin);
            db->stu[i].name[strcspn(db->stu[i].name, "\n")] = '\0';

            // 修改成绩
            printf("请重新输入%d门课程的成绩（0-100）:\n", COURSE_COUNT);
            for (int j = 0; j < COURSE_COUNT; j++)
            {
                printf("课程%d（当前: %.1f）: ", j + 1, db->stu[i].score[j]);
                db->stu[i].score[j] = inputScore();
            }

            printf("学生信息修改成功！\n");
            pauseScreen();
            clearScreen();
            return;
        }
    }

    printf("未找到ID为%d的学生！\n", id);
    pauseScreen();
    clearScreen();
}

void deleteStudent(StudentDB *db)
{
    if (db->count == 0)
    {
        printf("数据库为空，没有学生可删除。\n");
        pauseScreen();
        clearScreen();
        return;
    }

    int id;
    printf("请输入要删除的学生ID: ");
    // 增加输入检查
    if (scanf("%d", &id) != 1)
    {
        printf("输入无效！\n");
        flushInput();
        pauseScreen();
        clearScreen();
        return;
    }
    flushInput();

    int foundIndex = -1;
    // 1. 查找学生
    for (int i = 0; i < db->count; i++)
    {
        if (db->stu[i].id == id)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        printf("未找到 ID 为 %d 的学生。\n", id);
        pauseScreen();
        clearScreen();
        return;
    }

    // 2. 显示详情并请求确认
    Student *target = &db->stu[foundIndex];
    printf("\n即将删除学生: [ %s ] (ID: %d)\n", target->name, target->id);
    printf("警告：此操作不可恢复！\n");
    printf("确定要删除吗？(输入 y 确认，其他键取消): ");

    char confirm;
    scanf("%c", &confirm);
    flushInput();

    if (confirm != 'y' && confirm != 'Y')
    {
        printf(">> 已取消删除操作。\n");
        pauseScreen();
        clearScreen();
        return;
    }

    // 3. 执行物理删除 (数组移位)
    // 从 foundIndex 开始，后一个覆盖前一个
    for (int i = foundIndex; i < db->count - 1; i++)
    {
        db->stu[i] = db->stu[i + 1];
    }

    // 4. 更新计数并清空末尾多余数据
    db->count--;
    // 将原数组最后一个位置清零，防止残留数据
    memset(&db->stu[db->count], 0, sizeof(Student));

    printf(">> 删除成功！\n");
    pauseScreen();
    clearScreen();
}

void saveData(const StudentDB *db)
{
    FILE *fp = fopen("student_data.dat", "wb"); // 打开二进制写模式
    if (fp == NULL)
    {
        printf("警告：无法保存数据文件！\n");
        return;
    }

    // 1. 先写入学生数量
    fwrite(&db->count, sizeof(int), 1, fp);

    // 2. 写入有效的学生数组部分 (只写有数据的部分，节省空间)
    if (db->count > 0)
    {
        fwrite(db->stu, sizeof(Student), db->count, fp);
    }

    fclose(fp);
    printf(">> 数据已成功保存到 student_data.dat\n");
}

void loadData(StudentDB *db)
{
    FILE *fp = fopen("student_data.dat", "rb"); // 打开二进制读模式
    if (fp == NULL)
    {
        // 文件不存在是正常的（第一次运行），直接返回
        return;
    }

    // 1. 读取学生数量
    if (fread(&db->count, sizeof(int), 1, fp) != 1)
    {
        db->count = 0; // 读取失败或文件为空
        fclose(fp);
        return;
    }

    // 2. 读取学生数据
    if (db->count > 0)
    {
        // 注意：这里最好加一个检查，防止文件中的 count 超过数组最大容量 STUDENT_COUNT
        if (db->count > STUDENT_COUNT)
            db->count = STUDENT_COUNT;

        fread(db->stu, sizeof(Student), db->count, fp);
    }

    fclose(fp);
    printf(">> 已加载 %d 条历史数据。\n", db->count);
}