#include "../lib.h"

#include <stdlib.h>
#include <netinet/in.h>
#include <dirent.h>
#include <sys/stat.h>
#include <math.h>
#include <time.h>

#define TOTAL_CHALLENGES 12
#define WRITE_EBADF 13
#define ASCII_NO_REPRESENTABLES 32
#define CANT_CHARACTER_USED 123
#define BLACK_COLOR_PRINTF "\033[0;30m"
#define RESET_COLOR "\033[37m"
#define PI 3.14159265358979323846

typedef void (*functiontype)();

int challenge(int current_challenge, int socket);

void doNothing();

void challenge4();

void challenge6();

void challenge7();

void challenge8();

void challenge10();

void challenge11();

void challenge12();