#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <time.h>

#include <utmp.h>

#include <string.h>

#include <signal.h>

#include <termios.h>

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

 

void loginPage(); // 로그인 페이지

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

 

void game_search(); // 랭킹 도전 게임

int game_done(); // 랭킹 도전 게임

 

//void updateRank(int user_id, int user_score, char *user_nick, char *filename); //랭킹점수파일생성

 

void quiz_release(char *nowquiz);//랭킹 도전 문제 출제부분

void time_out(); //랭킹 도전 문제 출제부분

int correct = 0; //랭킹 도전 문제 출제부분

int skip = 0;//랭킹 도전 문제 출제부분

 

int main(){

	loginPage();

	mainPage();

        return 0;

}

 

void loginPage(){

        int user_id, user_pw;

        char    regist;

 

        printf("********************* LOG-IN PAGE ***********************\n\n");

        printf("\tID : ");

        scanf("%d", &user_id);

        printf("\tPassWord : ");

        scanf("%d", &user_pw);

        

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

			break;

		case 4: exit(1);

	}

}

 

//랭킹 도전 페이지..

void rankchallenge(){

	int command;

	

	//랭킹 점수 생성에 필요한 변수

	int user_id = 13920, user_score = 3;

	char user_nick[BUFSIZ] = "시프시프";

	char filename[BUFSIZ] = "rank1.txt";

	char filename2[BUFSIZ] = "rank2.txt";

	char filename3[BUFSIZ] = "rank3.txt";

	char filename4[BUFSIZ] = "rank4.txt";

 

        printf("********************** rank challenge ***********************\n\n");

        printf("* 원하는 과목의 번호를 입력하세요.\n\t1. 자료 구조\n\t2. 운영 체제\n\t3. 데이터 통신\n\t4. 시스템 프로그래밍\n\t5. 메인 화면으로 나가기\n");

        scanf("%d", &command);

	

	switch(command){

		case 1:

			game_search("data_structure");

			//updateRank(user_id, user_score, user_nick, filename);

			rankchallenge();

		case 2:

			game_search("data_structure"); // 문제 출제 후 수정

			//updateRank(user_id, user_score, user_nick, filename2);

			rankchallenge();

			break;

		case 3:

			game_search("data_structure");	// 문제 출제 후 수정

			//updateRank(user_id, user_score, user_nick, filename3);

			rankchallenge();

			break;

		case 4: 

			game_search("data_structure"); // 문제 출제 후 수정

			//updateRank(user_id, user_score, user_nick, filename4);

			rankchallenge();

			break;

		case 5: mainPage();

	}

}

 

void personalPage(){

        int command;

	FILE *fp;

 	char in;

	struct word getword;

	printf("******************* PERSONAL STUDY *********************\n\n");

        printf("* 원하는 기능의 번호를 입력하세요.\n\t1. 단어 추가\n\t2. 단어 삭제\n\t3. 학습하기\n\t4. 메인 화면으로 나가기\n");

        scanf("%d", &command);

 

	switch(command){

		case 1:

			 fp = fopen("indivi.txt", "w"); //쓰기

			  while(1) 

  				{

 				  getword = getWord();

				if(strcmp(getword.word, "q")==0) break;

 				fprintf(fp, "단어 : %s\n의미: %s\n",getword.word, getword.word_mean);

				 }

			fclose(fp);

			sleep(2);

			personalPage();

		case 2:

			personalPage();

			break;

		case 3:

			printf("\n내 학습장 \n\n");

			file_open();

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

printf("* 원하는 과목의 번호를 입력하세요.\n\t1. 자료 구조\n\t2. 운영 체제\n\t3. 데이터 통신\n\t4. 시스템 프로그래밍\n\t5. 메인 화면으로 나가기\n");

 

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

		printf("\n시스템 프로그래밍 랭킹\n");

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

 

//내 학습장 출력하기..

void file_open()

{

 int pid;

 int fd;

 

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

	// 문장 읽어올 때 마다 실행

	quiz_release(nowquiz[quiznum*3]);

	user_score += correct;

 

	// 반복 끝나면

	printf("The test is finished. Your Score is ... %d\n", user_score);

	//random print

	while(game_done(ok)){

		quiznum=rand()%5;//0~4

		if(ok[quiznum]==0){

			ok[quiznum]=1;

			printf("%s\n", nowquiz[quiznum*3]);

			printf("%s\n", nowquiz[quiznum*3+1]);

		}

	}

	

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

	char c;

 

	printf("%s\n", nowquiz);

	printf("%s\n		=> ", nowquiz+(1*BUFSIZ));

	

	signal(SIGALRM, time_out);

	alarm(10);

 

	c = getc(stdin);

 

	if(!skip)

	{

		if( !strcmp(&c, nowquiz+(2*BUFSIZ)) )

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

	printf("Go to next question in 3 sec ...\n");

	sleep(3);

	return;

}

 

 

//랭킹 도전 QUIZ!!!! 부분

void time_out()

{

	printf("\n\tTime out!\npress any keyboards\n");

	skip++;

	correct = 0;

	return;

}
