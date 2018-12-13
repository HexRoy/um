#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "execUM.h"
#include "bitpack.h"
#include "instruction.h"

//8 general purpose registers...
static uint32_t r[8] = {0,0,0,0,0,0,0,0};

//initialize program counter
static int prog_cntr = 0;

static uint64_t get_reg(uint64_t word, unsigned width, unsigned lsb) {
	word = word << (64 - width - lsb);
	word = word >> (64 - width);
	return word;
}

void runProg(struct segment *prog) {
	//????
	uint32_t a, b, c;
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
