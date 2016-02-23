#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

const char *g_AppName = "TRACER-TEA";
int validIP(char *ip);
int scanport(int portno,char *ip);


//Main Logic
int main(int argc,char *argv[])
{


    //Default help prompt
    if(argc<4)
    {
        printf("%s USAGE:IPADRESS STARTPORT ENDPORT\n",g_AppName);
    }
    else
    {

    if(validIP(argv[1])!=1)
    {
        printf("INVALID IP\n");
        return 0;
    }

    //Formats ports
    uintmax_t start_port = strtoumax(argv[2], NULL, 10);
    uintmax_t end_port = strtoumax(argv[3], NULL, 10);
    printf(
           "IP ADRESS: %s\n"
           "Start Port %i\n"
           "End Port %i\n"
           ,argv[1],start_port,end_port

           );
    if(end_port<start_port)
    {
        printf("ERROR START PORT IS BEFORE END PORT\n");
        return(0);
    }

    while(start_port<end_port)
    {
    scanport(start_port,argv[1]);
    start_port++;
    }

    }
    return 0;
}


//Port scanner function
int scanport(int portno,char *ip)
{
    int sockfd;
    struct hostent *target;
    struct sockaddr_in target_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }
    memset(&target_addr,'0',sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(portno);
    inet_pton(AF_INET,ip, &target_addr.sin_addr);

    if (connect(sockfd,(struct sockaddr *) &target_addr,sizeof(target_addr)) < 0) {
      //for verbose mode
      //printf("Port %i is closed\n",portno);
    } else {
       printf("Port %i is active\n",portno);
    }
    close(sockfd);
    return 0;
}

//Checks to see if the I address given by the user is valid
int validIP(char *ip)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET,ip,&(sa.sin_addr));
    return result;
}

