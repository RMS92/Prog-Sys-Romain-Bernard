#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd);

int main()
{
    srand(time(NULL));

    int sockfd, connfd, len;
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Association d'une adresse IPV4 au socket
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("Erreur lors du bind de la socket...\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("La socket a été correctement bind !\n");

    // Attente de la connexion client
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Attente de connexion du client a échouée...\n");
        exit(0);
    }
    else
        printf("Attente de connexion du client...\n");

    len = sizeof(cli);

    // Accepte la demande de connexion du client
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        printf("Le serveur n'a pas accepté la demande de connexion du client...\n");
        exit(0);
    }
    else
        printf("Le serveur a accepté la demande de connexion du client !\n");

    func(connfd);

    // Ferme la socket
    close(sockfd);
}

void func(int sockfd)
{
    int alea, running = 1;

    while (running)
    {
        alea = rand() % 100;

        write(sockfd, &alea, sizeof(int));

        printf("Nombre aléatoire envoyé au client: %d\n", alea);

        sleep(3);
    }
}