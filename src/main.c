#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "input.h"
#include "calc.h"
#include "grade.h"
#include "query.h"
#include "utils.h"

void showMainMenu()
{
    printf("\n===== 学生成绩管理系统 =====\n");
    printf("1. 添加学生\n");
    printf("2. 修改学生信息\n");
    printf("3. 删除学生\n");
    printf("4. 查询学生\n");
    printf("5. 显示全部成绩\n");
    printf("6. 成绩排名\n");
    printf("7. 学科分析报告\n");
    printf("8. 等级分布统计\n");
    printf("0. 退出\n");
    printf("请选择：");
}

void handleUserChoice(StudentDB *db)
{
    int op;

    if (scanf("%d", &op) != 1)
    {
        printf("输入无效，请输入数字！\n");
        flushInput();
        pauseScreen();
        return;
    }

    flushInput();

    switch (op)
    {
    case 1:
        inputStudentInfo(db);
        calcAll(db);
        evaluateAll(db);
        saveData(db);
        break;

    case 2:
        updateStudent(db);
        calcAll(db);
        evaluateAll(db);
        saveData(db);
        break;

    case 3:
        deleteStudent(db);
        calcAll(db);
        evaluateAll(db);
        saveData(db);
        break;

    case 4:
        queryById(db);
        break;

    case 5:
        sortById(db);
        displayAll(db);
        break;

    case 6:
        sortByTotal(db);
        displayAll(db);
        break;

    case 7:
        courseAnalysis(db);
        break;

    case 8:
        gradeDistribution(db);
        break;

    case 0:
        saveData(db);
        exit(0);

    default:
        printf("无效输入！\n");
    }
}

int main()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    StudentDB db = {.count = 0};

    loadData(&db);
    calcAll(&db);

    while (1)
    {
        showMainMenu();
        handleUserChoice(&db);
    }

    return 0;
}
