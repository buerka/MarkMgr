#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "input.h"
#include "course.h"
#include "enroll.h"
#include "utils.h"
#include "calc.h"
#include "grade.h"
#include "query.h"

// 全局数据
StudentDB globalStuDB = {0};
CourseDB globalCourseDB = {0};

int loginSystem()
{
    int choice;
    printf("\n==================================\n");
    printf("   综合教务管理系统 - 登录\n");
    printf("==================================\n");
    printf("1. 管理员登录 (默认密码 admin)\n");
    printf("2. 退出系统\n");
    printf("请选择: ");

    if (scanf("%d", &choice) != 1)
    {
        flushInput();
        return 0;
    }
    flushInput();

    if (choice == 1)
    {
        char pwd[20];
        printf("请输入管理员密码: ");
        fgets(pwd, 20, stdin);
        pwd[strcspn(pwd, "\n")] = 0;

        if (strcmp(pwd, "admin") == 0)
        {
            printf("登录成功！\n");
            return 1; // 登录成功
        }
        else
        {
            printf("❌ 密码错误！\n");
            return 0;
        }
    }
    else if (choice == 2)
    {
        exit(0);
    }
    return 0;
}

// 主菜单
void showMainMenu()
{
    printf("\n===== 教务系统主菜单 =====\n");
    printf("1. 学生信息管理 (录入/查询)\n");
    printf("2. 课程信息维护 (增删改)\n");
    printf("3. 学生选课管理 (选课/退课)\n");
    printf("---------------------------\n");
    printf("4. 查询个人成绩单\n");
    printf("5. 显示所有学生成绩\n");
    printf("6. 成绩排名 (按总分)\n");
    printf("7. 学科分析报告\n");
    printf("8. 等级分布统计\n");
    printf("---------------------------\n");
    printf("0. 退出登录\n");
    printf("请选择: ");
}

// 辅助函数：统一刷新数据
// 在显示之前，先重新计算总分、平均分和评级，确保数据最新
void refreshData()
{
    calcAll(&globalStuDB);
    evaluateAll(&globalStuDB);
}

int main()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    // 加载数据
    loadData(&globalStuDB, &globalCourseDB);

    while (1)
    {
        // 1. 登录循环
        if (!loginSystem())
        {
            continue;
        }

        // 2. 业务菜单循环
        int logout = 0;
        while (!logout)
        {
            showMainMenu();
            int op;
            if (scanf("%d", &op) != 1)
            {
                flushInput();
                continue;
            }
            flushInput();

            switch (op)
            {
            case 1:
                handleStudentInfoMenu(&globalStuDB);
                break;
            case 2:
                handleCourseMenu(&globalCourseDB);
                break;
            case 3:
                handleEnrollMenu(&globalStuDB, &globalCourseDB);
                break;
            case 4:            // 查询个人成绩单
                refreshData(); // 先计算，防止新录的成绩没算进总分
                queryById(&globalStuDB, &globalCourseDB);
                break;
            case 5:
                refreshData();
                displayAll(&globalStuDB);
                break;
            case 6:
                refreshData();
                sortByTotal(&globalStuDB); // 排序
                displayAll(&globalStuDB);  // 显示
                break;
            case 7: // 学科分析
                courseAnalysis(&globalStuDB, &globalCourseDB);
                break;
            case 8: // 等级分布
                refreshData();
                gradeDistribution(&globalStuDB);
                break;
            case 0:
                logout = 1;
                printf(">> 已退出登录。\n");
                saveData(&globalStuDB, &globalCourseDB);
                break;
            default:
                printf("无效选项！\n");
            }
        }
    }
    return 0;
}