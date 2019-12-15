#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void updateRank(int user_id, int user_score, char *user_nick, char *filename);

int main()
{

	int user_id = 13920, user_score = 3;
	char user_nick[BUFSIZ] = "시프시프";
	char filename[BUFSIZ] = "rank1.txt";
	
	updateRank(user_id, user_score, user_nick, filename);
}

/* rank file form ==> score id nickname */
void updateRank(int user_id, int user_score, char *user_nick, char *filename)
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
		if( id == user_id )
		{
			updated = 1;
			if( score < user_score )
				score = user_score;
		}
		fprintf(tempfile, "%d %d %s\n", score, id, nickname);
	}
	if(!updated)
		fprintf(tempfile, "%d %d %s", user_score, user_id, user_nick);

	unlink(filename);
	rename("temp.txt", filename);
}
