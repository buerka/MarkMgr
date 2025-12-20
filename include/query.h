#ifndef QUERY_H
#define QUERY_H

#include "student.h"

void queryById(const StudentDB *sDB, const CourseDB *cDB);
void displayAll(const StudentDB *sDB); // 简略列表不需要课程库

#endif