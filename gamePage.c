#include <stdio.h>


int main(){
	// game_search 함수에 추가
	int correct, user_score = 0;
	int i, j;
	char nowquiz[15][BUFSIZ];

	// 문장 읽어올 때 마다 실행
	user_score += quiz_release(nowquiz[quiznum*3], user_score);

	// 반복 끝나면
	printf("The test is finished. Your Score is ... %d", user_score);
}

void quiz_release(quiz nowquiz, int user_score){
	int user_answ;

	printf("%s\n", nowquiz.question);
	printf("%s\n => ", nowquiz.example);
	scanf("%d", user_answ);

	/* 유저가 정답을 맞추면 1 반환, 틀리면 0 반환 */
	if(user_answ == nowquiz.answer){
		user_score++;
		return 1;
	}
	else
		return 0;	
}
