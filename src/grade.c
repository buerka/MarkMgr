#include <stdio.h>
#include "grade.h"

char evaluateGrade(float avg)
{
    // TODO: E 负责设计规则
    return 'A';
}

void generateComment(Student *stu)
{
    // TODO: E 负责
}

void evaluateAll(StudentDB *db)
{
    for (int i = 0; i < db->count; i++)
    {
        db->stu[i].grade = evaluateGrade(db->stu[i].average);
        generateComment(&db->stu[i]);
    }
}

void gradeDistribution(const StudentDB *db)
{
    // TODO: E 负责
}
