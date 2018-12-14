#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "execUM.h"
#include "bitpack.h"
#include "instruction.h"

struct T {
	T segment_memory;
	uint32_t *r;
	uint32_t prog_cntr;
};


/**
 * newProg: creates a new UM
 *              defaults all registers to 0
 * @return 
 */
T newProg() {
	T prog = malloc(sizeof(struct T));
	prog->segment_memory = segmentNew();
	prog->r = calloc(8, sizeof(uint32_t));
	prog->prog_cntr = 0;
	return prog;
}


/**
 * runProg: runs all the instructions in the prog
 * @param UM
 * @param input
 */
void runProg(T UM, const char* input) {
	uint32_t instruction;
	openFile(UM, input);

	while(true) {
		instruction = segmentLoad(UM->segment_memory, 0, UM->prog_cntr);
		UM->prog_cntr += 1;
		opcode_instructions(UM, instruction);
	}
	return;
}


/**
 * openFile: reads the file and loads the instructions 
 * @param UM
 * @param input
 */
void openFile(T UM,  const char* input){
    char c;
    uint32_t word = 0;
    FILE* fp = fopen(input, "rb");
    uint32_t i = 0;
    c = getc(fp);
    while (c != EOF) {
        c = getc(fp);
        word = Bitpack_newu(word, 32, 0, (uint64_t)c);
        segmentSave(UM->segment_memory, 0, i, word);
        i++;
    }
    fclose(fp);
}


/**
 * opcode_instructions: executes the instruction based on the op code
 * @param UM
 * @param instruct
 */
void opcode_instructions(T UM, uint32_t instruct){
    uint32_t opcode = Bitpack_getu(instruct, 4, 28);
    uint32_t a, b, c, val;
    if (opcode == 13) {
			a = Bitpack_getu(instruct, 3, 25);
			val = Bitpack_getu(instruct, 25, 0);
			loadval(a, val, UM->r);
	}
	else if (opcode < 13) {
			a = Bitpack_getu(instruct, 3, 6);
			b = Bitpack_getu(instruct, 3, 3);
			c = Bitpack_getu(instruct, 3, 0);
			//conmove
			if (opcode == 0) {
				conmove(a, b, c, UM->r);
			}
			//
			else if (opcode == 1) {
				segload(a, b, c, UM->r, UM->segment_memory);
			}
			else if (opcode == 2) {
				segstore(a, b, c, UM->r, UM->segment_memory);
			}
			else if (opcode == 3) {
				add(a, b, c, UM->r);
			}
			else if (opcode == 4) {
				multiply(a, b, c, UM->r);
			}
			else if (opcode == 5) {
				divide(a, b, c, UM->r);
			}
			else if (opcode == 6) {
				nand(a, b, c, UM->r);
			}
			else if (opcode == 7) {
				freeUM(&UM);
				halt();
			}
			else if (opcode == 8) {
				mapseg(b, c, UM->r, UM->segment_memory);
			}
			else if (opcode == 9) {
				unmapseg(c, UM->r, UM->segment_memory);
			}
			else if (opcode == 10) {
				output(c, UM->r);
			}
			else if (opcode == 11) {
				input(c, UM->r);
			}
			else if (opcode == 12) {
				load(b, c, UM->r, UM->segment_memory);
			}
		}
		else {
			exit(1);
		}
}
    

/**
 * freeUM: frees the um from memory
 * @param UM
 */
void freeUM(T* UM){
    segmentFree(((*UM)->segment_memory));
    free((*UM)->r);
    free(*UM);
}




