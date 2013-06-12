/*
* Author: Danielle Tucker
* TCSS 371
* Date 10 November 2012
* Project 3 - Ripple Carry Adder Simulation
* ALU.c - simulating an ALU
*/
#include <stdlib.h>
#include <stdio.h> //only needed for testing in main()
#include "ALU.h"
#include "errors.h"

//The following are needed object files:
// bit_man.c, Register.c, logic_gate.c, RippleCarryAdder.c, FullAdder.c

//Functions
/**
* ALU* ALUConstructor()
* Allocates memory for the ALU struct and initilizes all values to some random numer.
* Returns a pointer to the struct.
*/
ALU* ALUConstructor()
{
	ALU* alu = (ALU*) malloc(sizeof(ALU));
	alu->rca = rippleCarryAdderConstructor();
	alu->operandA = initialize();
	alu->operandB = initialize();
	rippleCarryAdderSetRegisters(alu->rca, alu->operandA, alu->operandB);
	alu->resultR = initialize();
	alu->PSR = initialize();
	return alu;
}

/**
* int ALUadd(ALU* this)
* Performs the following operation: resultR <- operandA + operandB 
* Returns an error if there was a problem.
*/
int ALUadd(ALU* this)
{
	rippleCarryAdderSetRegisters(this->rca, this->operandA, this->operandB);

	rippleCarryAdderAdd(this->rca);
	int error = 0;
	this->resultR = rippleCarryAdderGetResult(this->rca, &error);
	Register old_flags = rippleCarryAdderGetFlags(this->rca, &error);
	this->PSR = old_flags << 12;
	return error;
}

/**
* int ALUsub(ALU* this)
* Performs the following operation: resultR <- operandA - operandB 
* Returns an error if there was a problem.
*/
int ALUsub(ALU* this)
{
	Register temp_register = this->operandA;
	putOperandA(this, this->operandB);
	ALUneg(this);
	putOperandA(this, temp_register);
	putOperandB(this, this->resultR);
	ALUadd(this);
	return NO_ERROR;
}

/**
* int ALUneg(ALU* this)
* Performs the following operation: resultR <- -operandA 
* Returns an error if there was a problem.
*/
int ALUneg(ALU* this)           
{
	//Store operandB so we can utalize the ripple carry adder
	Register temp = this->operandB;
	rippleCarryAdderSetRegisters(this->rca, ~this->operandA, 1);
	rippleCarryAdderAdd(this->rca);
	int error = 0;
	this->resultR = rippleCarryAdderGetResult(this->rca, &error);
	//Put the previous value back into B
	putOperandB(this, temp);
	setFlags(this);
	return error;
}

/**
* int ALUnot(ALU* this)
* Performs the following operation: resultR <- ~operandA 
* Returns an error if there was a problem.
*/
int ALUnot(ALU * this)
{
	this->resultR = ~this->operandA;
	setFlags(this);
	return NO_ERROR;
}

/**
* int ALUand(ALU* this)
* Performs the following operation: resultR <- operandA & operandB 
* Returns an error if there was a problem.
*/
int ALUand(ALU* this)
{
	this->resultR = this->operandA & this->operandB;
	setFlags(this);
	return NO_ERROR;
}

/**
* int ALUor(ALU* this)
* Performs the following operation: resultR <- operandA | operandB 
* Returns an error if there was a problem.
*/
int ALUor(ALU* this)
{
	this->resultR = this->operandA | this->operandB;
	setFlags(this);
	return NO_ERROR;
}

//Helper functions
/**
* int setFlags(ALU* this)
* For all ALU functions - overflow, negative, zero, and carry flags are set
* based on the values in the operand and result registers.  This function
* only calculates the flags for the logic functions as the other operations
* have flags which are determined by the ripple carry adder and calculated in
* the appropiate functions ALUadd ALUsub.
*/
int setFlags(ALU* this)
{
	//overflow and carry out are taken care of in the adding funciton by the ripple carry adder
	//so only use this function for logic operations.
	this->PSR = 0;
	int error = 0;
	//Flag_Z - result is zero;
	int i;
	bit temp_flag = 0;
	for(i = 0; i < REGISTER_BIT_SIZE; i++)
	{
		temp_flag = or(get_bit(this->resultR, i, &error), temp_flag);
	}
	if(temp_flag == 0)
	{
		this->PSR = this->PSR | PSR_Z;
	}
	
	//Flag_N - result is negative;
	if(get_bit(this->resultR, REGISTER_BIT_SIZE-1, &error) > 0)
	{
		this->PSR = this->PSR | PSR_N;
	} 
	return error;
}
/**
* Register getResult(ALU* this)
* Returns the value in the Result Register
*/
Register getResult(ALU* this)
{
	return this->resultR;
}

/**
* Register getALUFlags(ALU* this)
* Gets the bit vector for the ALU flags.
* PSR[15]=Negative, PSR[14]=Zero, PSR[13]=CarryOut, and PSR[12]=Overflow
*/
Register getALUFlags(ALU* this)
{
	return this->PSR;
}

/**
* int putOperandA(ALU* this, Register value)
* Set the A operand of the ALU to the value.  Also sets up the underlying RippleCarryAdder
* with this value.
* Returns an error if one occured.
*/
int putOperandA(ALU* this, Register value)
{
	set_register(&this->operandA, value);
	rippleCarryAdderSetRegisters(this->rca, this->operandA, this->operandB);
	return NO_ERROR;
}

/**
* int putOperandB(ALU* this, Register value)
* Set the B operand of the ALU to the value.  Also sets up the underlying RippleCarryAdder
* with this value.
* Returns an error if one occured.
*/
int putOperandB(ALU* this, Register value)   /* puts the argument (int or register) into operandB */
{
	set_register(&this->operandB, value);
	rippleCarryAdderSetRegisters(this->rca, this->operandA, this->operandB);
	return NO_ERROR;
}

/*
int main()
{
	ALU* alu = ALUConstructor();
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));

	putOperandA(alu, 0x1111);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));
	putOperandB(alu, 0x0000);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));

	printf("AND\n");
	ALUand(alu);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));
	
	printf("OR\n");
	putOperandA(alu, 0xffff);
	ALUor(alu);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));
	
	printf("NOT\n");
	ALUnot(alu);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));

	printf("NEGATE\n");
	putOperandA(alu, 0x04);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));
	ALUneg(alu);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));

	printf("\nTesting ADD\n");
	putOperandA(alu, 0x70b0);
	putOperandB(alu, 0x41aa);
	ALUadd(alu);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));

	printf("\n");
	putOperandA(alu, 0xa123);
	putOperandB(alu, 0x8001);
	ALUadd(alu);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));

	printf("\n");
	putOperandA(alu, 0xa123);
	putOperandB(alu, 0x7001);
	ALUadd(alu);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));

	printf("\n");
	putOperandA(alu, 0x0000);
	putOperandB(alu, 0x0000);
	ALUadd(alu);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));

	printf("\n");
	putOperandA(alu, 0xfffc);
	putOperandB(alu, 0x0001);
	ALUadd(alu);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));

	printf("\nTesting SUBTRACT\n");
	putOperandA(alu, 0x0007);
	putOperandB(alu, 0x0001);
	ALUsub(alu);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));

	printf("\n");
	putOperandA(alu, 0x0000);
	putOperandB(alu, 0x000a);
	ALUsub(alu);
	printf("A = %04x, B = %04x, R = %04x FLAGS = %04x\n", alu->operandA, alu->operandB, getResult(alu), getALUFlags(alu));
	return NO_ERROR;
}
*/
