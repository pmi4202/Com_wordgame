#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <utmp.h>
#include <string.h>
#include <signal.h>
#include <termios.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
//directory
#include <dirent.h>
#include <sys/types.h>
//copy
#define BUFFERSIZE 4096


//개인학습에 쓰이는 struct..
struct word {
 char *word;
 char *word_mean;
};

typedef struct User
{
	int user_id, user_pw;
        char user_nick[20];
}User;

User loginPage(); // 로그인 페이지
void mainPage(); // 메인 페이지
void personalPage(); //개인학습 페이지
void rankchallenge(); //랭킹 도전 페이지
void rankpage(); // 랭크 확인

void find_file_1(); // 랭크 파일 소팅하는 곳
void find_file_2();
void find_file_3();
void find_file_4(); // 랭크 파일 소팅하는 곳

struct word getWord(); //개인학습 단어추가
void file_open(); // 개인학습 학습장 
void find_file();
void copy();

void game_search(); // 랭킹 도전 게임
int game_done(); // 랭킹 도전 게임

void updateRank(); //랭킹점수파일생성

void quiz_release();//랭킹 도전 문제 출제부분
void time_out(); //랭킹 도전 문제 출제부분
int skip = 0;//랭킹 도전 문제 출제부분
int correct;
User nowUser;

int main(){
   nowUser = loginPage();
   mainPage();
        return 0;
}

User loginPage(){
        char    regist;

        printf("********************* LOG-IN PAGE ***********************\n\n");
        printf("\tNickName : ");
        scanf("%s", nowUser.user_nick);
        printf("\tPassWord : ");
        scanf("%d", &(nowUser.user_pw));
        srand(time(NULL));
	nowUser.user_id = rand()%10000;
        
        /* search the id & pw */

        /* if user has no account */
        printf("해당 계정이 없습니다. 회원가입을 하시겠습니까? (y/n)\n");
   scanf("%c", &regist);
   do{        
      if(regist == 'y' || regist == 'Y'){
              /* register new account */
      }
      else if((regist == 'n' || regist == 'N')){
              /* back to the log-in page */
      }
      else
              printf("y/n 로 입력하세요\n");
      scanf("%c", &regist);
   } while( (regist != 'y') && (regist != 'Y') && (regist != 'n') && (regist != 'N'));

	return nowUser;
}

//메인 페이지
void mainPage(){
        int command;

        printf("********************** MAIN PAGE ***********************\n\n");
        printf("* 원하는 기능의 번호를 입력하세요.\n\t1. 랭킹 확인\n\t2. 랭킹 도전\n\t3. 개인 학습\n\t4. 프로그램 종료\n");
        scanf("%d", &command);
   
   switch(command){
      case 1:
         rankpage();
         break;
      case 2:
         rankchallenge();
         break;
      case 3:
         personalPage();
      case 4: exit(1);
   }
}

//랭킹 도전 페이지..
void rankchallenge(){
   int command;
   
   //랭킹 점수 생성에 필요한 변수
   int user_score = 0;
   char filename[BUFSIZ] = "rank1.txt";
   char filename2[BUFSIZ] = "rank2.txt";
   char filename3[BUFSIZ] = "rank3.txt";
   char filename4[BUFSIZ] = "rank4.txt";

        printf("********************** rank challenge ***********************\n\n");
        printf("* 원하는 과목의 번호를 입력하세요.\n\t1. 자료 구조\n\t2. 운영 체제\n\t3. 데이터 통신\n\t4. 자바\n\t5. 메인 화면으로 나가기\n");
        scanf("%d", &command);
   
   switch(command){
      case 1:
         game_search("data_structure");
         updateRank(filename, nowUser, user_score);
         rankchallenge();
      case 2:
         game_search("operating_system"); // 문제 출제 후 수정
         updateRank(filename, nowUser, user_score);
         rankchallenge();
         break;
      case 3:
         game_search("data_communication");   // 문제 출제 후 수정
         updateRank(filename, nowUser, user_score);
         rankchallenge();
         break;
      case 4: 
         game_search("java"); // 문제 출제 후 수정
         updateRank(filename, nowUser, user_score);
         rankchallenge();
         break;
      case 5: mainPage();
   }
}

void personalPage(){
        int command, fd;
   FILE *fp;
    char in;
   struct word getword;
   printf("******************* PERSONAL STUDY *********************\n\n");
        printf("* 원하는 기능의 번호를 입력하세요.\n\t1. 단어 추가\n\t2. 단어 삭제\n\t3. 학습하기\n\t4. 메인 화면으로 나가기\n");
        scanf("%d", &command);

   switch(command){
      case 1:
        //fd = open(nowUser.user_nick, O_CREAT, 0644);
	//fp = fdopen(fd, "w"); //사용자 닉네임으로 파일 열고 (없으면 만들어서) 쓰기
           while(1) 
              {
               getword = getWord();
            	if(strcmp(getword.word, "q")==0) break;
		copy("indivi.txt", "copy_f", 0);//word copy
		copy("copy_f", "indivi.txt", -2);//word count increase
             	fprintf(fp, "단어 : %s\n의미: %s\n",getword.word, getword.word_mean);
             }
         fclose(fp);
         sleep(2);
         personalPage();
      case 2:
	find_file();
         personalPage();
         break;
      case 3:
         printf("\n내 학습장 \n\n");
         file_open(nowUser.user_nick);
         sleep(3);
         personalPage();
      case 4:
         mainPage();
   }
}

//랭크 확인 페이지
void rankpage(){
int subject;
printf("******************* RANK CONFIRM *********************\n\n");
printf("* 원하는 과목의 번호를 입력하세요.\n\t1. 자료 구조\n\t2. 운영 체제\n\t3. 데이터 통신\n\t4. 자바\n\t5. 메인 화면으로 나가기\n");

scanf("%d", &subject);

switch(subject){
   //각각 랭킹 파일 불러오기.
   case 1:
      printf("\n자료 구조 랭킹\n"); 
      find_file_1();
      printf("\n");
      rankpage(); // 돌아가기.
   case 2:
      printf("\n운영 체제 랭킹\n");
      find_file_2();
      printf("\n");
      rankpage();
   case 3:
      printf("\n데이터 통신 랭킹\n");
      find_file_3();
      printf("\n");
      rankpage();
   case 4:
      printf("\n자바 랭킹\n");
      find_file_4();
      printf("\n");
      rankpage();
   case 5:
      mainPage();
   }
}

void find_file_1(){
int pid;
FILE *fd;
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
FILE *fd;
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
FILE *fd;
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
FILE *fd;
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

//개인학습에 단어 추가하는것.
struct word getWord(){
 struct word wo;
 char input[BUFSIZ];
 char *tmp;

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
//word delete
void find_file(){
	int del_num, file_size;
	FILE* userfile, *copyfile;
	DIR *dir_ptr;
	struct dirent *direntp;

	if((dir_ptr=opendir("."))==NULL)
		fprintf(stderr, "can't opendir");
	else{
		while((direntp=readdir(dir_ptr))!=NULL){
			if(strcmp(direntp->d_name,"indivi.txt")==0){
				//user file open
				userfile=fopen("indivi.txt", "r");
				fscanf(userfile, "%d", &file_size);
				fclose(userfile);
				
				//input=delete word number
				printf("delete word number = ");
				scanf("%d", &del_num);
				if(file_size>=del_num*2){//if del_num is in range
					copy("indivi.txt", "copy_f", del_num);//word delete
					copy("copy_f", "indivi.txt", -1);//word count decrease
				}
				else
					printf("not exist\n");
				break;
			}
		}
		closedir(dir_ptr);
	}
	
}

void copy(char* f1name, char*f2name, int del_num){
	int i=0, n_chars, file_size;
	char *buf;
	buf=(char*)malloc(BUFFERSIZE*sizeof(char));
	FILE*f1, *f2;

	f1=fopen(f1name, "r");
	f2=fopen(f2name, "w");
	if(del_num==-1){//word count decrease
		fscanf(f1,"%d", &file_size);
		file_size-=2;
		sprintf(buf, "%d", file_size);
		fputs(buf,f2);
	}
	if(del_num==-2){//word count increase
		fscanf(f1, "%d", &file_size);
		file_size+=2;
		sprintf(buf, "%d", file_size);
		fputs(buf,f2);
	}
	while(fgets(buf, BUFFERSIZE,f1)){//word delete
		if(i==(del_num*2-1)){//1 3 5...
			fgets(buf, BUFFERSIZE,f1);//mean
			i+=2;
			continue;
		}
		fputs(buf, f2);
		i++;
	}
	fclose(f1);
	fclose(f2);

}

//내 학습장 출력하기..
void file_open(char *filename)
{
 int pid;
 int fd;

 if( (pid = fork() ) == -1 ){
  perror("fork");
  exit(1);
 }

 if( pid == 0 ){
  close(0);   /* close */
  fd = open(filename, O_CREAT);
  execlp("cat", "cat", NULL); 
  perror("execlp");
  exit(1);
 }

 if( pid != 0 ){
  wait(NULL);
 }
}

/*-------------game file search, random print------------랭킹 도전 하기!!!*/
void game_search(char* filename){
   FILE* classfile;
   int i=0, ok[5];
   int user_score = 0;
   char nowquiz[15][BUFSIZ] = {"question...", "number...", "2"};
   int quiznum = 0;
   
   srand(time(NULL));
   
   //read and store
   classfile=fopen(filename, "r");
   while(fgets(nowquiz[i++], BUFSIZ, classfile));
   for(i=0;i<5;i++)
      ok[i]=0;//init for random (quiz done or yet)

   //random print
   while(game_done(ok)){
      quiznum=rand()%5;//0~4
      if(ok[quiznum]==0){
         ok[quiznum]=1;
         // 문장 읽어올 때 마다 실행
	skip = 0;
quiz_release(nowquiz[quiznum*3]);
         user_score += correct;
      }
   }
   // 반복 끝나면
   printf("The test is finished. Your Score is ... %d\n", user_score);
}

/*-------------game file search, random print------------랭킹 도전 하기!!!*/
int game_done(int* ok){
   int i;
   for(i=0;i<5;i++){
      if(ok[i]==0)
         return 1;
   }
   return 0;
}

//랭킹 도전 QUIZ!!!! 부분
void quiz_release(char *nowquiz)
{
   char user_answ;
   char* temp=nowquiz+(2*BUFSIZ);

   printf("%s\n", nowquiz);
   printf("%s\n      => ", nowquiz+(1*BUFSIZ));
   
   signal(SIGALRM, time_out);
   alarm(10);
   getc(stdin); //enterkey del
   user_answ = getc(stdin);

   if(!skip)
   {
      if( user_answ==temp[0])
      {
         correct = 1;
         alarm(0);
         printf("Correct!\n");
      }
      else
      {
         correct = 0;
         alarm(0);
         printf("Wrong! The anwser is %s!\n", nowquiz+(2*BUFSIZ));
      }
   }
   printf("Go to next question in 3 sec ...\n\n");
   sleep(3);
}


//랭킹 도전 QUIZ!!!! 부분
void time_out()
{
   printf("\n\tTime out! press any keyboards\n");
   skip++;
   correct = 0;
   return;
}

/* rank file form ==> score id nickname */
void updateRank(char *filename, User nowUser, int user_score)
{
	int id, score, updated = 0;
	int fd = 0;
	char nickname[BUFSIZ];
	FILE *userfile, *tempfile = fopen("temp.txt", "w");

	fd = open(filename, O_CREAT, 0644);
	userfile = fdopen(fd, "r");

	/* copy line before now_user score. Edit now_user score. copy the remaining lines */
	while(!feof(userfile))
	{
		fscanf(userfile, "%d %d %s ", &score, &id, nickname);

		/* update when id is the same, new score is higher than original score */
		if( id == nowUser.user_id )
		{
			updated = 1;
			if( score < user_score )
				score = user_score;
		}
		fprintf(tempfile, "%d %d %s\n", score, nowUser.user_id, nowUser.user_nick);
	}
	if(!updated)
		fprintf(tempfile, "%d %d %s", user_score, nowUser.user_id, nowUser.user_nick);

	unlink(filename);
	rename("temp.txt", filename);
}
