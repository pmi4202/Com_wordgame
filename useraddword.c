#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct word {
 char *subject;
 char *word;
 char *word_mean;
};

 

struct word getWord();
void file_open();

void main(){

 struct word getword;
 FILE *fp;
 char in;

 fp = fopen("indivi.txt", "w"); //쓰기
  while(1) 
  {
   getword = getWord();
 fprintf(fp, "과목 : %s\n단어 : %s\n의미: %s\n", getword.subject, getword.word, getword.word_mean);
	if(strcmp(getword.subject, "q")==0) break; 
 }
 
// fprintf(fp, "과목 : %s\n단어 : %s\n의미: %s\n", getword.subject, getword.word, getword.word_mean);
       	fclose(fp);	
         file_open();
}

 

struct word getWord(){
 struct word wo;
 char input[BUFSIZ];
 char *tmp;
 int num;
 
//과목 입력
 printf("과목 입력 : ");
 scanf("%s", input);
 getchar();
 tmp = (char*)malloc(strlen(input)+1);
 strcpy(tmp, input);
 wo.subject = tmp;

//단어 입력
 printf("단어 입력: ");
 scanf("%s", input);
 getchar();
 tmp = (char*)malloc(strlen(input)+1);
 strcpy(tmp, input);
 wo.word = tmp;
 
//단어 뜻
 printf("의미 : ");
 scanf("%s", input);
 getchar();
 tmp = (char*)malloc(strlen(input)+1);
 strcpy(tmp, input);
 wo.word_mean = tmp;
 
 return wo;
}

 
//파일 출력
void file_open()
{
 int pid;
 int fd;

 printf("\n\n내 학습장 \n\n");
 
 if( (pid = fork() ) == -1 ){
  perror("fork");
  exit(1);
 }

 if( pid == 0 ){
  close(0);   /* close */
  fd = fopen("indivi.txt", "r"); 
  execlp("cat", "cat", NULL); 
  perror("execlp");
  exit(1);
 }

 if( pid != 0 ){
  wait(NULL);
 }
} 

