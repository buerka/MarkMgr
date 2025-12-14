#ifndef INPUT_H
#define INPUT_H

#include "student.h"

void inputStudentInfo(StudentDB *db);
float inputScore();
int validateScore(float score);

void updateStudent(StudentDB *db);
void deleteStudent(StudentDB *db);

void saveData(const StudentDB *db);
void loadData(StudentDB *db);

#endif
