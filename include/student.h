#ifndef STUDENT_H
#define STUDENT_H

#define COURSE_COUNT 3
#define STUDENT_COUNT 5

typedef struct
{
    char name[20];
    int id;
    float score[COURSE_COUNT];
    float total;
    float average;
    char grade;
    char comment[100];
} Student;

typedef struct
{
    Student stu[STUDENT_COUNT];
    int count;
} StudentDB;

#endif
