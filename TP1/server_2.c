#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>

int running = 1;

void exit_message()
{
    printf("Fin du programme\n");
}

void stop_handler(int sig)
{
    printf("Numéro du signal: %d\n", sig);
    running = 0;
}

int main()
{
    struct sigaction s;

    srand(time(NULL));

    s.sa_handler = stop_handler;

    sigaction(SIGINT, &s, NULL);

    sigaction(SIGTERM, &s, NULL);

    printf("Je suis le début de la boucle infinie.\n");

    while (running)
    {
        printf("Pid enfant: %d\n", getpid());
        printf("Pid parent: %d\n", getppid());
        printf("Nombre aléa entre 0 et 99: %d\n", rand() % 100);
        sleep(1);
    }

    printf("Je suis la fin de la boucle infinie.\n");

    atexit(exit_message);

    return EXIT_SUCCESS;
}