#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "bitpack.h"
#include "segment.h"
#include "instruction.h"
#include "execUM.h"


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
        T um;
        runUM(um, argv[1]);
    }
    
    else{
        printf("Too few arguments \n");
        exit(1);
    }
    return 1;    
}
