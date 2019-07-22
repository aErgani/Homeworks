#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

//Maximum amount of directory must be set before
//Set here. default is 100
int MAX_DIRECTORY = 100;
int flag;
FILE *fp;
int postOrderApply(char *path, int pathfun(char *path1));
int sizepathfun(char *path);
void flock(FILE *fp);	//imported from http://www.cs.toronto.edu/~maclean/csc209/lock.c
void funlock(FILE *fp);	//imported from http://www.cs.toronto.edu/~maclean/csc209/lock.c
int charoccurence(char *str,char chr);	//finds how many times chr appeared in the given string
void finalparse();

int strcompare(char *str1,char *str2)
{
	int i;
	if(strlen(str1) >= strlen(str2))
		return 0;
	else
		for(i = 0; i < strlen(str1); i++)
		{
			if(str1[i] != str2[i])
				return 0;
			i++;
		}
	return 1;
}
void finalparse()
{
	FILE *stream;
	char lines [MAX_DIRECTORY][1000];
	char *line = NULL;
	long dirsize = 0;
	long size1 = 0,size2 = 0;
	int oldslashcount = 0;
	int newslashcount;
	int pid1,pid2;
	int count = 0;
	int i,j;
	char path1[1000],path2[1000];
	char cbuff;
	size_t len = 0;
	ssize_t read;
	stream = fopen("output.txt", "r");
	if (stream == NULL)
		exit(EXIT_FAILURE);
	printf("PID\tSIZE\t\tPATH\n");
	if(!flag)
	{	
		while ((read = getline(&line, &len, stream)) != -1) 
			printf("%s", line);
		free(line);
		fclose(stream);
		exit(EXIT_SUCCESS);
	}
	else
	{
		while ((read = getline(&line, &len, stream)) != -1) 
		{
			strcpy(lines[count],line);
			count++;
		}
		printf("count is %d\n",count);
		i = 0;
		/*while(strlen(lines[i]) > 10)
		{
			printf("%s",lines[i]);
			i++;
		}*/
		for(i = 0; strlen(lines[i]) > 10; i++)
		{
			sscanf(lines[i],"%d\t%lu\t\t%s\n",&pid1,&size1,path1);
			dirsize += size1;
			for(j = count - 1;j > -1; j--)
			{
				sscanf(lines[j],"%d\t%lu\t\t%s\n",&pid2,&size2,path2);
				//printf("comparing: %s	%s ",path1,path2);
				if(strcompare(path1,path2))
						dirsize += size2;
			}
			printf("%d\t%lu\t\t%s\n",pid1,dirsize,path1);
			dirsize = 0;
		}
		free(line);
		fclose(stream);
		exit(EXIT_SUCCESS);
	}
}
void flock(FILE *fp)
{
	struct flock fl = { F_WRLCK, SEEK_SET, 0, 0};
  	assert(fp != (FILE *)NULL);

  	if (fcntl(fileno(fp), F_SETLKW, &fl) == -1)
  	{
    	perror("flock: error in fcntl");
    	exit(1);
  	}
}
void funlock(FILE *fp)
{
	struct flock fl = { F_UNLCK, SEEK_SET, 0, 0};
  	assert(fp != (FILE *)NULL);

  	if (fcntl(fileno(fp), F_SETLK, &fl) == -1)
  	{
    	perror("funlock: error in fcntl");
    	exit(1);
  	}
}
int sizepathfun(char *path)
{
	struct stat st;
	//printf("	%s\n",path);
	int data = stat(path, &st);
	//if (data >= 0)
		//printf("%ld\t\t%s\n", st.st_size, path);
	return st.st_size;
}

int postOrderApply(char *path, int pathfun(char *path1))
{
    int du = 0;
    int is_parent = 0;
    DIR * dir;
    if((dir = opendir(path)) == NULL)
        return -1;
	if(flag)
		flock(fp);
    while(1)
    {
        struct dirent * ent;
		ent = readdir(dir);
		if(ent == NULL) break;
        if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..")  == 0)
			continue;
        char * temp = malloc(strlen(path) + strlen(ent->d_name) + 2);
		strcpy(temp,path);
		strcat(temp, "/");
		strcat(temp, ent->d_name);
        if (ent->d_type == DT_DIR)
        {
            is_parent = fork();
            if(is_parent > 0)
            {
				free(temp);
				continue;
			}
            /*else if(flag)
				du = du + postOrderApply(temp, pathfun);
			else*/
				postOrderApply(temp, pathfun);
        }
        else if (ent->d_type == DT_REG)
			du = du + pathfun(temp);
		else
			fprintf(fp,"Special file %s\n", path);
		
		//printf("%d - %s\n", getpid(), ent->d_name);
		free(temp);
    }
	int stat;
	waitpid(is_parent, &stat, 0);
	if(!flag)
		flock(fp);
    fprintf(fp,"%d\t%d\t\t%s\n",getpid(),du, path);
	closedir(dir);
	funlock(fp);
	exit(EXIT_SUCCESS);
	//printf("after exit\n");
}
int main(int argc, char *argv[])
{
	//printf("%s\n", argv[1]);
	if (argc == 2)
		flag = 0;
	else if (argc == 3)
		flag = 1;
	else
	{	
		printf("Wrong  command line arguments\nUsage: './buNeDu [dir]' or './buNeDu -z [dir]'\n");
		return -1;
	}
	if(flag && strcmp(argv[1],"-z") != 0)
	{	
		printf("Wrong  command line arguments\nUsage: './buNeDu [dir]' or './buNeDu -z [dir]'\n");
		return -1;
	}
	fp = fopen("output.txt","w+");
	int pid = fork();
	if(pid > 0){
		//printf("Main process: %d\n", getpid());
		int wpid, status;
		while ((wpid = wait(&status)) > 0);
	}
	else 
	{
		if (flag)
			postOrderApply(argv[2], sizepathfun);
		else
			postOrderApply(argv[1], sizepathfun);
	}
	fclose(fp);
	finalparse();
	return 0;
}