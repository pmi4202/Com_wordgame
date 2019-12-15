#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <termios.h>
#include	<unistd.h> 

int correct = 0;
int skip = 0;

void quiz_release(char *nowquiz);
void time_out();

int main(){
	// game_search 함수에 추가
	int user_score = 0;
	char nowquiz[15][BUFSIZ] = {"question...", "number...", "2"};
	int quiznum = 0;
	// 문장 읽어올 때 마다 실행
	quiz_release(nowquiz[quiznum*3]);
	user_score += correct;

	// 반복 끝나면
	printf("The test is finished. Your Score is ... %d\n", user_score);
}

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


void time_out()
{
	printf("\n\tTime out!\npress any keyboards\n");
	skip++;
	correct = 0;
	return;
}
