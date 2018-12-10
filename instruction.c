#include <math.h>
#include <stdio.h>


//INSTRUCTIONS


//OPCODE 0
void conmove(uint32_t a, uint32_t b, uint32_t c, uint32_t *r) {
	if (c != 0) {
		r[a] = r[b];
	}
}

//OPCODE 1
void segload(uint32_t a, uint32_t b, uint32_t c, uint32_t *r, Mem memory) {
//--------------------------------COMPLETE ME---------------------------------------------

}

//OPCODE 2
void segstore(uint32_t a, uint32_t b, uint32_t c, uint32_t *r, Mem memory) {
//--------------------------------COMPLETE ME---------------------------------------------

}

//OPCODE 3
void add(uint32_t a, uint32_t b, uint32_t c, uint32_t *r) {
	r[a] = (r[b] + r[c]) % pow(2, 32);
}

//OPCODE 4
void mult(uint32_t a, uint32_t b, uint32_t c, uint32_t *r) {
	r[a] = (r[b] * r[c]) % pow(2, 32);
}

//OPCODE 5
void div(uint32_t a, uint32_t b, uint32_t c, uint32_t *r) {
	r[a] = r[b] / r[c];
}

//OPCODE 6
void nand(uint32_t a, uint32_t b, uint32_t c, uint32_t *r) {
	r[a] = ~(r[b] & r[c]);
}

//OPCODE 7
void halt() {
	exit(EXIT_SUCCESS);
	//--------------------------------COMPLETE ME---------------------------------------------

}

//OPCODE 8
void mapseg() {
//--------------------------------COMPLETE ME---------------------------------------------

}

//OPCODE 9
void unmapseg() {
//--------------------------------COMPLETE ME---------------------------------------------

}

//OPCODE 10
void output(uint32_t c, uint32_t *r) {
	putchar(r[c]);
}

//OPCODE 11
void input(uint32_t c, uint32_t *r) {
	uint32_t input = getchar();
	assert(inpput <= 255);
	r[c] = input;
	//--------------------------------COMPLETE ME---------------------------------------------

}

//OPCODE 12
void load(uint32_t b, uint32_t c, uint32_t *r, Mem memory) {
//--------------------------------COMPLETE ME---------------------------------------------
}

//OPCODE 13
void loadval(uint32_t a, uint32_t val, uint32_t *r) {
	r[a] = val;
}






