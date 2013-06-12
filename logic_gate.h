/*
* Author: Danielle Tucker
* TCSS 371
* Date 7 October 2012
* Assignment 2 Simulating Logic Gates
* logic_gate.h includes the function prototypes for logic gates
*/

#ifndef LOGIC_GATE_H
#define LOGIC_GATE_H

/**
* bit not(bit);
* Returns the logical NOT of the bit provided.
*/
bit not(bit);

/**
* bit and(bit, bit);
* Takes two bits and returns the logical AND of the bits. 
*/
bit and(bit, bit);

/**
* bit or(bit, bit);
* Takes two bits and returns the logical OR of the bits. 
*/
bit or(bit, bit);

/**
* bit xor(bit, bit);
* Takes two bits and returns the logical EXCLUSIVE OR of the bits
*/
bit xor(bit, bit);

/**
* bit nand(bit, bit);
* Takes two bits and returns the logical NOT AND of the bits
*/
bit nand(bit, bit);

/**
* bit nor(bit, bit);
* Takes two bits and returns the logical NOT OR of the bits
*/
bit nor(bit, bit);   // used to simulate logical NOT OR gate

#endif //#ifndef LOGIC_GATE_H
