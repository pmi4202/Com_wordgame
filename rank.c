#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void rankpage();
void find_file_1();
void find_file_2();
void find_file_3();
void find_file_4();

int main(){

	rankpage();
	return 0;
}

void rankpage(){
int subject;
printf("~~~~~~~~~~~~~~~~ rank page~~~~~~~~~~~~~~~\n");
printf("1.subject_1 \n2.subject_2 \n3.subject3 \n4.subject4 \n5. 뒤로가기\n");

scanf("%d", &subject);

switch(subject){
	//각각 랭킹 파일 불러오기.
	case 1:
		find_file_1();
		break;
	case 2:
		find_file_2();
		break;
	case 3:
		find_file_3();
		break;
	case 4:
		find_file_4();
		break;
	}
}

void find_file_1(){
int pid;
int fd;
 if( (pid = fork() ) == -1 ){
  perror("fork");
  exit(1);
 }

 if( pid == 0 ){
  close(0);
  fd =fopen("rank1.txt", "r" );
  execlp("sort", "sort","-r", NULL);
  perror("execlp");
  exit(1);
 }

 if( pid != 0 ){
  wait(NULL);
 }
}

void find_file_2(){
int pid;
int fd;
 if( (pid = fork() ) == -1 ){
  perror("fork");
  exit(1);
 }

 if( pid == 0 ){
  close(0);
  fd =fopen("rank2.txt", "r" );
  execlp("sort", "sort","-r", NULL);
  perror("execlp");
  exit(1);
 }

 if( pid != 0 ){
  wait(NULL);
 }
}


void find_file_3(){
int pid;
int fd;
 if( (pid = fork() ) == -1 ){
  perror("fork");
  exit(1);
 }
 
 if( pid == 0 ){
  close(0);   
  fd =fopen("rank3.txt", "r" );
  execlp("sort", "sort","-r", NULL);
  perror("execlp");
  exit(1);
 }

 if( pid != 0 ){
  wait(NULL);
 }
}

void find_file_4(){
int pid;
int fd;
 if( (pid = fork() ) == -1 ){
  perror("fork");
  exit(1);
 }

 if( pid == 0 ){
  close(0);   
  fd =fopen("rank4.txt", "r" );
  execlp("sort", "sort","-r", NULL);
  perror("execlp");
  exit(1);
 }

 if( pid != 0 ){
  wait(NULL);
 } 
}

