#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <time.h>

int main()
{
    pid_t pid;
    int pfd[2];
    int alea, alea2;

    srand(time(NULL));

    if (pipe(pfd) == -1)
    {
        printf("La création du pipe a echouée.\n");
        return 1;
    }

    pid = fork();

    if (pid == -1)
    {
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        printf("Je suis le processus fils de pid: %d\n", getpid());
        printf("Je suis le processus fils de parent: %d\n", getppid());
        // Close the read side
        close(pfd[1]);

        read(pfd[0], &alea2, sizeof(int));

        printf("Lecture du nombre aléatoire du père: %d", alea2);

        // Close the pipe
        close(pfd[0]);
    }
    else
    {
        printf("Je suis le processus père de pid: %d \n", getpid());

        alea = rand() % 100;
        printf("Nombre aléa entre 0 et 99 du processus père: %d\n", alea);

        // Close the read side
        close(pfd[0]);

        // Send some data into pipe
        write(pfd[1], &alea, sizeof(int));

        // Close the pipe
        close(pfd[1]);
    }

    while (1)
    {
    }

    return EXIT_SUCCESS;
}