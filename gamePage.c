#include <stdio.h>
#include <string.h>

int main(){
	// game_search 함수에 추가
	int correct, user_score = 0;
	int i=0, j;
	char nowquiz[15][BUFSIZ];
	char co[5][BUFSIZ], wr[5][BUFSIZE];

	// 문장 읽어올 때 마다 실행
	correct = quiz_release(nowquiz[quiznum*3]);
	// 맞았을 경우
	if(correct){
		user_score++;
		printf("	Correct!!\n\n");
	}
	else{
		printf("	Wrong!! The answer is %s\n\n", nowquiz[quiznum*3+2]);
	}

	// 반복 끝나면
	printf("The test is finished. Your Score is ... %d", user_score);
}

void quiz_release(char *nowquiz){
	char user_answ;

	printf("%s\n", nowquiz);
	printf("%s\n => ", nowquiz+1);
	scanf("%c", user_answ);

	/* 유저가 정답을 맞추면 1 반환, 틀리면 0 반환 */
	if(strcmp(user_answ, nowquiz+2)){
		return 1;
	}
	else
		return 0;	
}
