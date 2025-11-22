#ifndef GRADE_H
#define GRADE_H

#include "student.h"

char evaluateGrade(float avg);
void generateComment(Student *stu);
void evaluateAll(StudentDB *db);
void gradeDistribution(const StudentDB *db);

#endif
