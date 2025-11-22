#ifndef CALC_H
#define CALC_H

#include "student.h"

float calcTotal(const Student *stu);
float calcAverage(const Student *stu);

void calcAll(StudentDB *db);
void sortByTotal(StudentDB *db);
void courseAnalysis(const StudentDB *db);

#endif
