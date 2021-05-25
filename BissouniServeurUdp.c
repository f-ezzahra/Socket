
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#define MSGSIZE 500

int main(int argc, char **argv)
{
  int sockfd, cc, addr_in_size;
  u_short portnum = 12345;
  struct sockaddr_in *my_addr, *from;
  char *msg;
  u_long fromaddr;

  addr_in_size = sizeof(struct sockaddr_in);

  msg = (char *)malloc(MSGSIZE);
  from = (struct sockaddr_in *)malloc(addr_in_size);
  my_addr = (struct sockaddr_in *)malloc(addr_in_size);

  memset((char *)my_addr,(char)0,addr_in_size);
  my_addr->sin_family = AF_INET;
  my_addr->sin_addr.s_addr = htonl(INADDR_ANY);
  my_addr->sin_port = portnum;

  if((sockfd = socket (PF_INET, SOCK_DGRAM, 0)) < 0){
     printf("Error\n");
  };

  if(bind(sockfd, (struct sockaddr *)my_addr, addr_in_size) < 0){
    printf("Error\n");
  };

  fprintf(stdout,"Ready to receive your msg your address  port\n");


  while(1){
    if((cc = recvfrom (sockfd,msg,MSGSIZE,0,(struct sockaddr *)from,&addr_in_size)) == -1){
     printf("Error\n");
    };
    fromaddr = from->sin_addr.s_addr;
    msg[cc] = '\0';
    fprintf(stdout,"From %s port %d: %s\n",(gethostbyaddr((char *)&fromaddr,sizeof(fromaddr),AF_INET))->h_name,from->sin_port,msg);

  }
  return 0;
}
