#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//directory
#include <dirent.h>
#include <sys/types.h>

void game_search();
int game_done();

int main(){
	//file number choose
	game_search("data_structure");
	return 0;
}
/*-------------game file search, random print------------*/
void game_search(char* filename){
	FILE* classfile;
	int i=0, quiznum, ok[5];
	char nowquiz[15][BUFSIZ];
	
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
			printf("%s\n", nowquiz[quiznum*3]);
			printf("%s\n", nowquiz[quiznum*3+1]);
		}
	}
	
}
//all quiz print check
int game_done(int* ok){
	int i;
	for(i=0;i<5;i++){
		if(ok[i]==0)
			return 1;
	}
	return 0;
}

