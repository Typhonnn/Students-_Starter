#pragma once

#include "Student.h"

typedef enum { text, binary } eFileType;


typedef struct {
	int	classCount;
	int countInClass;
	Student** studentArr;
} School;

int createSchoolFromFile(char* fileName, School* school, eFileType fileType);

int createSchoolFromFileBinary(FILE* file, School* school);

int createSchoolFromFileTxt(FILE* file, School* school);

void saveSchoolToBinaryFile(char* fileName, School* school);

void sortEachClassInSchool(School* school, int(*compare)(const void* st1, const void* st2));

void searchStudentInSchool(School* school, int id);

void showSchool(School* school);

void freeSchool(School* school);
