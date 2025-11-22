#include <stdio.h>
#include "calc.h"

float calcTotal(const Student *stu)
{
    float t = 0;
    for (int i = 0; i < COURSE_COUNT; i++)
        t += stu->score[i];
    return t;
}

float calcAverage(const Student *stu)
{
    return stu->total / COURSE_COUNT;
}

void calcAll(StudentDB *db)
{
    for (int i = 0; i < db->count; i++)
    {
        db->stu[i].total = calcTotal(&db->stu[i]);
        db->stu[i].average = calcAverage(&db->stu[i]);
    }
}

void sortByTotal(StudentDB *db)
{
    // TODO: C、D 负责
}

void courseAnalysis(const StudentDB *db)
{
    // TODO: C、D 负责
}
