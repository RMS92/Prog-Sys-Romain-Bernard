#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/stat.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd);

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // Creation d'une extrémité de connexion avec socket()
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        printf("Erreur lors de la création de la socket...\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("La socket a été correctement créée !\n");

    bzero(&servaddr, sizeof(servaddr));

    // Assignement de l'IP et du PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // Se connecte au client
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("La connexion avec le client a échouée...\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("Connexion avec le client réussi !\n");

    func(sockfd);

    // Ferme la socket
    close(sockfd);
}

void func(int sockfd)
{
    int alea, running = 1;

    while (1)
    {
        read(sockfd, &alea, sizeof(int));

        if (alea == -1)
        {
            printf("Déconnexion en cours...\n");
            running = 0;
        }
        else
        {
            printf("Nombre aléatoire reçu par le serveur %d\n", alea);
        }

        sleep(3);
    }
}