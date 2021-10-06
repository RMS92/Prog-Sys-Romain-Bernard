#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1)
    {
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        printf("Je suis le processus fils de pid: %d\n", getpid());
        printf("Je suis le processus fils de parent: %d\n", getppid());
    }
    else
    {
        printf("Je suis le processus père de pid: %d \n", getpid());
        printf("Attente de la fin d'exécution du fils.\n");
        waitpid(pid, &status, 0);
        printf("Fin attente du fils.\n\n");

        printf("Code de retour du fils: %d\n", WEXITSTATUS(status));

        if (WEXITSTATUS(status) == 0)
            printf("Le fils s'est correctement terminer.\n");

        if (WEXITSTATUS(status) == 1)
            printf("Le fils s'est terminer de façon anormale\n");
    }

    while (1)
    {
        /* code */
    }

    return EXIT_SUCCESS;
}