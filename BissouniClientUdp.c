#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#define MSGSIZE 500

int main(int argc,char **argv)
{
  int sockfd, ok, addr_in_size;
  u_short portnum = 12345;
  struct sockaddr_in *to;
  struct hostent *toinfo;
  char *msg, *htoname = "127.0.0.1";
  u_long toaddr;

  msg = (char *)malloc(MSGSIZE);
  to = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

  if((toinfo = gethostbyname(htoname)) == NULL){
       printf("Error\n");
  };
  toaddr = *(u_long *)toinfo->h_addr_list[0];

  addr_in_size = sizeof(struct sockaddr_in);
  memset((char *)to,(char)0,addr_in_size);

  
  to->sin_family = AF_INET;
  to->sin_addr.s_addr = toaddr;
  to->sin_port = /*(htons)*/portnum;

  if((sockfd = socket (PF_INET, SOCK_DGRAM, 0)) == -1){
      printf("Error\n");
  };

  
  while(1){
    printf("entre un msg\n");
    fprintf(stdout,"Message: ");
    scanf("%s",msg);
    fprintf(stdout,"\n");
    ok = (msg[0] != '0');

    if(sendto(sockfd,msg,strlen(msg),0,(struct sockaddr *)to,addr_in_size) == -1){
        printf("Error\n");
    }
  }
}