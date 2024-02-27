#include "msgq.h"

int main() {
	msg mname, msnd;
	int msgid = msgget(MKEY, IPC_CREAT | 0666);
	student stu[MAXSIZE];
	int i=0, j=0, n=0;

	while(msgrcv(msgid, &mname, sizeof(mname), 1, 0)!=-1) {
		stu[i] = mname.s;
		n++;
		printf("Name: %s\n", stu[i].name);

		if(n == stu[i].no_of_students) {
			break;
		}

		i++;
	}

	for(i=0;i<n;i++){
 		for(j=i+1;j<n;j++){
      			if(strcmp(stu[i].name,stu[j].name)>0){
				char s[1000];
         			strcpy(s,stu[i].name);
         			strcpy(stu[i].name,stu[j].name);
         			strcpy(stu[j].name,s);
      			}
   		}
	}

	printf("Sorted Names: \n");	
	for(i=0; i<n; i++) {
		printf("%s\t", stu[i].name);
	}

	printf("\n");
	
	msnd.type = 3;
	for(i=0; i<n; i++) {
		msnd.s = stu[i];
		msgsnd(msgid, &msnd, sizeof(msnd), 0);
	}
	
}
