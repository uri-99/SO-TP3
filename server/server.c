#include "server.h"

int main(int argc, char *argv[]){
  system("clear");  
  struct sockaddr_in self_address; //tiene family, port, addr, zero[8]
  struct sockaddr_in client;

  int server_fd, client_socket;
  int opt = 1;
  int self_address_len = sizeof(self_address);

  char assignment[TOTAL_CHALLENGES][BUFFER_SIZE] = 
  { "Veo que llegaste hasta aqui nene pícaro, para comenzar dar en entendido",
    "Segundo desafio",
    "Tercer desafio",
    "Cuarto desafio"};
  char answer[TOTAL_CHALLENGES][BUFFER_SIZE] = {"entendido", "itba", "rta3", "rta4"};

  char message_to_client[BUFFER_SIZE] = {0};
  char buffer[BUFFER_SIZE] = {0};
  int current_challenge = 0;

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
    //printf("Veo que llegaste hasta aqui nene pícaro, para comenzar dar en entendido");


    int completed = 0;
    while (current_challenge < TOTAL_CHALLENGES) {//run challenges

        challenge(assignment[current_challenge], answer[current_challenge], client_socket);
        current_challenge++;
             
    }
    
    system("clear");
    printf("FELICITACIONES\n\n");
    
    return 0;
}

int challenge(char * assignment, char* answer, int client_socket) {
    
    system("clear");
    printf("%s\n\n", assignment);

    while(1) {
        char buffer[BUFFER_SIZE] = {0};
        int valread = read(client_socket, buffer, BUFFER_SIZE);
        if (valread > 0) {
            buffer[valread] = '\0';

            if(strcmp(buffer, answer) == 0) {
                printf("\n\n");
                return 1;
            } else {
                system("clear");
                printf("%s\n\n", assignment);
                printf("Respuesta incorrecta: %s\n", buffer);
            }
        }
    }    
}
