#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    int fd, alea, running = 1;

    printf("Démarrage du client fifo\n");
    printf("Connexion au server fifo en cours...\n");

    fd = open("fifo", O_RDONLY);

    printf("Connexion au seveur fifo réussi !\n");

    while (running)
    {
        read(fd, &alea, sizeof(int));

        if (alea == -1)
        {
            printf("Déconnexion en cours...\n");
            running = 0;
        }
        else
        {
            printf("Nombre aléatoire lu: %d\n", alea);
        }

        sleep(3);
    }

    printf("Vous avez été déconnecté du server fifo !\n");

    close(fd);

    printf("Fermeture du client fifo\n");

    return (EXIT_SUCCESS);
}