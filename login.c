#include<stdio.h.>
#include<stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 100
#define NAME_SIZE 20

struct Userinfo {
	int UserNum;
	char UserName[10];
	int Score;
};

void main(int argc, char* argv[]) {

	int getNum;
	struct Userinfo myUser[200];
	char buf[40];

	printf("���Ͻô� ���� ��ȣ�� �Է��ϼ���. ���� 0~199\n")

	fgets(buf, 19, stdin);
	getNum = atoi(buf);
	myUser[getNum].UserNum = getNum; 

	printf("���Ͻô� ���� �г����� �Է��ϼ���.\n")

	fgets(buf, 19, stdin);
	myUser[getNum].UserName = buf; 
	
}