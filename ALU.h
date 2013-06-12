/*
* Author: Danielle Tucker
* TCSS 371
* Date 10 November 2012
* Project 3 - Ripple Carry Adder Simulation
* ALU.h - includes, typdefs, and prototypes needed for simulating an ALU
*/
//ALU ADT/Class

#ifndef ALU_H
#define ALU_H

#include "bit_def.h"
#include "Register.h"
#include "RippleCarryAdder.h"

#define PSR_O 0x1000
#define PSR_C 0x2000
#define PSR_Z 0x4000
#define PSR_N 0x8000

typedef struct {
	RippleCarryAdderPtr rca;
	Register operandA;
	Register operandB;
	Register resultR;
	Register PSR;	// unlike the register in the LC-3, the condition code flags in this register are
					// PSR[15..12]; PSR[15]=N, PSR[14]=Z, PSR[13]=C, and PSR[12]=O
} ALU;


//Functions
/**
* ALU* ALUConstructor()
* Allocates memory for the ALU struct and initilizes all values to some random numer.
* Returns a pointer to the struct.
*/
ALU* ALUConstructor();

/**
* int ALUadd(ALU* this)
* Performs the following operation: resultR <- operandA + operandB 
* Returns an error if there was a problem.
*/
int ALUadd(ALU* this);

/**
* int ALUsub(ALU* this)
* Performs the following operation: resultR <- operandA - operandB 
* Returns an error if there was a problem.
*/
int ALUsub(ALU* this); 

/**
* int ALUneg(ALU* this)
* Performs the following operation: resultR <- -operandA 
* Returns an error if there was a problem.
*/
int ALUneg(ALU* this); 

/**
* int ALUnot(ALU* this)
* Performs the following operation: resultR <- ~operandA 
* Returns an error if there was a problem.
*/
int ALUnot(ALU * this);  

/**
* int ALUand(ALU* this)
* Performs the following operation: resultR <- operandA & operandB 
* Returns an error if there was a problem.
*/
int ALUand(ALU* this);

/**
* int ALUor(ALU* this)
* Performs the following operation: resultR <- operandA | operandB 
* Returns an error if there was a problem.
*/
int ALUor(ALU* this);            /* resultR <- operandA | operandB */

//Helper functions
/**
* int setFlags(ALU* this)
* For all ALU functions - overflow, negative, zero, and carry flags are set
* based on the values in the operand and result registers.  This function
* only calculates the flags for the logic functions as the other operations
* have flags which are determined by the ripple carry adder and calculated in
* the appropiate functions ALUadd ALUsub.
*/
int setFlags(ALU* this);

/**
* Register getResult(ALU* this)
* Returns the value in the Result Register
*/
Register getResult(ALU* this);

/**
* Register getALUFlags(ALU* this)
* Gets the bit vector for the ALU flags.
* PSR[15]=Negative, PSR[14]=Zero, PSR[13]=CarryOut, and PSR[12]=Overflow
*/
Register getALUFlags(ALU* this);

/**
* int putOperandA(ALU* this, Register value)
* Set the operand of the ALU to the value.  Also sets up the underlying RippleCarryAdder
* with this value.
* Returns an error if one occured.
*/
int putOperandA(ALU* this, Register value);   /* puts the argument (int or register) into operandA */

/**
* int putOperandB(ALU* this, Register value)
* Set the B operand of the ALU to the value.  Also sets up the underlying RippleCarryAdder
* with this value.
* Returns an error if one occured.
*/
int putOperandB(ALU* this, Register value);   /* puts the argument (int or register) into operandB */

#endif //#ifndef ALU_H
