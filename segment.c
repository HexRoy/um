//ATEMPT TO CHANGE THIS AROUND A LITTLE
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "seq.h"
#include "assert.h"
#include <string.h>
#include "segment.h"

#define T Seg_T
struct T {
	Seq_T unmappedIDs;
	Seq_T segments;
} ;

T segmentNew() {
	T segment_memory = malloc(sizeof(struct Seg_T));
	assert(Seg_T != NULL);
	Seq_T IDs = Seq_new(1000);
	Seq_T segments = Seq_new(1000);
	for (uint32_t i = 0; i < 1000; i++) {
		Seq_addhi(ids, (void *)(uintptr_t) i);
	}

	segment_memory->unmappedIDs = IDs;
	segment_memory->segments = segments;

	return segment_memory;
}

uint32_t segmentMap(T segment_memory, unsigned size) {

	uint32_t seg = malloc(sizeof(uint32_t) * (size + 1));
	for (uint32_t i = 0; i < (size + 1); i++) {
		seg[i] = 0;
	}

	assert(seg != NULL);
	seg[0] = size;
	uint32_t ID;
	Seq_T segments = segment_memory->segments;
	Seq_T unmapped = segment_memory->unmappedIDs;
	uint32_t unmappedLength = Seq_length(unmapped);
	uint32_t LengthOfSegments = Seq_length(segments);

	if (unmappedLength == 0) {
		for (uint32_t i = LengthOfSegments; i < LengthOfSegments + 1000; i++) {
			Seq_addhi(unmapped, (void *)(uintptr_t)i);
		}
	}

	ID = (uint32_t)(uintptr_t)Seq_remlo(unmapped);

	if (ID >= LengthOfSegments) {
		Seq_addhi(segments, seg);
	}

	else {
		Seq_put(segments, ID, seg);
	}

	return ID;
}

void segmentUnmap(T segment_memory, uint32_t ID) {
	uint32_t test;
	Seq_addlo(segment_memory->unmappedIDs, (void *)(uintptr_t)ID);
	test = Seq_get(segment_memory->segments, ID);
	free(test);
	Seq_put(segment_memory->segments, ID, NULL); 
}

void segmentSave(T segment_memory, uint32_t ID, uint32_t offset, uint32_t word) {
	uint32_t segment = Seq_get(segment_memory->segments, ID);
	segment[offset + 1] = word;
}

uint32_t segmentLoad(T segment_memory, uint32_t ID, uint32_t offset) {
	uint32_t segment = Seq_get(segment_memory->segments, ID);
	return segment[offset + 1];
}

void segmentFree(T segment_memory) {
	int length = Seq_length(segment_memory->segments);
	for (int i = 0; i < length; i++) {
		free(Seq_get(segment_memory->segments, i));
	}

	Seq_free(segment_memory->segments);
	Seq_free(segment_memory->unmappedIDs);
	free(segment_memory);
}

void segmentMove(T segment_memory, uint32_t sourceSeg, uint32_t destinationSeg) {
	uint32_t src = Seq_get(segment_memory->segments, sourceSeg);
	uint32_t size = src[0];
	segmentUnmap(segment_memory, destinationSeg);
	assert(segmentMap(segment_memory, size) == destinationSeg);
	uint32_t dest = Seq_get(segment_memory->segments, destinationSeg);
	memcpy(dest, src, ((size + 1) * sizeof(uint32_t)));
}