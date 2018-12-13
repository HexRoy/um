#include <math.h>
#include <stdio.h>
#include "segment.h"
#include "execUM.h"
//INSTRUCTIONS


//OPCODE 0
void conmove(uint32_t a, uint32_t b, uint32_t c, uint32_t *r) {
	if (c != 0) {
		r[a] = r[b];
	}
}

//OPCODE 1
void segload(uint32_t a, uint32_t b, uint32_t c, uint32_t *r, Seg_T segment_memory) {
	r[a] = segmentLoad(segment_memory, r[b], r[c]);
}

//OPCODE 2
void segstore(uint32_t a, uint32_t b, uint32_t c, uint32_t *r, Seg_T segment_memory) {
	segmentSave(segment_memory, r[a], r[b], r[c]);
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
	printf("program has succesfully been completed");
}

//OPCODE 8
void mapseg(uint32_t b, uint32_t c, uint32_t *r , Seg_T segment_memory) {

	r[b] = segmentMap(segment_memory, r[c]);
}

//OPCODE 9
void unmapseg(uint32_t c, uint32_t *r, Seg_T segment_memory) {
	
	segmentUnmap(segment_memory, r[c]);
}

//OPCODE 10
void output(uint32_t c, uint32_t *r) {
	putchar(r[c]);
}

//OPCODE 11
void input(uint32_t c, uint32_t *r) {
	uint32_t input = getchar();
	assert(input <= 255);
	r[c] = input;
	//--------------------------------COMPLETE ME---------------------------------------------

}

//OPCODE 12
void load(uint32_t b, uint32_t c, uint32_t *r, Seg_T segment_memory) {
//--------------------------------COMPLETE ME---------------------------------------------
	if (r[b] != 0) {
			segmentMove(segment_memory, r[b], 0);
	}
}

//OPCODE 13
void loadval(uint32_t a, uint32_t val, uint32_t *r) {
	r[a] = val;
}






