#include <stdio.h>
#include <string.h>
#include "input.h"
#include "utils.h"

// 查找学生索引
int findStudentIndex(const StudentDB *db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->stu[i].id == id) return i;
    }
    return -1;
}

static void inputStudentInfo(StudentDB *db) {
    if (db->count >= MAX_STUDENTS) {
        printf("❌ 学生人数已达上限，无法注册！\n");
        return;
    }

    Student newStu = {0};

    // 1. 学号录入与去重
    while (1) {
        printf("请输入学号 (数字): ");
        if (scanf("%d", &newStu.id) != 1) {
            printf("输入格式错误。\n");
            flushInput(); continue;
        }
        flushInput();

        if (findStudentIndex(db, newStu.id) != -1) {
            printf("⚠️ 学号 %d 已存在，请重新输入。\n", newStu.id);
        } else {
            break; // 学号可用
        }
    }

    // 2. 姓名
    printf("请输入姓名: ");
    fgets(newStu.name, 20, stdin);
    newStu.name[strcspn(newStu.name, "\n")] = 0;
    if (strlen(newStu.name) == 0) strcpy(newStu.name, "Unknown");

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
static void listStudents(const StudentDB *db) {
    printf("\n--- 学生列表 ---\n");
    for(int i=0; i<db->count; i++) {
        printf("ID:%-8d 姓名:%-10s 已选课:%d门\n", 
               db->stu[i].id, db->stu[i].name, db->stu[i].selectedCount);
    }
}

void handleStudentInfoMenu(StudentDB *db) {
    while(1) {
        printf("\n--- 学生信息管理 ---\n");
        printf("1. 录入新生\n2. 查看所有学生\n0. 返回\n请选择: ");
        int op;
        scanf("%d", &op);
        flushInput();
        if (op == 0) break;
        if (op == 1) inputStudentInfo(db);
        if (op == 2) listStudents(db);
    }
}

// 注意：loadData 和 saveData 需要你自己根据新的 Student 结构体和 CourseDB 重写
// 暂时留空防止编译错误
void saveData(const StudentDB *db, const CourseDB *cdb) { printf("保存功能待更新...\n"); }
void loadData(StudentDB *db, CourseDB *cdb) { printf("加载功能待更新...\n"); }