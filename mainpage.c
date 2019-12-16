#include        <stdio.h>
void loginPage();
void mainPage();
void personalPage();

int main(){

        int     user_id, user_pw;
        int     command;
        char    regist;

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

void mainPage(){
        int command;

        printf("********************** MAIN PAGE ***********************\n\n");
        printf("* 원하는 기능의 번호를 입력하세요.\n\t1. 랭킹 확인\n\t2. 랭킹 도전\n\t3. 개인 학습\n\t4. 프로그램 종료\n");
        scanf("%d", &command);
	
	switch(command){
		case 1:
			break;
		case 2:
			break;
		case 3:
			personalPage();
	}
}

void personalPage(){
        int command;

	printf("******************* PERSONAL STUDY *********************\n\n");
        printf("* 원하는 기능의 번호를 입력하세요.\n\t1. 단어 추가\n/t2. 단어 삭제\n\t3. 학습하기\n\t4. 메인 화면으로 나가기\n");
        scanf("%d", &command);

	switch(command){
		case 1:
			break;
		case 2:
			break;
		case 3:
			//personal_study();
			break;
	}
}
