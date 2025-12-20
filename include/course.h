#ifndef COURSE_H
#define COURSE_H

#include "student.h"

void handleCourseMenu(CourseDB *db);
int findCourseIndex(const CourseDB *db, int id);

#endif