#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
void sigint_handler(int sig) {
	printf("SIGINT caught: %d\n", sig);
	}
int main(){
	char cmd[512],*ptr,*args[35];
	int i,ret,err,s;
	signal(SIGINT, sigint_handler);
	while(1) {
	printf("cmd>  ");
	gets(cmd);
		i=0;
	ptr=strtok(cmd," ");
	args[i]=ptr;
	i++;
	do{
		ptr=strtok(NULL," ");
		args[i]=ptr;
		i++;
	}while(ptr !=NULL);
	ret=fork();
	if(ret==0){
		err=execvp(args[0],args);
		if(err< 0){
			perror("bad comment");
			_exit(1);
		}
	}else
		wait(&s);
		}
	printf("bye\n");

	return 0;
}

