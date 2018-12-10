#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttype.h>
#include "bitpack.h"


//Initialized registers
static uint32_t r[8] = {0,0,0,0,0,0,0,0};

//initialize program counter
static int prgcntr = 0;



// Function prototypes
T newUM();
void runUM ();
void freeUM();
size_t getFileSize();
void loadFile();

struct T{
    
};



T newUM(){
    T um = malloc(sizeof(struct UM_T))
}





/**
 * main: the main of the UM
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char* argv[]){
    if (argc > 2){
        printf("Too many arguments \n");
        exit(1);
    }
    
    else if (argc == 2){
        // good start UM
    }
    
    else{
        printf("Too few arguments \n");
        exit(1);
    }
    return 1;    
}