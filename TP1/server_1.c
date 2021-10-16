#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    printf("Je suis le début de la boucle infinie.\n");

    while (1)
    {
        printf("Pid enfant: %d\n", getpid());
        printf("Pid parent: %d\n", getppid());
        printf("Nombre aléa entre 0 et 99: %d\n", rand() % 100);
        sleep(1);
    }

    printf("Je suis la fin de la boucle infinie.\n");

    return EXIT_SUCCESS;
}