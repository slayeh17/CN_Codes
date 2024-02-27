#include "msgq.h"

int main() {
	msg mroll, msnd;
	int msgid = msgget(MKEY, IPC_CREAT | 0666);
	student stu[MAXSIZE];
	int i=0, j=0, n=0;

	while(msgrcv(msgid, &mroll, sizeof(mroll), 2, 0)!=-1) {
		stu[i] = mroll.s;
		n++;
		printf("Roll: %ld\n", stu[i].roll);

		if(n == stu[i].no_of_students) {
			break;
		}

		i++;
	}

	for(i=1; i<n; i++) {
		j=i-1;
		long key = stu[i].roll;
		while(j>=0 && stu[j].roll > key) {
			stu[j+1].roll = stu[j].roll;
			j--;
		}
		stu[j+1].roll = key;
	}

	printf("Sorted Rolls: \n");	
	for(i=0; i<n; i++) {
		printf("%ld\t", stu[i].roll);
	}

	printf("\n");

	sleep(2);

	msnd.type = 4;
	for(i=0; i<n; i++) {
		msnd.s = stu[i];
		msgsnd(msgid, &msnd, sizeof(msnd), 0);
	}
	
}
