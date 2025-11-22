#ifndef QUERY_H
#define QUERY_H

#include "student.h"

void queryById(const StudentDB *db);
void displayStudent(const Student *stu);
void displayAll(const StudentDB *db);
void printTranscript(const Student *stu);

#endif
