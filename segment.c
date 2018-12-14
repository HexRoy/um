//ATEMPT TO CHANGE THIS AROUND A LITTLE
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "seq.h"
#include "assert.h"
#include <string.h>
#include "segment.h"


struct T {
	Seq_T unmappedIDs;
	Seq_T segments;
};


// function prototypes
T segmentNew();
void segmentMap(T segment_memory, unsigned numWords);
void segmentUnmap(T segment_memory, uint32_t ID);
void segmentSave(T segment_memory, uint32_t ID, uint32_t offset, uint32_t word);
uint32_t segmentLoad(T segment_memory, uint32_t ID, uint32_t offset);
void segmentFree(T segment_memory);



/**
 * segmentNew(): allocates the segment in memory
 * @return 
 */
T segmentNew() {
    T segment_memory = malloc(sizeof(struct Seg_T));
    assert(Seg_T != NULL);

    // Need to figure out how to store  ids and segments in seq_t
    //segment_memory->unmappedIDs = 
    //segment_memory->segments = 

    return segment_memory;
}


/**
 * segmentMap: to create a segment of size numWords
 * @param segment_memory
 * @param numWords
 */
void segmentMap(T segment_memory, unsigned numWords) {

    // malloc memory for the segment
    uint32_t seg = malloc(sizeof(uint32_t) * (numWords + 1));
    // set all values in the segment to 0
    for (uint32_t i = 0; i < (numWords + 1); i++) {
            seg[i] = 0;
    
    }
    // TODO
}


/**
 * segmentUnmap: frees a segment from memory
 * @param segment_memory
 * @param ID
 */
void segmentUnmap(T segment_memory, uint32_t ID) {
    Seq_addlo(segment_memory->unmappedIDs, (void *)(uintptr_t)ID);
    free(Seq_get(segment_memory->segments, ID));
    Seq_put(segment_memory->segments, ID, NULL); 
}


/**
 * segmentSave: saves a segment in memory with the correct offset
 * @param segment_memory
 * @param ID
 * @param offset
 * @param word
 */
void segmentSave(T segment_memory, uint32_t ID, uint32_t offset, uint32_t word) {
    uint32_t wordLocation = offset + 1;
    uint32_t segment = Seq_get(segment_memory->segments, ID);
    segment[wordLocation] = word;
}


/**
 * segmentLoad: to load a word in a specific segment of memory
 * @param segment_memory
 * @param ID
 * @param offset
 * @return 
 */
uint32_t segmentLoad(T segment_memory, uint32_t ID, uint32_t offset) {
    wordLocation = offset + 1;
    uint32_t segment = Seq_get(segment_memory->segments, ID);
    return segment[wordLocation];
}


/**
 * segmentFree: frees a segment from memory
 * @param segment_memory
 */
void segmentFree(T segment_memory) {
    //first free the segments and unmappedIDs
    free(segment_memory->segments);
    free(segment_memory->unmappedIDs);
    // then free the segment memory
    free(segment_memory);
}

