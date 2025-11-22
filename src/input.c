#include <stdio.h>
#include "input.h"
#include "calc.h"
#include "grade.h"

float inputScore()
{
    float s;
    scanf("%f", &s);
    return s;
}

int validateScore(float s)
{
    return (s >= 0 && s <= 100);
}

void inputStudentInfo(StudentDB *db)
{
    // TODO: 由学生B实现
}

void updateStudent(StudentDB *db)
{
    // TODO: 由学生B实现
}

void deleteStudent(StudentDB *db)
{
    // TODO: 由学生B实现
}
