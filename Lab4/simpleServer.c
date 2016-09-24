/* A simple server using TCP Sockets
   The port number used is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     char *z;
     FILE *file;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     while((newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen)) >= 0){
        if (newsockfd < 0) 
           error("ERROR on accept");
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) error("ERROR reading from socket");
           printf("Here is the message: %s\n",buffer);
        z = inet_ntoa(*(struct in_addr *)&cli_addr); /* cast as a struct in_addr */
        printf("Client information: %s\n", z);
        file = fopen("clients.txt","a+");
        fprintf(file,"%s\t%s",z,buffer);
        fclose(file);
        n = write(newsockfd,"I got your message\nMessage: %",18);
        if (n < 0) error("ERROR writing to socket");
     }
     printf("Server Terminated\n");
     return 0; 
}
