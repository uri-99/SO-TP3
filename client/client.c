#include "includes/client.h"




int main()
{
    //crear socket, despues connect
    struct sockaddr_in server_address;
    int sock;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket creation error \n");
        return -1;
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);


    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    //connection made
    char* hello = "hi i just connected";
    send(sock , hello , strlen(hello) , 0);
    printf("Hello message sent\n");
    return 0;
}
   