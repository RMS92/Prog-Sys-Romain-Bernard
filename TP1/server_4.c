#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

int running = 1;
pid_t child_pid;

void exit_message()
{
    printf("Fin du programme\n");
}

void stop_handler(int sig)
{
    printf("Numéro du signal: %d\n", sig);
    running = 0;
}

void kill_child(int sig)
{
    printf("Numéro du signal du meurtre du fils: %d\n", sig);
    printf("Meurtre du fils\n");
    kill(child_pid, SIGTERM);
    printf("Meurtre du père\n");
    exit(EXIT_SUCCESS);
}

int main()
{
    srand(time(NULL));

    struct sigaction s;
    struct sigaction k;

    pid_t pid;
    int pfd[2];
    int alea, alea2;

    s.sa_handler = stop_handler;
    k.sa_handler = kill_child;

    sigaction(SIGINT, &s, NULL);

    sigaction(SIGTERM, &s, NULL);

    sigaction(SIGTERM, &k, NULL);

    if (pipe(pfd) == -1)
    {
        printf("La création du pipe a echouée.\n");
        return 1;
    }

    pid = fork();

    printf("Je suis le début de la boucle infinie.\n");

    while (running)
    {
        if (pid == -1)
        {
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            printf("Je suis le processus fils de pid: %d\n", getpid());
            printf("Je suis le processus fils de parent: %d\n", getppid());

            child_pid = getpid();

            // Close the read side
            close(pfd[1]);

            read(pfd[0], &alea2, sizeof(int));

            printf("Lecture du nombre aléatoire du père: %d\n", alea2);

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

        sleep(50);
    }

    printf("Je suis la fin de la boucle infinie.\n");

    atexit(exit_message);

    return EXIT_SUCCESS;
}