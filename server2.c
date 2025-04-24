#include <stdio.h>
#include <stdlib.h>
#include <string.h>      // for strlen()
#include <unistd.h>      // for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>

int main(){
    int sockid = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server,client;
    socklen_t client_len = sizeof(client);
    server.sin_family = AF_INET;
    server.sin_port = htons(2004);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockid, (struct sockaddr *)& server, sizeof(server));

    // listen(sockid, 1);

    // int connection = accept(sockid, NULL, NULL);

    char input[20];
    int flag = 1;
    int i, j;

    recvfrom(sockid, input, sizeof(input), 0, (struct sockaddr *)&client, &client_len);

    int n = strlen(input);

    if (n == 0) flag = 1;

    i = 0, j = n-1;

    while (i <= j)
    {
        if (input[i] == input[j]){
            ++i; --j;
        }
        else {
            flag = 0;
            break;
        }
    }

    sendto(sockid, &flag, sizeof(flag), 0, (struct sockaddr *)&client, client_len);
    //close(connection);
    close(sockid);
}