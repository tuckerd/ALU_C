/*
* Author: Danielle Tucker
* TCSS 371
* Date 13 October 2012
* Project 2 - Ripple Carry Adder Simulation
* RippleCarryAdder.c simulates a Ripple Carry Adder for 16 bit registers
*/

#include <stdlib.h>
#include <stdio.h> //needed only for testing in main()
#include "RippleCarryAdder.h"
#include "errors.h"

/*need to chain load the following:
bit_man, logic_gate, fullAdder
*/

//Function Prototype for helper method
int calculateRippleCarryAdderFlags(RippleCarryAdderPtr this);

//Constructors and CleanUp
/**
* RippleCarryAdderPtr RippleCarryAdderConstructor();
* Creates a Pointer to a RippleCarryAdder struct and allocates appropiate memory.
*/
RippleCarryAdderPtr rippleCarryAdderConstructor()
{
	RippleCarryAdderPtr rca = (RippleCarryAdderPtr) malloc(sizeof(RippleCarryAdder));
	rippleCarryAdderClear(rca);
	return rca;
}

/**
* int rippleCarryAdderClear(RippleCarryAdderPtr this);
* Resets a RippleCarryAdder to a default state (clears the input bits) and returns
* an error code if there was a problem.
*/
int rippleCarryAdderClear(RippleCarryAdderPtr this)
{
	int i;
	if(this == NULL)	{return NULL_PTR_ERROR;}
	for (i = 0; i < REGISTER_BIT_SIZE; i++)
	{
		//initialize all values in the adders to 0x0;
		fullAdderClear(&(this->adders[i])); 
	}
	this->A = 0;
	this->B = 0;
	this->R = 0;
	this->flags = 0;
	
	return NO_ERROR;
}

/**
* int rippleCarryAdderDestructor(RippleCarryAdderPtr this);
* Destroys the memory allocated by the RippleCarryAdderConstructor
*/
int rippleCarryAdderDestructor(RippleCarryAdderPtr this)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}

	free(this);
	return NO_ERROR;
}

//Operations
/**
* int rippleCarryAdderAdd(RippleCarryAdderPtr this);
* Performs bit addition on the bits which have been set by setBitAt 
* Returns an error code if there was a problem.
*/
int rippleCarryAdderAdd(RippleCarryAdderPtr this)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}
	this->R = 0;
	//initial adding of bit 0 (no carry in)
	int error = 0;
	bit a = getBitAt(this->A, 0, &error);
	bit b = getBitAt(this->B, 0, &error);
	bit c_in;
	setInputBits(&this->adders[0], a, b, 0);
	fullAdderPtrCompute(&this->adders[0]);
	setBitAt(&this->R, 0, getResultBit(&this->adders[0]));
	int i;
	for(i = 1; i < REGISTER_BIT_SIZE; i++)
	{
		//Take Bit from Register A and B and put in adder
		a = getBitAt(this->A, i, &error);
		b = getBitAt(this->B, i, &error);
		c_in = getCarryOutBit(&this->adders[i-1]);
		setInputBits(&this->adders[i], a, b, c_in);
		//Compute ADD for that bit in the adder
		fullAdderPtrCompute(&this->adders[i]);
		//Take result from ADD and place in Result register
		setBitAt(&this->R, i, getResultBit(&this->adders[i]));
	}
	
	//set flags from calculation
	calculateRippleCarryAdderFlags(this);
	
	return NO_ERROR;
}
/**
* int calculateRippleCarryAdderFlags(RippleCarryAdderPtr this)
* Helper method used to calculate and set the flags in the RCAdder struct based
* on current inputs and result in the field.  This is a helper method and 
* not intended for use outside this program.
*/
int calculateRippleCarryAdderFlags(RippleCarryAdderPtr this)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}
	//check to see that calculation has been done somehow???
	this->flags = 0;
	int error;
	//Flag_O - overflow
	bit a = getBitAt(this->A, REGISTER_BIT_SIZE-1, &error);
	bit b = getBitAt(this->B, REGISTER_BIT_SIZE-1, &error);
	bit r = getBitAt(this->R, REGISTER_BIT_SIZE-1, &error);
	if(a != r && b != r)
	{
		this->flags = this->flags | FLAG_O;
	}
	
	//Flag_C - carry out on last bit;
	if(getCarryOutBit(&this->adders[REGISTER_BIT_SIZE-1]) > 0)
	{
		this->flags = this->flags | FLAG_C;
	}
	
	//Flag_Z - result is zero;
	int i;
	bit temp_flag = 0;
	for(i = 0; i < REGISTER_BIT_SIZE; i++)
	{
		temp_flag = or(getResultBit(&this->adders[i]), temp_flag);
	}
	if(temp_flag == 0)
	{
		this->flags = this->flags | FLAG_Z;
	}
	
	//Flag_N - result is negative;
	if(getBitAt(this->R, REGISTER_BIT_SIZE-1, &error) > 0)
	{
		this->flags = this->flags | FLAG_N;
	} 
}

/**
* bit getBitAt(Register rgst, int bit_num, int * error);
* Gets the value of the bit in the Register rgst at location bit_num 
* Sets error if there was a problem.
*/
bit getBitAt(Register rgst, int bit_num, int * error)
{
	if(bit_num > REGISTER_BIT_SIZE || bit_num < 0) 
	{
		*error = INDEX_OUT_OF_BOUNDS_ERROR;
		return 0;
	}

	return(rgst >> bit_num)& 0X01;
}

/**
* int setBitAt(Register * rgst, int bit_num, bit value);
* Sets the value of the bit in the Register rgst at location bit_num 
* Returns error if there was a problem.
*/
int setBitAt(Register * rgst, int bit_num, bit value)
{
	if(rgst == NULL)	{return NULL_PTR_ERROR;}
	if(bit_num > REGISTER_BIT_SIZE || bit_num < 0) 
		{return INDEX_OUT_OF_BOUNDS_ERROR;}

	bit temp = value & 0X01; //just to make sure no extra bits!
	*rgst = *rgst | (value << bit_num);
	
	return NO_ERROR;
}

//Setters and Getters
/**
* int rippleCarryAdderSetRegisters(RippleCarryAdderPtr this, unsigned short A, unsigned short B);
* The inputs are set to A and B in the ripple carry adder struct for use in
* later calculations.
* If there is a problem, an error code will be returned.
*/
int rippleCarryAdderSetRegisters(RippleCarryAdderPtr this, unsigned short A, unsigned short B)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}

	this->A = A & 0x0FFFF;
	this->B = B & 0x0FFFF;
	return NO_ERROR;
}

/**
* unsigned short rippleCarryAdderGetResult(RippleCarryAdderPtr this, int * error); 
* Returns the current value of the result "register" in the ripple
* carry adder.
*/
unsigned short rippleCarryAdderGetResult(RippleCarryAdderPtr this, int * error)
{
	if(this == NULL)	{*error = NULL_PTR_ERROR;}
	return this->R;
}

/**
* unsigned char rippleCarryAdderGetFlags(RippleCarryAdderPtr this, int * error);
* Returns the current flag vector of the ripple carry adder.
* flags[3]=Negative, flags[2]=Zero, flags[1]=CarryOut, flags[0]=Overflow
*/
unsigned char rippleCarryAdderGetFlags(RippleCarryAdderPtr this, int * error)
{
	if(this == NULL)	{*error = NULL_PTR_ERROR;}
	return this->flags;
}

/**
* char * rippleCarryAdderToString(RippleCarryAdderPtr this);
* Provides a string representation of the current state of the values in the RCAdder
*/
char * rippleCarryAdderToString(RippleCarryAdderPtr this)
{
	//reserving space for the string
	char * retString = (char *) malloc(sizeof(char)*32 + sizeof(Register)*3 + sizeof(unsigned char));
	sprintf(retString, "0x%04X + 0x%04X = 0x%04X  Flags: 0x%01X" , 
						this->A, this->B, this->R, this->flags);
	return retString;
	//need to destroy the string after you call this function!
}
/*
int main()
{
	char * output;
	int error;
	
	printf("---------Testing Constructor and ToString---------\n");
	RippleCarryAdderPtr test = rippleCarryAdderConstructor();
	output = rippleCarryAdderToString(test);
	printf("%s\n", output);
	free(output);
	
	printf("-------Testing Setting and Clearing Values--------\n");
	rippleCarryAdderSetRegisters(test, 0X70B0, 0X41AA);
	output = rippleCarryAdderToString(test);
	printf("%s\n", output);
	free(output);
	
	rippleCarryAdderClear(test);
	output = rippleCarryAdderToString(test);
	printf("%s\n", output);
	free(output);

	printf("\n----------------Testing Operations----------------\n");
	printf("Key to Flags: FLAG_O 0x1, FLAG_C 0x2, FLAG_Z 0x4, FLAG_N 0x8\n\n");

	rippleCarryAdderSetRegisters(test, 0X70b0, 0X41aa);
	rippleCarryAdderAdd(test);
	output = rippleCarryAdderToString(test);
	printf("%s\n", output);
	free(output);

	rippleCarryAdderClear(test);
	rippleCarryAdderSetRegisters(test, 0Xa123, 0X8001);
	rippleCarryAdderAdd(test);
	output = rippleCarryAdderToString(test);
	printf("%s\n", output);
	free(output);
	
	rippleCarryAdderClear(test);
	rippleCarryAdderSetRegisters(test, 0Xa123, 0X7001);
	rippleCarryAdderAdd(test);
	output = rippleCarryAdderToString(test);
	printf("%s\n", output);
	free(output);

	rippleCarryAdderClear(test);
	rippleCarryAdderSetRegisters(test, 0X0, 0X0);
	rippleCarryAdderAdd(test);
	output = rippleCarryAdderToString(test);
	printf("%s\n", output);
	free(output);

	rippleCarryAdderClear(test);
	rippleCarryAdderSetRegisters(test, 0XFFFc, 0X01);
	rippleCarryAdderAdd(test);
	output = rippleCarryAdderToString(test);
	printf("%s\n", output);
	free(output);

	printf("\n------------Testing Get Result Function-----------\n");
	printf("Result of last operation = 0x%04X", rippleCarryAdderGetResult(test, &error)); 

	rippleCarryAdderDestructor(test);

	return NO_ERROR;
}
*/
