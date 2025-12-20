#ifndef ENROLL_H
#define ENROLL_H

#include "student.h"

void handleEnrollMenu(StudentDB *stuDB, const CourseDB *courseDB);
void registerScore(StudentDB *stuDB, const CourseDB *courseDB);

#endif