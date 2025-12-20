#ifndef INPUT_H
#define INPUT_H

#include "student.h"

int findStudentIndex(const StudentDB *db, int id);

void handleStudentInfoMenu(StudentDB *db);
void saveData(const StudentDB *db, const CourseDB *cdb); // 也要保存课程
void loadData(StudentDB *db, CourseDB *cdb);

#endif