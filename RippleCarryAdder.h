/*
* Author: Danielle Tucker
* TCSS 371
* Date 13 October 2012
* Project 2 - Ripple Carry Adder Simulation
* RippleCarryAdder.h includes includes, typdefs, and prototypes needed for RippleCarryAdder.c
*/

#ifndef RIPPLE_CARRY_ADDDER_H
#define RIPPLE_CARRY_ADDDER_H

#include "bit_def.h"
#include "logic_gate.h"
#include "FullAdder.h"
#include "Register.h"

#define REGISTER_BIT_SIZE 16

#define FLAG_O 0x1
#define FLAG_C 0x2
#define FLAG_Z 0x4
#define FLAG_N 0x8

/*
* Ripple Carry Adder Struct to simulate the addition of two bits and the
* flag associated with each addition.
*/
typedef struct {
	FullAdder adders[REGISTER_BIT_SIZE];
	Register A, B, R;
	unsigned char flags; // flags[0]=O, flags[1]=C, flags[2]=Z, flags[3]=N
} RippleCarryAdder;

typedef RippleCarryAdder * RippleCarryAdderPtr;

//Function Prototypes

//Constructors and Cleanup
/*
* RippleCarryAdderPtr RippleCarryAdderConstructor();
* Creates a Pointer to a RippleCarryAdder struct and allocates appropiate memory.
*/
RippleCarryAdderPtr rippleCarryAdderConstructor();

/*
* int rippleCarryAdderClear(RippleCarryAdderPtr this);
* Resets a RippleCarryAdder to a default state (clears the input bits) and returns
* an error code if there was a problem.
*/
int rippleCarryAdderClear(RippleCarryAdderPtr this);

/*
* int rippleCarryAdderDestructor(RippleCarryAdderPtr this);
* Destroys the memory allocated by the RippleCarryAdderConstructor
*/
int rippleCarryAdderDestructor(RippleCarryAdderPtr this);

//Operations
/*
* int rippleCarryAdderAdd(RippleCarryAdderPtr this);
* Performs bit addition on the bits which have been set by setBitAt 
* Returns an error code if there was a problem.
*/
int rippleCarryAdderAdd(RippleCarryAdderPtr this);

/*
* bit getBitAt(Register rgst, int bit_num, int * error);
* Gets the value of the bit in the Register rgst at location bit_num 
* Sets error if there was a problem.
*/
bit getBitAt(Register rgst, int bit_num, int * error);

/*
* int setBitAt(Register * rgst, int bit_num, bit value);
* Sets the value of the bit in the Register rgst at location bit_num 
* Returns error if there was a problem.
*/
int setBitAt(Register * rgst, int bit_num, bit value);

//Setters and Getters
/*int rippleCarryAdderSetRegisters(RippleCarryAdderPtr this, unsigned short A, unsigned short B);
* The inputs are set to A and B in the ripple carry adder struct for use in
* later calculations.
* If there is a problem, an error code will be returned.
*/
int rippleCarryAdderSetRegisters(RippleCarryAdderPtr this, unsigned short A, unsigned short B);

/*
* unsigned short rippleCarryAdderGetResult(RippleCarryAdderPtr this, int * error); 
* Returns the current value of the result "register" in the ripple
* carry adder.
*/
unsigned short rippleCarryAdderGetResult(RippleCarryAdderPtr this, int * error); 

/*
* unsigned char rippleCarryAdderGetFlags(RippleCarryAdderPtr this, int * error);
* Returns the current flag vector of the ripple carry adder.
* flags[3]=Negative, flags[2]=Zero, flags[1]=CarryOut, flags[0]=Overflow
*/
unsigned char rippleCarryAdderGetFlags(RippleCarryAdderPtr this, int * error);

//Reporting State
/*
* char * rippleCarryAdderToString(RippleCarryAdderPtr this);
* Provides a string representation of the current state of the values in the RCAdder
*/
char * rippleCarryAdderToString(RippleCarryAdderPtr this);

#endif //#ifndef RIPPLE_CARRY_ADDDER_H

