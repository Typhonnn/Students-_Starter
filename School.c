//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "School.h"

int createSchoolFromFile(char* fileName, School* school, eFileType fileType) {
	FILE* file = NULL;
	if (fileType == text) {
		fopen_s(&file, fileName, "r");
	}
	else if (fileType == binary) {
		fopen_s(&file, fileName, "rb");
	}
	if (file == NULL) {
		printf("Failed to open file! ABORTING!");
		return 0;
	}
	if (school == NULL) {
		printf("Please initialize memory for school! ABORTING!");
		fclose(file);
		return 0;
	}
	if (fileType == text) {
		return createSchoolFromFileTxt(file, school);
	}
	else if (fileType == binary) {
		return createSchoolFromFileBinary(file, school);
	}
	fclose(file);
	return 0; //false
}

int createSchoolFromFileBinary(FILE* file, School* school) {
	int i, j;
	if (school == NULL) {
		printf("School needs to be initialized! ABORTING!");
		fclose(file);
		return 0;
	}
	if (!feof(file)) {
		fread(&school->classCount, sizeof(int), 1, file);
		fread(&school->countInClass, sizeof(int), 1, file);
	}
	school->studentArr = calloc(school->classCount, sizeof(Student*));
	if (school->studentArr == NULL) {
		printf("Failed to allocate memory for students! ABORTING!");
		fclose(file);
		return 0;
	}
	for (i = 0; i < school->classCount && !feof(file); i++) {
		school->studentArr[i] = calloc(school->countInClass, sizeof(Student));
		if (school->studentArr[i] == NULL) {
			printf("Failed to allocate memory for students! ABORTING!");
			fclose(file);
			return 0;
		}
		for (j = 0; j < school->countInClass && !feof(file); j++) {
			fread(&school->studentArr[i][j].id, sizeof(int), 1, file);
			unsigned char temp = 0;
			unsigned int mask = 0;
			fread(&temp, sizeof(unsigned char), 1, file);
			school->studentArr[i][j].grade |= temp & 127;
			mask = temp & 128;
			school->studentArr[i][j].type |= mask >> 7;
		}
	}
	fclose(file);
	return 1;
}

int createSchoolFromFileTxt(FILE* file, School* school) {
	int i, j;
	if (school == NULL) {
		printf("School needs to be initialized! ABORTING!");
		fclose(file);
		return 0;
	}
	if (!feof(file)) {
		fscanf_s(file, "%d", &school->classCount);
		fscanf_s(file, "%d", &school->countInClass);
	}
	school->studentArr = calloc(school->classCount, sizeof(Student*));
	if (school->studentArr == NULL) {
		printf("Failed to allocate memory for students! ABORTING!");
		fclose(file);
		return 0;
	}
	for (i = 0; i < school->classCount; i++) {
		school->studentArr[i] = calloc(school->countInClass, sizeof(Student));
		for (j = 0; j < school->countInClass; j++) {
			if (school->studentArr[i] == NULL) {
				printf("Failed to allocate memory for students in class! ABORTING!");
				fclose(file);
				return 0;
			}
			createStudentFromFileTxt(file, &(school->studentArr[i][j]));
		}
	}
	fclose(file);
	return 1;
}

void saveSchoolToBinaryFile(char* fileName, School* school) {
	int i, j;
	if (school == NULL) {
		printf("School is NULL! Nothing to save! ABORTING!");
		return;
	}
	FILE* file = NULL;
	fopen_s(&file, fileName, "wb");
	if (file == NULL) {
		printf("Failed to open binary file! ABORTING!");
		return;
	}
	fwrite(&school->classCount, sizeof(int), 1, file);
	fwrite(&school->countInClass, sizeof(int), 1, file);
	for (i = 0; i < school->classCount; i++) {
		for (j = 0; j < school->countInClass; j++) {
			fwrite(&school->studentArr[i][j].id, sizeof(int), 1, file);
			unsigned char temp = 0;
			temp |= school->studentArr[i][j].grade & 127;
			temp |= (school->studentArr[i][j].type << 7) & 128;
			fwrite(&temp, sizeof(unsigned char), 1, file);
		}
	}
	fclose(file);
}

void sortEachClassInSchool(School* school, int(*compare)(const void* st1, const void* st2)) {
	int i;
	if (school == NULL) {
		printf("Failed to sort school!");
		return;
	}
	for (i = 0; i < school->classCount; i++) {
		qsort(school->studentArr[i], school->countInClass, sizeof(Student), compare);
	}
}

void searchStudentInSchool(School* school, int id) {
	sortEachClassInSchool(school, compareStudentDegreeId);
	int i;
	Student temp;
	Student *foundStudent;
	temp.id = id;
	if (school == NULL) {
		printf("No school found! Failed to bsearch! ABORTING!");
		return;
	}
	for ( i = 0; i < school->classCount; i++)	{
		foundStudent = bsearch(&temp, school->studentArr[i], school->countInClass, sizeof(Student), compareStudentId);
			if (foundStudent != NULL) {
				printf("Student found in class No.%d:\n", i + 1);
				showStudent(foundStudent);
				return;
			}
	}
	printf("Student Not Found...\n");
}

void showSchool(School* school) {
	int i, j;
	if (school == NULL) {
		return;
	}
	for (i = 0; i < school->classCount; i++) {
		printf("Class No.%d :\n", i + 1);
		for (j = 0; j < school->countInClass; j++) {
			printf("Student No.%d : %d %d %d\n", j + 1, school->studentArr[i][j].id, school->studentArr[i][j].type, school->studentArr[i][j].grade);
		}
	}
}

void freeSchool(School* school) {
	int i;
	if (school == NULL) {
		return;
	}
	if (school->studentArr == NULL) {
		return;
	}
	Student* st1 = &school->studentArr[1][3];
	for (i = 0; i < school->classCount; i++) {
		free(school->studentArr[i]);
	}
	free(school->studentArr);
}

