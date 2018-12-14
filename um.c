#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "bitpack.h"
#include "segment.h"
#include "instruction.h"

//Initialized registers
static uint32_t r[8] = {0,0,0,0,0,0,0,0};

//initialize program counter
static int prgcntr = 0;

#define OPCODE_LEN 4
#define OPCODE_LSB 28
#define REG_ID_LEN 3
#define VAL_LENGTH 25
#define A_LSB 6
#define B_LSB 3
#define C_LSB 0


struct T {
        T memory;
        uint32_t *registers;
        uint32_t prog_counter;
};
typedef struct T *T;


// Function prototypes
T newUM();
void runUM(T um, const char* input);
void freeUM(T* um);
size_t get_file_size(const char *filename);
void load_file(T um, int size, const char* input);
void route_instruct(T um, WORD_SIZE instruct);





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


T newUM(){
    T um = malloc(sizeof(struct UM_T));
    um->memory = Segment_new();
    um->registers = calloc(8, sizeof(uint32_t));
    um->prog_counter = 0;
    return um;
}


void runUM(T um, const char* input){
    uint32_t curr_inst;
    int size = get_file_size(input);
    
    assert(Segment_map(um->memory, size) == 0);
    
    load_file(um, size, input);
    
    while(true){
        curr_inst = segment_load(um->memory, 0, um->prog_counter);    
        route_instruct(um, curr_inst);
        um->prog_counter += 1;
    }
    return;
}

void freeUM(T* um){
    Segment_free(&((*um)->memory));
    free((*um)->registers);
    free(*um);
}




size_t get_file_size(const char *filename){
    struct stat st;
    int size;
    if (stat(filename, &st) != 0) {
        printf("Incompatible file size. \n");
        exit(1);
    }
    size = st.st_size;
    
    if (size % 4 != 0){
        printf("Incompatible File Size. \n");
        exit(1);
    }
    return size / 4;
}



void load_file(T um, int size, const char* input){
    uint32_t word = 0;
    uint32_t num_words = size;
    unsigned char c;
    FILE* fp = fopen(input, "rb");
    for (uint32_t = 0; i < num_words; i++) {
        c = getc(fp);
        word = Bitpack_newu(word, 8, 24, (uint64_t)c);
        c = getc(fp);
        word = Bitpack_newu(word, 8, 16, (uint64_t)c);
        c = getc(fp);
        word = Bitpack_newu(word, 8, 8, (uint64_t)c);
        c = getc(fp);
        word = Bitpack_newu(word, 8, 0, (uint64_t)c);
        Segment_store(um->memory, 0, i, word);
    }
    fclose(fp);
}



void route_instruct(T um, uint32_t instruct){
    short opcode = Bitpack_getu(instruct, OPCODE_LEN, OPCODE_LSB);
    short a_id = Bitpack_getu(instruct, REG_ID_LEN, A_LSB);
    short b_id = Bitpack_getu(instruct, REG_ID_LEN, B_LSB);
    short c_id = Bitpack_getu(instruct, REG_ID_LEN, C_LSB);
    uint32_t* a_prt = &((um->registers)[a_id]);
    uint32_t* a_prt = &((um->registers)[b_id]);
    uint32_t* a_prt = &((um->registers)[c_id]);
    uint32_t val;
    
    switch(opcode){
        
        case 0:
            coditional_move(a_ptr, b_prt, c_prt);
            break;
        case 1:
            load(um->memory, a_ptr, b_prt, c_prt);
            break;
        case 2:
            store(um->memory, a_ptr, b_prt, c_prt);
            break;
        case 3:
            add(a_ptr, b_prt, c_prt);
            break;
        case 4:
            multiply(a_ptr, b_prt, c_prt);
            break;
        case 5:
            divide(a_ptr, b_prt, c_prt);
            break;
        case 6:
            nand(a_ptr, b_prt, c_prt);
            break;
        case 7:
            freeUM(&um);
            halt();
        case 8:
            map_segment(um->memory, b_ptr, c_ptr);
            break;
        case 9:
            ummap_segment(um->memory, c_ptr);
            break;
        case 10:
            output(c_ptr);
            break
        case 11:
            input(c_ptr);
            break;
        case 12:
            load_program(um->memory, b_ptr, c_ptr);
            um->prog_counter = *c_ptr - 1;
            break;
        case 13:
            val = Bipack_getu(instruct, VAL_LENGTH, VAL_LSB);
            a_id = Bitpack_getu(instruct, REG_ID_LEN, OPCODE_LSB - REG_ID_LEN);
            a_ptr = &((um->registers)[a_id]);
            load_value(a_ptr, val);
            break;
        default:
            printf("Invalid instruction. \n");
            freeUM(&um);
            exit(1);     
    }
    
}


