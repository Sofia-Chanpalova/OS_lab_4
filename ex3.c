#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
    char cmd[100];

    while (1) {
        printf("> ");
        fflush(stdout);

        if (!fgets(cmd, sizeof(cmd), stdin)) {
            printf("\n");
            break;
        }
        
        cmd[strcspn(cmd, "\n")] = '\0';

        if (cmd[0] == '\0') continue;

        if (strcmp(cmd, "exit") == 0) break;

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            execlp(cmd, cmd, (char *)NULL);
            perror("exec");
            _exit(127);
        }

        wait(NULL);
    }

    return 0;
}
