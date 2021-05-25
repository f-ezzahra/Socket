#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#define BUFFER_SIZE 256
int cree_socket_tcp_ip(){
int sock;
struct sockaddr_in adresse;
if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
fprintf(stderr, "Erreur socket\n");
return -1;
}
memset(&adresse, 0, sizeof(struct sockaddr_in));
adresse.sin_family = AF_INET;
adresse.sin_port = htons(0);
adresse.sin_addr.s_addr = htons(INADDR_ANY);
adresse.sin_port = htons(33016);
inet_aton("127.0.0.1", &adresse.sin_addr);
if (bind(sock, (struct sockaddr*) &adresse,sizeof(struct sockaddr_in)) < 0){
	close(sock);
	fprintf(stderr, "Erreur bind\n");
	return -1;}
	return sock;
}
int affiche_adresse_socket(int sock){
	struct sockaddr_in adresse;
	socklen_t longueur;
	longueur = sizeof(struct sockaddr_in);
	if (getsockname(sock, (struct sockaddr*)&adresse, &longueur) < 0){
		fprintf(stderr, "Erreur getsockname\n");
		return -1;}
		printf("IP = %s, Port = %u\n", inet_ntoa(adresse.sin_addr),ntohs(adresse.sin_port));
		return 0;}
		void traite_connection(int sock){
						struct sockaddr_in adresse;
						socklen_t  longueur;
						char bufferR[BUFFER_SIZE];
						char bufferW[BUFFER_SIZE];
						int nb;
						longueur = sizeof(struct sockaddr_in);
						if (getpeername(sock, (struct sockaddr*) &adresse, &longueur) < 0){
							fprintf(stderr, "Erreur getpeername\n");
							
						}
							sprintf(bufferW, "IP = %s, Port = %u \n",inet_ntoa(adresse.sin_addr),ntohs(adresse.sin_port));
							printf("Connexion : locale (sock_connectee) ");
							affiche_adresse_socket(sock);
							printf("   Machine distante : %s", bufferW);
							write(sock, "Votre adresse : ", 16);
							write(sock, bufferW, strlen(bufferW)+1);
							strcpy(bufferW, "Veuillez entrer une phrase : ");
							write(sock, bufferW, strlen(bufferW)+1);
							nb= read(sock, bufferR, BUFFER_SIZE);
							bufferR[nb-2] = '\0';
							printf("L'utilsateur distant a tap: %s\n", bufferR);
							sprintf(bufferW, "Vous avez tap: %s\n", bufferR);
							strcat(bufferW, "Appuyez sur entree pour terminer\n");
							write(sock, bufferW, strlen(bufferW)+1);
							read(sock, bufferR, BUFFER_SIZE);
						}
		int main(void){
			int sock_contact;
			int sock_connectee;
			struct sockaddr_in adresse;
			socklen_t longueur;
			pid_t pid_fils;
			sock_contact = cree_socket_tcp_ip();
			if (sock_contact < 0)
				return -1;
			listen(sock_contact, 5);
			printf("Mon adresse (sock contact) -> ");
			affiche_adresse_socket(sock_contact);
			while (1){
				longueur = sizeof(struct sockaddr_in);
				sock_connectee = accept(sock_contact,(struct sockaddr*)&adresse,&longueur);
				if (sock_connectee < 0){
					fprintf(stderr, "Erreur accepte\n");
					return -1;}
					pid_fils = fork();
					if (pid_fils == -1){
						fprintf(stderr, "Erreur fork\n");
						return -1;
					}
						 if(pid_fils == 0)  {
					
							close(sock_contact);
							traite_connection(sock_connectee);
							exit(0);}
							else  {
								close(sock_connectee);
						}
						
					}}

					
