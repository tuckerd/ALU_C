/*
* Author: Danielle Tucker
* TCSS 371
* Date 13 October 2012
* Project 2 - Ripple Carry Adder Simulation
* FullAdder.h includes includes, typdefs, and prototypes needed for FullAdder.c
*/

#ifndef FULL_ADDER_H
#define FULL_ADDER_H

#include "bit_def.h"
#include "logic_gate.h"

typedef struct {
	bit a;
	bit b;
	bit c_in;
	bit r;
	bit c_out;
} FullAdder;

typedef FullAdder * FullAdderPtr;

//Function Prototypes

//Constructors and Cleanup
/**
* FullAdderPtr fullAdderConstructor()
* Allocates memory and initializes all values in this struct to 0;
* Returns a pointer to this struct.
*/
FullAdderPtr fullAdderConstructor();

/**
* int fullAdderClear(FullAdderPtr this)
* Clears (resets) all of the values in the Full Adder to 0
* Returns an error if there was a problem.
*/
int fullAdderClear(FullAdderPtr this); 

/**
* int fullAdderDestructor (FullAdderPtr this) 
* Frees all memory associated with this struct.
*/
int fullAdderDestructor (FullAdderPtr this); 

//Operations
/**
* bit fullAdder (bit a, bit b, bit c_in, bit * c_out)
* Returns the value of the fullAdder calculation.
* Note: the result value is not set in this function.
* See fullAdderPtrCompute()
* This function should not be used outside this program.
*/
bit fullAdder (bit a, bit b, bit c_in, bit * c_out);

/**
* int fullAdderPtrCompute(FullAdderPtr this)
* Computes the result of the fullAdder calculation and sets the result bit
* Returns an error if a problem occured.
*/
int fullAdderPtrCompute(FullAdderPtr this);

//Getters on Structure
/**
* bit getABit(FullAdderPtr this)
* Returns the value of the A bit in this Full Adder.
*/
bit getABit(FullAdderPtr this);

/**
* bit getBBit(FullAdderPtr this)
* Returns the value of the B bit in this Full Adder.
*/
bit getBBit(FullAdderPtr this);

/**
* bit getCarryInBit(FullAdderPtr this)
* Gets the current carry in bit value.
*/
bit getCarryInBit(FullAdderPtr this);

/**
* bit getCarryOutBit(FullAdderPtr this)
* Gets the current carry out bit value.
*/
bit getCarryOutBit(FullAdderPtr this);

/**
* bit * getCarryOutBitPtr(FullAdderPtr this)
* Provides a pointer to the carry out bit for use in
* a ripple carry adder.
*/
bit * getCarryOutBitPtr(FullAdderPtr this);

/**
* bit getResultBit(FullAdderPtr this)
* Returns the current result bit that is in the full adder.
* Make sure you perform the add before checking this to get result
* or it might be set to the previous result.
*/
bit getResultBit(FullAdderPtr this);

//Setters on Structure
/**
* int setInputBits(FullAdderPtr this, bit a, bit b, bit c_in)
* Sets both the a, b, and carry in bit of the full adder.
*/
int setInputBits(FullAdderPtr this, bit a, bit b, bit c_in);

/**
* int setABit(FullAdderPtr this, bit a)
* Sets the A bit input to this Full Adder
*/
int setABit(FullAdderPtr this, bit a);

/**
* int setBBit(FullAdderPtr this, bit b)
* Sets the B bit input to this Full Adder
*/
int setBBit(FullAdderPtr this, bit b);

/**
* int setCarryInBit(FullAdderPtr this, bit c_in)
* Sets the CarryIn bit in the struct. 1 if there was carry in, else 0
*/
int setCarryInBit(FullAdderPtr this, bit c_in);

/**
* int setCarryOutBit(FullAdderPtr this, bit c_out)
* Sets the CarryOut bit in the struct. 1 if there was carry out, else 0
* Should not be used outside this program.
*/
int setCarryOutBit(FullAdderPtr this, bit c_out);

/**
* int setResultBit(FullAdderPtr this, bit r)
* Sets the Result Bit in this struct.  Should not be used outside
* this program.  Returns a result if there was an error.
*/
int setResultBit(FullAdderPtr this, bit r);

//Report Structure toString
/**
* char * fullAdderToString(FullAdderPtr this)
* Provides a string representation of the state of all of the values in the FullAdder struct.
*/
char * fullAddertoString(FullAdderPtr this);

#endif //#ifndef FULL_ADDER_H

