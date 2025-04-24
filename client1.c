
#include <stdio.h>
#include <stdlib.h>
#include <string.h>      // for strlen()
#include <unistd.h>      // for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>


int main(){

    int sockid;

    sockid = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in client;
    client.sin_family=AF_INET;
    client.sin_port=htons(2004);
    client.sin_addr.s_addr=INADDR_ANY;

    int c=connect(sockid, ( struct sockaddr* )&client, sizeof(client));

    char b[20];
    int flag;

    // printf("Enter the string\n");
    // scanf("%s",b);

    FILE *fin = fopen("input.txt","r");

    if(!fin){
        perror("");
        fclose(fin);
    }

    fscanf(fin,"%s",b);
    fclose(fin);

    send(sockid,b,sizeof (b),0);

    recv(sockid,&flag, sizeof (int),0);

    FILE *fout = fopen("output.txt", "w");
    if(flag==1)
    fprintf(fout, "Palindrome\n");
    else
    fprintf(fout, "Not\n");
    fclose(fout);
    close(sockid);
}