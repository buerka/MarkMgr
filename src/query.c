#include <stdio.h>
#include <string.h>
#include "query.h"
#include "utils.h"

static const Student *findStudentById(const StudentDB *db, int id)
{
    for (int i = 0; i < db->count; i++)
    {
        if (db->stu[i].id == id)
        {
            return &db->stu[i];
        }
    }
    return NULL;
}

void queryById(const StudentDB *db)
{
    int id;
    printf("请输入要查询的学生ID: ");
    if (scanf("%d", &id) != 1)
    {
        printf("输入无效！\n");
        flushInput();
        pauseScreen();
        return;
    }
    flushInput(); // 清除回车

    const Student *stu = findStudentById(db, id);

    if (stu != NULL)
    {
        // 找到学生，显示详细成绩单
        printTranscript(stu);
    }
    else
    {
        printf("未找到ID为 %d 的学生记录。\n", id);
    }

    pauseScreen();
    clearScreen();
}

void displayStudent(const Student *stu)
{
    // 打印表格中的一行
    // 格式：ID(8) 姓名(15) 总分(8) 平均分(8) 等级(6)
    printf("%-8d %-15s %-8.1f %-8.1f %-6c %s\n",
           stu->id,
           stu->name,
           stu->total,
           stu->average,
           stu->grade ? stu->grade : '-', // 如果还没评级显示 -
           stu->comment[0] ? "已评" : "-");
}

void displayAll(const StudentDB *db)
{
    if (db->count == 0) {
        printf("数据库为空，暂无学生信息。\n");
        pauseScreen();
        clearScreen();
        return;
    }

    // ============================================================
    // 1. 打印表头 (完全手动对齐)
    // ============================================================
    // 视觉宽度设计：
    // 排名(6) | ID(10) | 姓名(14) | 总分(10) | 平均分(10) | 等级(8) | 状态
    printf("\n");
    printf("排名  ID        姓名          总分      平均分    等级    状态\n");
    printf("----------------------------------------------------------------------\n");
    
    // ============================================================
    // 2. 打印数据 (严格匹配上面的视觉宽度)
    // ============================================================
    for (int i = 0; i < db->count; i++) {
        const Student *stu = &db->stu[i];
        
        // [列1] 排名 (占6格)
        printf("%-6d", i + 1);
        
        // [列2] ID (占10格)
        printf("%-10d", stu->id);
        
        // [列3] 姓名 (占14格，手动处理中文)
        printf("%s", stu->name);
        // 计算需要补多少空格
        int len = strlen(stu->name);
        int padding = 0;
        if (len == 6) padding = 10;      // 2个汉字(占4格) -> 补10空
        else if (len == 9) padding = 8;  // 3个汉字(占6格) -> 补8空
        else if (len == 12) padding = 6; // 4个汉字(占8格) -> 补6空
        else padding = 14 - len;         // 英文名兜底
        
        if (padding < 0) padding = 0;
        for(int k=0; k<padding; k++) printf(" ");

        // [列4] 总分 (占10格)
        printf("%-10.1f", stu->total);

        // [列5] 平均分 (占10格)
        printf("%-10.1f", stu->average);

        // [列6] 等级 (占8格)
        printf("%-8c", stu->grade ? stu->grade : '-');
               
        // [列7] 状态
        if (stu->comment[0]) printf("已评");
        else printf("-");
        
        printf("\n");
    }
    
    printf("----------------------------------------------------------------------\n");
    printf("共找到 %d 条记录。\n", db->count);
    
    pauseScreen();
    clearScreen();
}

void printTranscript(const Student *stu)
{
    // 显示详细的单人成绩单
    printf("\n========= 学生成绩报告 =========\n");
    printf(" 学号 : %-10d  姓名 : %s\n", stu->id, stu->name);
    printf("------------------------------\n");

    printf("【各科成绩】\n");
    for (int i = 0; i < COURSE_COUNT; i++)
    {
        printf("  课程 %d : \t%5.1f 分\n", i + 1, stu->score[i]);
    }

    printf("------------------------------\n");
    printf(" 总分   : \t%5.1f\n", stu->total);
    printf(" 平均分 : \t%5.1f\n", stu->average);
    printf(" 等级   : \t[ %c ]\n", stu->grade ? stu->grade : '-'); // 防止空字符
    printf(" 评语   : \t%s\n", stu->comment[0] ? stu->comment : "暂无评语");
    printf("==============================\n");
}
