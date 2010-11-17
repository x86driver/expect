#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

extern char **environ;

void sig(int signo)
{
	printf("Aha!\n");
	exit(1);
}

int main()
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	printf("%d:%d\n", tm->

	struct sigaction act;
	act.sa_handler = sig;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGALRM, &act, NULL) < 0)
		perror("sigaction");
//	int ret = execve("./upload.exp", NULL, environ);
//	if (ret == -1)
//		perror("execve");
	alarm(1);
	pause();
	printf("no~\n");
	return 0;
}

