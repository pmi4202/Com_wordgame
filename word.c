#include	<stdio.h>
#include	<unistd.h>	
#include	<stdlib.h>	
#include	<fcntl.h>
#include	<sys/wait.h>
#include	<string.h>
 

struct word {
	char *subject;
	char *word;
 	char *word_mean;
};

struct word wo;
struct word getword();
//여기서 단어 받고 저장소로 보내기.
int main()
{
//FILE *fp;
//fp = fopen("indivi", "w");
//fprintf("%s %s %s " , wo.subject, wo.word, wo.word_mean);
//수정해야함...
getword();
//printf("%s , %s , %s ", wo.subject, wo.word, wo.word_mean);
return 0;
}

//각 단어와 의미 받아오는 함수
struct word getword(){
char input[BUFSIZ];
char tmp;
int num;

//과목 입력
printf("과목 입력 : ");
scanf("%s", input);
getchar();
tmp = (char*)malloc(strlen(input)+1);
strcpy(&tmp, input);
wo.subject = &tmp;

//단어 입력 
printf("단어입력 : ");
scanf("%s", input);
getchar();
tmp = (char*)malloc(strlen(input)+1);
strcpy(&tmp, input);
wo.word = &tmp;

//단어 의미 입력
printf("단어의 의미 입력 : ");
scanf("%s", input);
getchar();
tmp = (char*)malloc(strlen(input)+1);
strcpy(&tmp, input);
wo.word_mean =&tmp;

return wo;
}
