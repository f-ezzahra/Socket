#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#define BUFFER_SIZE 256
#include <stdlib.h>
void traite_connection(int sock){
	struct sockaddr_in adresse;
	socklen_t  longueur;
	char bufferR[BUFFER_SIZE];
	char bufferW[BUFFER_SIZE];
	char tmp[50];
	int nb;
	longueur = sizeof(struct sockaddr_in);
	if (getpeername(sock, (struct sockaddr*) &adresse, &longueur) < 0){
		fprintf(stderr, "Erreur getpeername\n");
		return;}
		sprintf(bufferW, "IP = %s, Port = %u\n",inet_ntoa(adresse.sin_addr),ntohs(adresse.sin_port));
		printf("Veuillez entrer une phrase ");
		printf("Connexion : locale (sock_connectee) ");
		affiche_adresse_socket(sock, tmp);
		printf(tmp);
		printf("   Machine distante : %s", bufferW);
		strcat(bufferW, "Votre adresse : ");
		affiche_adresse_socket(sock, tmp);
		strcat(bufferW, tmp);
		strcat(bufferW, "Veuillez entrer une phrase : ");
		write(sock, bufferW, BUFFER_SIZE);
		nb= read(sock, bufferR, BUFFER_SIZE);
		printf("L'utilsateur distant a tap￿ : %s\n", bufferR);
		sprintf(bufferW, "Vous avez tap￿ : %s\n", bufferR);
		write(sock, bufferW, BUFFER_SIZE);
	}
int cree_socket_tcp_client(int argc, char** argv){
	struct sockaddr_in adresse;
	int sock;
	if (argc != 3){
		fprintf(stderr, "Usage : %s adresse port\n", argv[0]);
		exit(0);}
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
			fprintf(stderr, "Erreur socket\n");
			return -1;}
			memset(&adresse, 0, sizeof(struct sockaddr_in));
			adresse.sin_family = AF_INET;adresse.sin_port = htons(atoi(argv[2]));
			inet_aton(argv[1], &adresse.sin_addr);
			if (connect(sock, (struct sockaddr*) &adresse,sizeof(struct sockaddr_in)) < 0){
				close(sock);
				fprintf(stderr, "Erreur connect\n");
				return -1;}
				return sock;}
				int affiche_adresse_socket(int sock){
					struct sockaddr_in adresse;socklen_t longueur;
					longueur = sizeof(struct sockaddr_in);
					if (getsockname(sock, (struct sockaddr*)&adresse, &longueur) < 0){
						fprintf(stderr, "Erreur getsockname\n");
						return -1;}
						printf("IP = %s, Port = %u\n", inet_ntoa(adresse.sin_addr),ntohs(adresse.sin_port));
						return 0;}
						int main(int argc, char**argv){
							int sock;
							char buffer[BUFFER_SIZE];sock = cree_socket_tcp_client(argc, argv);
							if (sock < 0)
								{puts("Erreur connection socket client");
							exit(1);}
							affiche_adresse_socket(sock);
							while(1){
								if (read(sock, buffer, BUFFER_SIZE)==0)
									break;
								puts(buffer);
								if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
									break;
								buffer[strlen(buffer)-1] = '\0';
								write(sock, buffer, BUFFER_SIZE);}
								return 0;}