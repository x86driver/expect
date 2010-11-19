#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

extern char **environ;

void sig(int signo)
{
        int ret = execve("./upload.exp", NULL, environ);
        if (ret == -1)
                perror("execve");

	printf("Aha!\n");
	exit(1);
}

int main(int argc, char **argv)
{
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        printf("Now: %d:%d:%d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);

	if (argc != 3) {
		printf("Usage: %s [hour] [min]\n", argv[0]);
		exit(1);
	}

	int f_hour = atoi(argv[1]);
	int f_min = atoi(argv[2]);
	int offset_h = f_hour - tm->tm_hour;
	int offset_m = f_min - tm->tm_min;
	int offset_sec = offset_h * 60 * 60 + offset_m * 60;

	printf("Run: %d:%d\n", f_hour, f_min);
	printf("Offset: %d seconds\n", offset_sec);

	struct sigaction act;
	act.sa_handler = sig;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGALRM, &act, NULL) < 0)
		perror("sigaction");

	alarm(offset_sec);
	pause();

	printf("no~\n");
	return 0;
}

