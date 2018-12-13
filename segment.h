#ifndef SEGMENT_INCLUDED
#define SEGMENT_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "seq.h"
#include "assert.h"
#include <string.h>
#include "segment.h"

#define T Seg_T     
typedef struct T *T;
T segmentNew();
uint32_t segmentMap(T segment_memory, unsigned size);
void segmentUnmap(T segment_memory, uint32_t ID);
void segmentSave(T segment_memory, uint32_t ID, uint32_t offset, uint32_t word);
uint32_t segmentLoad(T segment_memory, uint32_t ID, uint32_t offset);
void segmentFree(T segment_memory);
void segmentMove(T segment_memory, uint32_t sourceSeg, uint32_t destinationSeg);
#endif