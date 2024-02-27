#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>

#define MKEY 1234
#define MAXSIZE 1000

typedef struct {
	char name[MAXSIZE];
	long roll;
	int no_of_students;
} student;

typedef struct {
	long type;
	student s;
} msg;
