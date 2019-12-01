#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>

void show_info();

int main(){
	struct utmp current_record;
	int utmpfd;
	int reclen=sizeof(current_record);

	if((utmpfd=open(UTMP_FILE, O_RDONLY)) ==-1){
		perror(UTMP_FILE);
		exit(1);
	}
	while(read(utmpfd, &current_record, reclen)==reclen){
		show_info(&current_record);
	}

	close(utmpfd);
	return 0;
}

void show_info(struct utmp *utbufp){
	if(utbufp->ut_type !=USER_PROCESS)
		return;
	printf("%s\n", utbufp->ut_name);
}
