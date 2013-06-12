/*
* Author: Dr. Mobus
* TCSS 371
* Date 7 October 2012
* Assignment 2 Simulating Logic Gates
* bit_def.h simulates a bit
*/
#ifndef BIT_DEF_H
#define BIT_DEF_H

typedef unsigned char bit;        // simulates a single bit, we'll use the low order bit in a byte

#ifndef BIT0_MASK
#define BIT0_MASK 0x01
#endif

#ifndef TRUE 
#define TRUE 1
#define FALSE 0
#endif

#define BIT_DEF_H

/**
* bit maskBit(bit a)
* Takes an unsigned char and makes sure all but lowest bit is 0 to 
* simulate one bit.
*/
bit maskBit(bit a);

#endif //#ifndef BIT_DEF_H
