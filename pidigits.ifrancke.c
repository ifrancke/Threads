#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pidigits.ifrancke.h"

int readFile(char *fileName, int *numChars){
    FILE *fp = fopen(fileName, "r"); // filename is the char* passed to your readFile() function
    if (fp == NULL) {
        printf("ERROR: cannot open file '%s'\n", fileName);
        return 1;
    }
    //buffer that holds each line
    char line[LINELEN];
    //length of each line
    int len;
    //file contents
    char *chp = fgets(line, LINELEN, fp);
    if (chp == NULL) {
        printf("file is empty\n");
        fclose(fp);
        return 8;
    }
    while (chp != NULL) {
        len = strlen(line);
        if (line[len-1] == '\n')
            len = len - 1;
        for (int i=0; i<len; ++i) {
            buffer[nextFree] = line[i];
            ++nextFree;
        }
        chp = fgets(line, LINELEN, fp);
    } // while not at end of file

}

int main(int argc, char *argv[]) {
    int rc, numChars;
    if (argc < 2) {
        printf("ERROR: need a filename\n");
        return 8;
    }
    rc = readFile(argv[1], &numChars);
    if (rc != 0)
        return 8;
    // here’s where you’ll create the threads that do the actual searching
    for(int i = 0; i < nextFree; i++){
        printf(buffer[i]);
    }
    return 0;
}