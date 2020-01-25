//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Student.h"

int createStudentFromFileTxt(FILE* file, Student* student) {
	if (file == NULL) {
		return 0;
	}
	if (student == NULL) {
		return 0;
	}
	fscanf_s(file, "%d %d %d", &student->id, &student->type, &student->grade);
	return 1;
}

int compareStudentId(const void* st1, const void* id) {
	Student* tempSt = st1;
	int tempId = id;
	if (tempSt->id > tempId) {
		return 1; //tempSt id is greater.
	}
	else if (tempSt->id < tempId) {
		return -1; //tempSt id is smaller.
	}
	else {
		return 0; //student found!
	}
}

int compareStudentDegreeId(const void* st1, const void* st2) {
	Student* tempSt1 = st1;
	Student* tempSt2 = st2;
	if (tempSt1->type > tempSt2->type) {
		return 1; //st1 is greater.
	}
	else if (tempSt1->type < tempSt2->type) {
		return -1; //st2 is greater
	}
	else {
		if (tempSt1->id > tempSt2->id) {
			return 1; //st1 is greater
		}
		else if (tempSt1->id < tempSt2->id) {
			return -1; //st2 is greater
		}
		else {
			return 0; //st's are equal.
		}
	}
}

int compareStudentGradeDegree(const void* st1, const void* st2) {
	Student* tempSt1 = st1;
	Student* tempSt2 = st2;
	if (tempSt1->grade > tempSt2->grade) {
		return 1; //st1 is greater.
	}
	else if (tempSt1->grade < tempSt2->grade) {
		return -1; //st2 is greater
	}
	else {
		if (tempSt1->type > tempSt2->type) {
			return 1; //st1 is greater
		}
		else if (tempSt1->type < tempSt2->type) {
			return -1; //st2 is greater
		}
		else {
			return 0; //st's are equal.
		}
	}
}

