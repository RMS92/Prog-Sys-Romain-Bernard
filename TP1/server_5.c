#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

int fd, running = 1;

void stop_handler(int sig)
{
    printf("Numéro du signal: %d\n", sig);
    printf("Fermeture de la fifo via un signal.\n");
    int stop_num = -1;
    write(fd, &stop_num, sizeof(int));
    running = 0;
}

int main(void)
{
    srand(time(NULL));

    struct sigaction s;

    int alea;

    s.sa_handler = stop_handler;

    sigaction(SIGINT, &s, NULL);
    sigaction(SIGTERM, &s, NULL);

    printf("Démarrage du server fifo\n");
    printf("En attente d'un client fifo...\n");

    fd = open("fifo", O_WRONLY);
    printf("Un client fifo s'est connecté !\n");

    while (running)
    {
        alea = rand() % 100;

        write(fd, &alea, sizeof(int));

        printf("Nombre aléatoire envoyé: %d\n", alea);

        sleep(3);
    }

    close(fd);

    printf("Fermeture du serveur fifo\n");

    return (EXIT_SUCCESS);
}