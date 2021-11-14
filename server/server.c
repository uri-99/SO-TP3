#include "server.h"

  char assignment[TOTAL_CHALLENGES][BUFFER_SIZE] = 
  { "Veo que llegaste hasta aqui nene pícaro, la primer respuesta es 'entendido'",
    "The Wire S1E5\n5295 888 6288",
    "https://ibb.co/tc0Hb6w",
    "EBADF",
    "strings: NUMERO",
    ".data .bss .comment ? .shstrtab .symtab .strtab\n",
    "Filter error",
    "¿?\n\n",
    "Latexme\nSi\n\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u})\nentonces\n y=\n",
    "",
    "gdb me to fin the magic number",
    "Me conoces"};
  char answer[TOTAL_CHALLENGES][BUFFER_SIZE] = {"e", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k"};

  functiontype functions[TOTAL_CHALLENGES] = {  &doNothing, //1
                                                &doNothing, //2
                                                &doNothing, //3
                                                &challenge4,
                                                &doNothing, //5
                                                &challenge6,
                                                &challenge7,
                                                &challenge8,
                                                &doNothing, //9
                                                &challenge10,
                                                &challenge11,
                                                &challenge12}; 


int main(int argc, char *argv[]){
  system("clear");  
  struct sockaddr_in self_address; //tiene family, port, addr, zero[8]
  struct sockaddr_in client;

  int server_fd, client_socket;
  int opt = 1;
  int self_address_len = sizeof(self_address);

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


    while (current_challenge < TOTAL_CHALLENGES) {//run challenges
        
        challenge(current_challenge, client_socket);
        current_challenge++;
             
    }
    
    system("clear");
    printf("FELICITACIONES\n\n");
    
    return 0;
}

int challenge(int current_challenge, int client_socket) {
    
    system("clear");
    printf("%s\n\n", assignment[current_challenge]);

    functions[current_challenge]();

    while(1) {
        char buffer[BUFFER_SIZE] = {0};
        int valread = read(client_socket, buffer, BUFFER_SIZE);
        if (valread > 0) {
            buffer[valread] = '\0';

            

            if(strcmp(buffer, answer[current_challenge]) == 0) {
                printf("\n\n");
                return 1;
            } else {
                //system("clear");
                printf("%s\n\n", assignment[current_challenge]);
                printf("Respuesta incorrecta: %s\n", buffer);
            }
        }
    }    
}

void doNothing() {
    // printf("Soy la funcion que no hace nada holaaaa\n\n");
}
void challenge4() {
    write(WRITE_EBADF, "La respuesta es: fk3wfLCm3QvS\n", strlen("La respuesta es: fk3wfLCm3QvS\n"));
}
void challenge6() {
    pid_t pid = getpid();
    char buffer6[BUFFER_SIZE] = {0};
    sprintf(buffer6, "cat /proc/%d/status | grep \"TracerPid\" > killP.txt ", pid);
    system(buffer6);
    FILE *killFile;
    killFile = fopen("killP.txt", "r");

    if (killFile != NULL)
    {
        int pidTracer = -1;
        fscanf(killFile, "TracerPid:\t%d", &pidTracer);
        if (pidTracer >0)
        { // Si leyo un numero
            char bufferKill[30] = {0};
            sprintf(bufferKill, "kill %d", pidTracer);
            system(bufferKill);
            //kill(pidTracer, 0);
        }
    }
    system("rm -f killP.txt");
}

void challenge7() {
    
    int k = 0;
    int i = strlen("La respuesta es: K5n2UFfpFMUN");
    char *toPrint = "La respuesta es: K5n2UFfpFMUN";
    srand(time(NULL));
    int randNumber = 0;
    while (k < i)
    {
        randNumber = rand() % 7;
        if (randNumber == 0)
        {
            write(STDOUT_FILENO, toPrint + k++, 1);
        }
        else
        {
            char toP = (char)(rand() % CANT_CHARACTER_USED + ASCII_NO_REPRESENTABLES);
            write(STDERR_FILENO, &toP, 1);
        }
    }    
}

void challenge8() {
    printf(BLACK_COLOR_PRINTF); // Seteado el color
    printf("La respuesta es: BUmyYq5XxXGt \n");
    printf(RESET_COLOR); // Se resetea al valor default
}

void challenge10() {
    //Compilar el quine.c
    system("gcc -Wall -o quine quine.c");
    // Busco en el PWD si esta el archivo
    DIR *dp;
    int pid = -1;
    int fd[2] = {-1, -1};
    struct dirent *entry;
    struct stat statbuf;
    if ((dp = opendir(".")) == NULL)
    {
        printf("Cannot open directory\n");
        return;
    }
    int found = 0;
    while ((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name, &statbuf);
        if (S_ISREG(statbuf.st_mode))
        {
            if (strcmp("quine.c", entry->d_name) == 0)
            {
                found = 1;
            }
        }
    }
    closedir(dp);

    // Si el archivo NO esta, imprimo y corto
    if (!found)
    {
        printf("\n");
        printf("Que pasa capo, no te sale?\n");
    }
    else
    {
        // Si el archivo esta, tengo que ver si hace lo que tiene que hacer
        printf("¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde.\n");

        if (pipe(fd) < 0)
        {
            perror("ERROR al crear pipe (desafio10)");
            return;
        }

        if ((pid = fork()) == 0)
        {
            close(fd[0]);                       // el hijo solo escribe
            if (dup2(fd[1], STDOUT_FILENO) < 0) //redirecciono la salida del STDOUT al pipe (eso intento)
            {
                perror("Error al supear la salida");
            }
            char *quine[] = {"./quine", NULL}; //antes del exec hay que forkear si no te pisa la imagen del server
            int resExec = execvp(quine[0], quine);
            if (resExec < 0)
            {
                perror("ERROR en Execv (desafio10)");
                return;
            }
        }

        close(fd[1]); // el padre solo lee
        char buffer[1024] = {0};
        read(fd[0], buffer, 1024);

        //Ahora deberia ver si lo que se escribio en el fd es igual al programa en si
        char chSalida;
        int bufferIndex = 0;
        FILE *fp;

        int different = 0;

        fp = fopen("quine.c", "r");

        while ((chSalida = (char)fgetc(fp)) != EOF && (buffer[bufferIndex]) != EOF && bufferIndex < 1024)
        {
            if (chSalida != buffer[bufferIndex++])
            {
                different = 1;
            }
        }
        fclose(fp);

        if (!different)
        {
            printf("La respuesta es chin_chu_lan_cha\n");
        }
        else
        {
            printf("-- Codigo del programa --\n"); //Codigo de quine
            char chAux;
            FILE *fpAux;
            fpAux = fopen("quine.c", "r");
            while ((chAux = fgetc(fpAux)) != EOF)
            {
                printf("%c", chAux);
            }

            printf("-- Salida del programa --\n"); //Salida de quine
            bufferIndex = 0;
            while ((buffer[bufferIndex]) != EOF && bufferIndex < 1024)
            {
                printf("%c", buffer[bufferIndex++]);
            }
            printf("\ndiff encontró diferencias.\n");
            printf("\n");
        }
        if (pid > 0)
        {
            waitpid(pid, NULL, 0);
        }
    }
    if (fd[0] != -1)
    {
        close(fd[0]);
    }
}

int gdbme()
{
    return 0;
}

void challenge11()
{
    if (gdbme() != 0x12346578) // Deberia cambiarse el valor de retorno usando el gdb!
    {
        puts("Introduzca cualquier tecla y ENTER para reintentar\n");
    }
    else
    {
        puts("La respuesta es gdb_rules\n");
    }
}

double drand() /* uniform distribution, (0..1] */
{
    return (rand() + 1.0) / (RAND_MAX + 1.0);
}

double randomNormal()
/* normal distribution, centered on 0, std dev 1 */
{
    return sqrt(-2 * log(drand())) * cos(2 * PI * drand());
}

void challenge12() {

    double rands[1000];
    int i = 0;
    for (i = 0; i < 1000; i++)
    {
        rands[i] = 1.0 + 0.5 * randomNormal();
        printf("%g ", rands[i]);
    }
}

char * too_easy;
