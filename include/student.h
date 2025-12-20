#ifndef STUDENT_H
#define STUDENT_H

// 定义最大限制
#define MAX_STUDENTS 100
#define MAX_COURSES_POOL 50    // 课程库最大数量
#define MAX_STUDENT_COURSES 10 // 每个学生最多选多少门课

// --- 新增：课程结构体 (学生C/D维护) ---
typedef struct
{
    int id;        // 课程编号
    char name[20]; // 课程名称
    float credit;  // 学分 (0.5 - 6.0)
} Course;

// --- 新增：课程数据库 ---
typedef struct
{
    Course courses[MAX_COURSES_POOL];
    int count;
} CourseDB;

// --- 修改：选课记录结构体 ---
typedef struct
{
    int courseId; // 选修的课程ID
    float score;  // 成绩 (-1 表示已选课但未录入成绩)
} EnrolledCourse;

// --- 修改：学生结构体 (学生A/B/E/F维护) ---
// 原结构体需大幅修改以支持动态选课和登录
typedef struct
{
    int id;
    char name[20];     // 长度限制 19 + '\0'
    char password[20]; // 新增：登录密码

    // 选课列表：代替原来的 float score[COURSE_COUNT]
    EnrolledCourse selectedCourses[MAX_STUDENT_COURSES];
    int selectedCount; // 当前已选课程数

    // 统计数据
    float totalScore;   // 总分
    float average;      // 平均分 (新增)
    char grade;         // 综合等级 (A/B/C...) (新增)
    char comment[100];  // 评语 (新增)
} Student;

typedef struct
{
    Student stu[MAX_STUDENTS];
    int count;
} StudentDB;

#endif