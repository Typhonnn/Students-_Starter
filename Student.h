#pragma once

typedef enum {first, second, eNofTypes} eDegreeType;
static const char* DegreeStr[eNofTypes];

typedef struct {
	int id;
	int	type;
	int grade;
}Student;

int createStudentFromFileTxt(FILE* file, Student* student);

int compareStudentId(const void* st1, const void* id);

int compareStudentDegreeId(const void* st1, const void* st2);

int compareStudentGradeDegree(const void* st1, const void* st2);