#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "pidigits.ifrancke.h"
char buffer[BUFLEN];
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

void *runner(void *param){
    SearchStruct *data;
    int longest = 0;
    int count = 0;

    data = (SearchStruct *) param;
    for (int i=data->startIndex; i<=data->endIndex; ++i) {
        if (buffer[i]-'0' == data->searchFor){
            if(buffer[i+1]-'0' == data->searchFor){
                ++count;
            }
            else{
                if(count > longest){
                    longest = count;
                }
                count = 1;
            }
        }
  }
  data->longestRun = longest;

}

int main(int argc, char *argv[]) {
    int rc, numChars, search;
    if (argc < 2) {
        printf("ERROR: need a filename\n");
        return 8;
    }
    rc = readFile(argv[1], &numChars);
    if (rc != 0)
        return 8;

    printf("Enter the number you're looking for:\n");
    scanf("%d", &search);

    //setting up section separation
    SearchStruct sections[NUMTHREADS];
    pthread_t threads[NUMTHREADS];
    for(int i = 0; i < NUMTHREADS; i++){
        sections[i].searchFor = search;
        //nextFree is the number of actual values in the buffer
        sections[i].startIndex = i*nextFree/4;
        sections[i].endIndex = (i+1)*nextFree/4;
        if(i==3){
            //need to decrement the last case so it isn't searching empty values
            --sections[i].endIndex;
        }
        printf("I am thread %d. I start at %d and end at %d and I'm looking for %d.\n", i, sections[i].startIndex, sections[i].endIndex, sections[i].searchFor);
        pthread_create(&threads[i], NULL, runner, &sections[i]);
    }
    for(int i = 0; i < NUMTHREADS; i++){
        pthread_join(threads[i], NULL);
    }
    int maxLongestRun = 0;
    for(int i = 0; i < NUMTHREADS; i++){
        printf("Longest run section %d : %d\n", i, sections[i].longestRun);
        if(sections[i].longestRun > maxLongestRun){
            maxLongestRun = sections[i].longestRun;
        }
    }

    printf("Longest Run: %d\n", maxLongestRun);

    return 0;
}