#include "server.h"


int main(int argc, char *argv[]){
  struct sockaddr_in self_address; //tiene family, port, addr, zero[8]
  struct sockaddr_in client;

  int server_fd, client_socket;
  int opt = 1;
  int self_address_len = sizeof(self_address);

  char message_to_client[150] = {0};
  char buffer[150] = {0};
  int current_challenge = 0;
  int TOTAL_CHALLENGES = 12;

    server_fd = socket(AF_INET, SOCK_STREAM, 0); //returns descriptor, ipv4, TCP
    //acá van mas cosas, bind listen accept, seguro vamos a tener que hacer una funcion createServer() que haga todo
    if (server_fd == -1)	{
        perror("socket failed");
        exit(EXIT_FAILURE);
	}

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    self_address.sin_family = AF_INET;
    self_address.sin_addr.s_addr = INADDR_ANY;
    self_address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&self_address, sizeof(self_address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((client_socket = accept(server_fd, (struct sockaddr *)&self_address,
                       (socklen_t*)&self_address_len))<0)
    {
        printf("accept error");
    }

    //accepted
    int valread = read( client_socket , buffer, 150);
    printf("%s\n",buffer);

    while(current_challenge < TOTAL_CHALLENGES){
        for(int i=0; i<150; i++){
            buffer[i] = 0;
        }
        int valread = read( client_socket , buffer, 150);
        if(valread > 0){
            printf("%s\n",buffer);
        }
        //recieve and validate answer
    }

    return 0;
}
