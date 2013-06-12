/*
* Author: Dr. Mobus
* TCSS 371
* Date 7 October 2012
* Assignment 2 Simulating Logic Gates
* bit_man.c simulates a bit
*/

#include "bit_def.h"

/**
* bit maskBit(bit a)
* Takes an unsigned char and makes sure all but lowest bit is 0 to 
* simulate one bit.
*/
bit maskBit(bit a) { a &= 0x01; return a; }
