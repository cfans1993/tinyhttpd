#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFSIZE 1024
#define quest_string_fmt "GET /%s HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: Close\r\n\r\n"
int main(int argc, char *argv[])
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(4000);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);

    if (result == -1)
    {
        perror("oops: client1");
        exit(1);
    }

    char buf[1024];
    if(argc == 2)
        sprintf(buf,quest_string_fmt,argv[1]);
    else
        sprintf(buf,quest_string_fmt,"");

    if(write(sockfd,buf,strlen(buf)) == -1){
        perror("write");
        exit(1);
    }

    ssize_t i=0;
    while(1){
        i=read(sockfd,buf,BUFSIZE-1);
        if(i <= 0)
            break;
        buf[i]='\0';
        printf(buf); 
    }
    close(sockfd);
    exit(0);
}
