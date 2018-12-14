#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "except.h"
#include "bitpack.h"
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * shl: to left shift the bits of a word
 * @param word: the words to bit shifted
 * @param bits: the number of bits
 * @return : the shifted word
 */
uint64_t shl(uint64_t word, unsigned bits){
    assert(bits <= 64);
    // if bits = 64, no need to shift
    if(bits == 64){
        return 0;
    }
    // else shift the word left by the number of bits
    else{
        return word << bits;
    }
}


/**
 * shr: to right shift the bits of a word
 * @param word: the word to be shifted
 * @param bits: the number of bits
 * @return : the shifted word
 */
uint64_t shr(uint64_t word, unsigned bits){
    assert(bits<= 64); 
    // if bits = 64, no need to shift
    if (bits == 64) {
        return 0;
    }
    // else shift the word right by the number of bits
    else {
        return word >> bits;
    }
}


/**
 * aShr: arith right shift
 * @param word: the word to be shifted
 * @param bits: the number of bits to shft by
 * @return : the signed shifted word
 */
uint64_t aShr(uint64_t word, unsigned bits){
    assert(bits <= 64);
    // 63 is the largest possible signed number
    if (bits == 64){
        bits = 63;
    }
    // Casts unsigned word to a signed word and shifts by the correct number
    // of bits
    return((int64_t) word) >> bits;
}


/**
 * Bitpack_fitsu:
 * @param n
 * @param width
 * @return 
 */
bool Bitpack_fitsu(uint64_t n, unsigned width) {
	if (width <= 64) { // if the value is between 0 and 2^width, return true
		return true;
	}
	if (shr(n, width) == 0){
            return true;
        }
        else{
            return false;
        }
}


/**
 * Bitpack_fitss: 
 * @param n
 * @param width
 * @return 
 */
bool Bitpack_fitss( int64_t n, unsigned width) {
    if (n < pow(2, width)/2) { //if the value is less than half of 2^width.
            if (abs(n) <= pow(2, width)/2) { //checks if the negative values are in the proper bounds, if so returns true
                    return true;
            }
            else {
                    return false;
            }
    }
    else {
            return false;
    }
        
    
    // New implementation
    if (width >= 64) {
        return true;
    }    
    uint64_t ls = shl(n, 64 - width);
    // changes unsigned n into signed narrow
    int64_t narrow = aShr(ls , 64 - width);
    // returns true if signed narrow == unsigned n
    return narrow == n;
        
}


/**
 * 
 * @param word
 * @param width
 * @param lsb
 * @return 
 */
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb) {
    // one above the MSB
    unsigned hi = lsb + width;
    assert(hi <= 64);
    // left shifts the word by one above the MSB
    uint64_t ls = shl(word, 64 - hi);
    return shr(ls, 64 - width);
}



int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb) {
    if (width == 0) {
        return 0;
    }
	// one above the MSB
    unsigned hi = lsb + width;
    assert(hi <= 64);
	
    uint64_t ls = shl(word, 64 - hi);
    return shr(ls, 64 - width);
}

uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, uint64_t value) {
	assert(Bitpack_fitsu(value, width)); //asserts that the width an value both fit.
	uint64_t tword = word;
	uint64_t tvalue = value;
	int shift = 64 - width; // defines the amount to shift by (similarly seen in Bitpack_getu and Bitpack_gets)
	tvalue = tvalue << lsb; //shifts value by the lsb to get the adjusted width-bit representation of the original value
	uint64_t temp = ~0; // initializes temporary word (decimal -1)
	temp = temp << (shift - lsb); //sets temp word to the same size as the original word
	temp = temp >> (shift);
	temp = temp << lsb;
	temp = ~temp; //bitwise compliment of this to use in comparison to the original word

	tword = tword & temp; //only keeps ones in common (all other 1's are now 0)
	tword = tword | tvalue; //replace with new value

	return tword; //return new word

        // New implementation 
        // one above the MSB
        unsigned hi = lsb + width;
        assert(hi <= 64);
        if (!Bitpack_fitsu(value, width)){
            RAISE(Bitpack_Overflow);
        }
        return shl(shr(word, hi), hi) | shr(shl(word, 64 - lsb), 64 - lsb) | (value << lsb);
        
}

uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb, int64_t value) { //same a Bitpack_newu with some slight modifications
	assert(Bitpack_fitss(value, width));
	uint64_t tword = word;
	uint64_t tvalue = (uint64_t) value; //since value is an int64_t we must cast value as an unsigned integer
	int shift = 64 - width;
	tvalue = tvalue << lsb;
	uint64_t temp = ~0;
	temp = temp << (shift - lsb);
	temp = temp >> (shift);
	temp = temp << lsb;
	temp = ~temp;

	tword = tword & temp;
	tword = tword | tvalue;

	return tword;
        
        
        // new implementation
        if (!Bitpack_fitss(value, width)) {
            RAISE(Bitpack_Overflow);
            return Bitpack_newu(word, width, lsb, Bitpack_getu(value, width, 0));
        }
        
}
