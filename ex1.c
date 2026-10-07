#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

int main() {
	clock_t main_start = clock();
	printf("main: %d, parent %d \n", getpid(), getppid());
	for (int i = 0; i < 2; i++) {
		pid_t pid = fork();
		if (pid == 0) {
			clock_t start = clock();
			printf("child: %d, parent: %d \n", getpid(), getppid());
			clock_t end = clock();
			printf("child %d, finished in %ld miliseconds \n", getpid(), end - start);
			exit(0);
		}
	}
	for (int i = 0; i < 2; i++) wait(NULL);
	clock_t main_end = clock();
	printf("parent: %d, finished in %ld miliseconds \n", getpid(), main_end - main_start);
	exit(0);
	return 0;
	
}

