#define LINELEN 256
#define BUFLEN 10100
char buffer[BUFLEN];
//nextFree is used to track the next available spot in the buffer
int nextFree = 0;
int readFile(char *fileName, int *numChars);
int main(int argc, char *argv[]);
