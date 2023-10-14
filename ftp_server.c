#include<stdio.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define SERV_TCP_PORT 9000
#define MAX 60
#define PI 3.412

int main(int afg, char *argv)
{      
       int i, j, tem;
       char buff[4096], t;
       int sockfd, newsockfd, clength;
       struct sockaddr_in serv_addr,cli_addr;
       char t[MAX], str[MAX];
       FILE *f1;;
       strcpy(t,"exit");

       /* Creates a Socket */
       sockfd=socket(AF_INET, SOCK_STREAM,0);
       serv_addr.sin_family=AF_INET;
       serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

       /*  htons() function converts the unsigned short integer hostshort from host byte order to network byte order*/
       serv_addr.sin_port=htons(SERV_TCP_PORT);

       /* Bind() binds the socket with specified address and port number */
       bind(sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
       printf("\nBinded\n\n");
       /* Activates the server to accept requests from client with queue limit */
       listen(sockfd, 5);
       printf("Listening!!!");
       clength=sizeof(cli_addr);

       /* Establishes a new socket */
       newsockfd=accept(sockfd,(struct sockaddr*) &cli_addr,&clength);
       // close(sockfd);

       /* Reads the request from client */
       read(newsockfd, &str, MAX);
       printf("\nClient message\n File Name : %s\n", str);

       /* Extracts characters from file */
       f1=fopen(str, "r");
       while(fgets(buff, 4096, f1)!=NULL)
       {
            write(newsockfd, buff,MAX);
            printf("\n");
       }
       fclose(f1);
       close(sockfd);
       close(newsockfd);
       printf("\nFile Transferred\n");
       return 0;
}
