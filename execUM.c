#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "execUM.h"
#include "bitpack.h"
#include "instruction.h"


static uint64_t get_reg (uint64_t word, unsigned width, unsigned lsb) {
	word = word << (64 - width - lsb);
	word = word >> (64 - width);
	return word;
}

struct T {
	Seg_T segment_memory;
	uint32_t *r;
	uint32_t prog_cntr;
}; typedef struct T* T;

T newProg() {
	T prog = malloc(sizeof(struct T));
	prog->segment_memory = segmentNew();
	prog->r = calloc(8, sizeof(uint32_t));
	prog->prog_cntr = 0;
	return prog;
}
void runProg(T prog, const char* input) {
	uint32_t instruction;
	uint32_t a, b, c;
	int filesize = 
	while(prog_cntr < programLength) {
		uint32_t operation = mem_get_op(memory, 0, prog_cntr);
		uint32_t opcode = get_reg(operation, 4, 28);

		if (opcode == 13) {
			a = get_reg(operation, 3, 7);
			value = get_reg(operation, 25, 0);
			loadval(a, value, r);

		}
		else if (opcode < 13 && opcode >= 0) {
			a = get_reg(operation, 3, 6);
			b = get_reg(operation, 3, 3);
			c = get_reg(operation, 3, 0);
			//conmove
			if (opcode == 0) {
				conmove(a, b, c, r);
			}
			//
			else if (opcode == 1) {
				segload(a, b, c, r, memory);
			}
			else if (opcode == 2) {
				segstore(a, b, c, r, memory);
			}
			else if (opcode == 3) {
				add(a, b, c, r);
			}
			else if (opcode == 4) {
				mult(a, b, c, r);
			}
			else if (opcode == 5) {
				div(a, b, c, r);
			}
			else if (opcode == 6) {
				nand(a, b, c, r);
			}
			else if (opcode == 7) {
				halt(memory, unmapped);
			}
			else if (opcode == 8) {
				mapseg(b, c, r, memory, unmapped);
			}
			else if (opcode == 9) {
				unmapseg(c, r, memory, unmapped);
			}
			else if (opcode == 10) {
				output(c, r);
			}
			else if (opcode == 11) {
				input(c, r);
			}
			else if (opcode == 12) {
				load(b, c, r, memory);
			}
		}
		else {
			exit(1);
		}
	}
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

void freeUM(T* um){
    Segment_free(&((*um)->memory));
    free((*um)->registers);
    free(*um);
}


#define OPCODE_LEN 4
#define OPCODE_LSB 28
#define REG_ID_LEN 3
#define VAL_LENGTH 25
#define A_LSB 6
#define B_LSB 3
#define C_LSB 0

