#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <string.h>
//directory
#include <dirent.h>
#include <sys/types.h>
//copy
#define BUFFERSIZE 4096

/*
<quiz file structure>
2(word count)
word1
mean1
word2
mean2
*/
void find_file();
void copy();

int main(){
	struct utmp current_record;
	int utmpfd;
	int reclen=sizeof(current_record);

	if((utmpfd=open(UTMP_FILE, O_RDONLY)) ==-1){
		perror(UTMP_FILE);
		exit(1);
	}
	while(read(utmpfd, &current_record, reclen)==reclen){
		find_file(&current_record);
	}

	close(utmpfd);
	return 0;
}

void find_file(struct utmp *utbufp){
	int del_num, file_size;
	FILE* userfile, *copyfile;
	DIR *dir_ptr;
	struct dirent *direntp;

	if(utbufp->ut_type !=USER_PROCESS)
		return;
	if((dir_ptr=opendir("."))==NULL)
		fprintf(stderr, "can't opendir");
	else{
		while((direntp=readdir(dir_ptr))!=NULL){
			if(strcmp(direntp->d_name,utbufp->ut_name)==0){
				//user file open
				userfile=fopen(utbufp->ut_name, "r");
				fscanf(userfile, "%d", &file_size);
				fclose(userfile);
				
				//input=delete word number
				printf("delete word number = ");
				scanf("%d", &del_num);
				if(file_size>=del_num*2){//if del_num is in range
					copy(utbufp->ut_name, "copy_f", del_num);//word delete
					copy("copy_f", utbufp->ut_name, -1);//word count decrease
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
