/*
* Author: Danielle Tucker
* TCSS 371
* Date 13 October 2012
* Project 2 - Ripple Carry Adder Simulation
* FullAdder.c simulates a Full Adder for Binary Addition
*/

#include <stdlib.h>
#include <stdio.h> //only needed for testing in main()
#include "FullAdder.h"
#include "errors.h"

//Requires the following object files to be chainloaded
// logic_gate.c, bit_man.c

//Function Prototypes for Helper Methods
bit andThreeInputs(bit a, bit b, bit c);
bit orFourInputs (bit a, bit b, bit c, bit d);

//Constructors and CleanUp
/**
* FullAdderPtr fullAdderConstructor()
* Allocates memory and initializes all values in this struct to 0;
* Returns a pointer to this struct.
*/
FullAdderPtr fullAdderConstructor()
{
	FullAdderPtr adder = (FullAdderPtr) malloc (sizeof(FullAdder));
	fullAdderClear(adder);
	return adder;
}

/**
* int fullAdderClear(FullAdderPtr this)
* Clears (resets) all of the values in the Full Adder to 0
* Returns an error if there was a problem.
*/
int fullAdderClear(FullAdderPtr this)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}

	this->a = 0;
	this->b = 0;
	this->c_in = 0;
	this->r = 0;
	this->c_out = 0;
	return NO_ERROR;
}

/**
* int fullAdderDestructor (FullAdderPtr this) 
* Frees all memory associated with this struct.
*/
int fullAdderDestructor (FullAdderPtr this) 
{
	if(this == NULL)	{return NULL_PTR_ERROR;}

	free(this);
	return NO_ERROR;
}

//Operations
/**
* bit fullAdder (bit a, bit b, bit c_in, bit * c_out)
* Returns the value of the fullAdder calculation.
* Note: the result value is not set in this function.
* See fullAdderPtrCompute()
* This function should not be used outside this program.
*/
bit fullAdder (bit a, bit b, bit c_in, bit * c_out)
{
	//gate0 ~A and ~B and ~C (unused in adder) 
	//gate1 ~A and ~B and C
	bit gate1 = andThreeInputs(not(a), not(b), c_in);
	//gate2 ~A and B and ~C
	bit gate2 = andThreeInputs(not(a), b, not(c_in));
	//gate3 ~A and B and C
	bit gate3 = andThreeInputs(not(a), b, c_in);
	//gate4 A and ~B and ~C
	bit gate4 = andThreeInputs(a, not(b), not(c_in));
	//gate5 A and ~B and C
	bit gate5 = andThreeInputs(a, not(b), c_in);
	//gate6 A and B and ~C
	bit gate6 = andThreeInputs(a, b, not(c_in));
	//gate7 A and B and C
	bit gate7 = andThreeInputs(a, b, c_in);

	//carry out from or of gate 3, 5, 6, 7
	*c_out = orFourInputs(gate3, gate5, gate6, gate7);
	
	//r from or of gate 1, 2, 4, 7)
	return orFourInputs(gate1, gate2, gate4, gate7);
}

/**
* int fullAdderPtrCompute(FullAdderPtr this)
* Computes the result of the fullAdder calculation and sets the result bit
* Returns an error if a problem occured.
*/
int fullAdderPtrCompute(FullAdderPtr this)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}

	setResultBit(this, fullAdder(this->a, this->b, this->c_in, &this->c_out));
	return NO_ERROR;
}

//Helper Methods
/**
* bit andThreeInputs (bit a, bit b, bit c)
* Helper method used to simplify logic in other functions.
* Returns the logical AND of the three inputs.
*/
bit andThreeInputs (bit a, bit b, bit c)
{
	return and(and(a, b), c);
}

/**
* bit orFourInputs (bit a, bit b, bit c, bit d)
* Helper method to simplify logic in other functions.
* Used to logical OR four inputs together.
* Returns the result of the logical or.
*/
bit orFourInputs (bit a, bit b, bit c, bit d)
{
	return or(or(a, b), or(c, d));
}

//Getters
/**
* bit getABit(FullAdderPtr this)
* Returns the value of the A bit in this Full Adder.
*/
bit getABit(FullAdderPtr this)
{
	return this->a;
}

/**
* bit getBBit(FullAdderPtr this)
* Returns the value of the B bit in this Full Adder.
*/
bit getBBit(FullAdderPtr this)
{
	return this->b;
}

/**
* bit getCarryInBit(FullAdderPtr this)
* Gets the current carry in bit value.
*/
bit getCarryInBit(FullAdderPtr this)
{
	return this->c_in;
}

/**
* bit getCarryOutBit(FullAdderPtr this)
* Gets the current carry out bit value.
*/
bit getCarryOutBit(FullAdderPtr this)
{
	return this->c_out;
}

/**
* bit * getCarryOutBitPtr(FullAdderPtr this)
* Provides a pointer to the carry out bit for use in
* a ripple carry adder.
*/
bit * getCarryOutBitPtr(FullAdderPtr this)
{
	return &this->r;
}

/**
* bit getResultBit(FullAdderPtr this)
* Returns the current result bit that is in the full adder.
* Make sure you perform the add before checking this to get result
* or it might be set to the previous result.
*/
bit getResultBit(FullAdderPtr this)
{
	return this->r;
}

//Setters
/**
* int setInputBits(FullAdderPtr this, bit a, bit b, bit c_in)
* Sets both the a, b, and carry in bit of the full adder.
*/
int setInputBits(FullAdderPtr this, bit a, bit b, bit c_in)
{
	if (this == NULL)	{return NULL_PTR_ERROR;}
	this->a = a;
	this->b = b;
	this->c_in = c_in;
	
	return NO_ERROR;
}

/**
* int setABit(FullAdderPtr this, bit a)
* Sets the A bit input to this Full Adder
*/
int setABit(FullAdderPtr this, bit a)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}

	this->a = a;
	return NO_ERROR;
}

/**
* int setBBit(FullAdderPtr this, bit b)
* Sets the B bit input to this Full Adder
*/
int setBBit(FullAdderPtr this, bit b)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}

	this->b = b;
	return NO_ERROR;
}

/**
* int setCarryInBit(FullAdderPtr this, bit c_in)
* Sets the CarryIn bit in the struct. 1 if there was carry in, else 0
*/
int setCarryInBit(FullAdderPtr this, bit c_in)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}

	this->c_in = c_in;
	return NO_ERROR;
}

/**
* int setCarryOutBit(FullAdderPtr this, bit c_out)
* Sets the CarryOut bit in the struct. 1 if there was carry out, else 0
* Should not be used outside this program.
*/
int setCarryOutBit(FullAdderPtr this, bit c_out)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}

	this->c_out = c_out;
	return NO_ERROR;
}

/**
* int setResultBit(FullAdderPtr this, bit r)
* Sets the Result Bit in this struct.  Should not be used outside
* this program.  Returns a result if there was an error.
*/
int setResultBit(FullAdderPtr this, bit r)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}

	this->r = r;
	return NO_ERROR;
}

//Reporting State
/**
* char * fullAdderToString(FullAdderPtr this)
* Provides a string representation of the state of all of the values in the FullAdder struct.
*/
char * fullAdderToString(FullAdderPtr this)
{
	//reserving space for the string
	char * retString = (char *) malloc(sizeof(char)*128 + sizeof(*this));
	sprintf(retString, "FullAdder@%p: a = %d, b = %d, c_in = %d r = %d, c_out = %d" , 
						this, this->a, this->b,	this->c_in, this->r, this->c_out);
	return retString;
	//need to destroy the string after you call this function!
}

//Testing driver code for FullAdder
//Remember to comment this section out when compiling to an object file.
/*
int main(void) 
{
    bit on = 0x01;    
	bit off = 0x00;
	char * output;
	printf("------Testing Constructor and ToString------\n");
	FullAdderPtr test = fullAdderConstructor();
	output = fullAdderToString(test);
	printf("%s \n", output);

	printf("\n------------Testing Setting Bits------------\n");	
	setABit(test, on);
	setBBit(test, on);
	setCarryInBit(test, on);
	setResultBit(test, on);
	setCarryOutBit(test, on);
	output = fullAdderToString(test);
	printf("%s \n", output);

	printf("\n------------Testing Getting Bits------------\n");	
	printf("getABit = %d, getBBit = %d, getCarryIn = %d, getResultBit = %d, getCarryOutBit = %d\n",
		getABit(test),	getBBit(test), getCarryInBit(test), getResultBit(test), getCarryOutBit(test));
	
	//Create truth table for Adder
	printf("\n-------------Testing Full Adder-------------\n");
	int a, b, c_in;
	for(a = 0; a < 2; a++)
	{
		for(b = 0; b <2; b++)
		{
			for(c_in = 0; c_in < 2; c_in++)
			{
				fullAdderClear(test);
				setInputBits(test, a, b, c_in);
				fullAdderPtrCompute(test);
				output = fullAdderToString(test);
				printf("%s \n", output);
			}
		}
	}
	printf("\n-------------Testing Destructor-------------\n");
	int destroy = fullAdderDestructor(test);
	printf("Result: %d  Pointer at: %p\n", destroy, test);  
	output = fullAdderToString(test);
	printf("%s \n", output);
	
	//free the memory from output toString
	free(output);
	
	return NO_ERROR;
}
*/
