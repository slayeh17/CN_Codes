#include "msgq.h"

int main() {


	msg mname, mroll, m_name_rcv, m_roll_rcv;
	int msgid = msgget(MKEY, IPC_CREAT | 0666);
	mname.type = 1;
	mroll.type = 2;

	int i=0;
	int N;
	printf("Enter the number of students: ");
	scanf("%d", &N);
	student stu[N], stuName[N], stuRoll[N];

	printf("Enter name & roll:\n");
	
	//Sending Name & Roll one by one
	for(; i<N; i++) {
		printf("Student %d: \n", i+1);
		printf("Name: ");
		scanf("%s", stu[i].name);
		printf("Roll: ");
		scanf("%ld", &stu[i].roll);

		stu[i].no_of_students = N;

		mname.s = stu[i];
		msgsnd(msgid, &mname, sizeof(mname), 0);
		perror("msgsnd");
		mroll.s = stu[i];
		msgsnd(msgid, &mroll, sizeof(mroll), 0);
		perror("msgsnd");
	}

	//Recieving sorted names from sortName.c
	printf("Sorted Names:\n");
	i=0;
	while(msgrcv(msgid, &m_name_rcv, sizeof(m_name_rcv), 3, 0)!=-1) {
		stuName[i] = m_name_rcv.s;
		printf("%s\t", stuName[i].name);
		i++;

		if(i == N) {
			break;
		}
	}

	printf("\n");

	//Recieving sorted rolls from sortRoll.c
	printf("Sorted Roll:\n");
	i=0;
	while(msgrcv(msgid, &m_roll_rcv, sizeof(m_roll_rcv), 4, 0)!=-1) {
		stuRoll[i] = m_roll_rcv.s;
		printf("%ld\t", stuRoll[i].roll);
		i++;

		if(i == N) {
			break;
		}
	}
	printf("\n");

	msgctl(msgid, IPC_RMID, NULL);	
}
