#define LINELEN 256
#define BUFLEN 10100
#define NUMTHREADS 4

typedef struct {
char searchFor; // character to search for
int startIndex; // start index in buffer[] at which to begin searching
int endIndex; // end index
int longestRun; // result: the longest run found of the specified character in buffer[],
// between startIndex and endIndex (inclusive)
} SearchStruct;

//nextFree is used to track the next available spot in the buffer
int nextFree = 0;
int readFile(char *fileName, int *numChars);
void *runner(void *param);
int main(int argc, char *argv[]);
