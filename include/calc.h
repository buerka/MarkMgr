#ifndef CALC_H
#define CALC_H

#include "student.h"

void calcAll(StudentDB *db);
void sortByTotal(StudentDB *db);
void courseAnalysis(const StudentDB *sDB, const CourseDB *cDB); 

#endif