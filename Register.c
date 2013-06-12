/*
* Author: Danielle Tucker
* TCSS 371
* Date 10 November 2012
* Project 3 - Ripple Carry Adder Simulation
* RegisterSet.c - includes, typdefs, and prototypes needed for simulating a register
*/

#include <stdlib.h>
#include <stdio.h> //only needed for testing in main()
#include <time.h>
#include "Register.h"
#include "errors.h"

//requires object file from bit_man.c

//Register ADT/Class

//Functions (operations on a register)
/**
*  Register initialize();
*  Returns a Register with bits set in register to random value.
*/
Register initialize()
{
	Register value = rand() * rand();
	value &= 0x0FFFF; 
	return value;
}

/**
* int set_register(Register* this, unsigned short value);
* Sets the register to a 16 bit value.
* Returns an error if anything went wrong.
*/
int set_register(Register* this, unsigned short value)
{
	*this = value & 0x0FFFF;
	return NO_ERROR;
}

/**
* Register get_register(Register this);
* Gets the value of the register.
*/
Register get_register(Register this)
{
	return this;
}

/**
* bit get_bit(Register this, int bit_num, int * error);
* Gets the value of an individual bit (bit_num) in a Register.
* Error is set if bit_n is out of bounds (0-15 inclusive).
*/
bit get_bit(Register this, int bit_num, int * error)
{
	if(bit_num >= REGISTER_BIT_SIZE || bit_num < 0) 
	{
		*error = INDEX_OUT_OF_BOUNDS_ERROR;
		return 0;
	}

	return(this >> bit_num)& 0X01;
}

/**
* int set_bit(Register* this, int bit_num);
* Sets (changes to 1) the bit in a register specified by bit_num.
* Error is set if bit_n is out of bounds (0-15 inclusive).*/
int set_bit(Register* this, int bit_num)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}
	if(bit_num >= REGISTER_BIT_SIZE || bit_num < 0) 
		{return INDEX_OUT_OF_BOUNDS_ERROR;}

	*this = *this | (1 << bit_num);
	return NO_ERROR;
}

/**
* int clear_bit(Register* this, int bit_num);
* Clears (changes to 0) the bit in a register specified by bit_num.
* Error is set if bit_n is out of bounds (0-15 inclusive).*/
int clear_bit(Register* this, int bit_num)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}
	if(bit_num >= REGISTER_BIT_SIZE || bit_num < 0) 
		{return INDEX_OUT_OF_BOUNDS_ERROR;}

	*this = *this & ~(1 << bit_num);
	return NO_ERROR;	
}


//RegisterSet ADT/Class

//Functions (operations on a register set)
/**
* RegisterSet* registerSetInitialize();
* Intilizes all of the values in the registerset (which is assumed to be Register[8]
* to a random value, and returns pointer to that array.
*/
int registerSetInitialize(Register* the_registers)
{
	int i;
	for (i = 0; i < NUM_OF_REGISTERS; i++)
	{
		the_registers[i] = initialize();
	}
	return NO_ERROR;
}

/**
* int setRegisterNum(RegisterSet* this, int index, unsigned short value);
* Sets the value of register number indicated by the index to value.
* Value will be ensured to be a 16 bit number, all bits above 15 will be cleared.
* Error is set if index is out of bounds (0-15 inclusive).
*/
int setRegisterNum(Register* this, int index, unsigned short value)
{
	if(this == NULL)	{return NULL_PTR_ERROR;}
	if(index >= NUM_OF_REGISTERS || index < 0) 
		{return INDEX_OUT_OF_BOUNDS_ERROR;}
	this[index] = value & 0x0FFFF;
}

/**
* Register getRegisterNum(RegisterSet* this, int index);
* Gets the value of the register indicated by index.
*/
Register getRegisterNum(RegisterSet* this, int index)
{
	return  get_register(*this[index]);
}

/*
int main()
{
	int error = 0;
	Register reg1 = initialize();
	Register reg2 = initialize();
	printf("Register1: %04x\n", reg1);
	printf("Register2: %04x\n", reg2);
	
	set_register(&reg1, 0x4561);
	printf("Register1: %04x\n", get_register(reg1));

	set_register(&reg2, 0x12d4);
	printf("Register2: %04x\n", get_register(reg2));

	printf("\nRegister1 bit 0: %d\n", get_bit(reg1, 0, &error));
	printf("Register1 bit 1: %d\n", get_bit(reg1, 1, &error));
	printf("Register1 bit 2: %d\n", get_bit(reg1, 2, &error));
	printf("Register1 bit 3: %d\n", get_bit(reg1, 3, &error));
	printf("Register1 bit 4: %d\n", get_bit(reg1, 4, &error));
	printf("Register1 bit 5: %d\n", get_bit(reg1, 5, &error));

	set_bit(&reg1, 1);
	printf("\nAfter Set Bit 1 Register1: %04x\n", reg1);
	printf("\nRegister1 bit 0: %d\n", get_bit(reg1, 0, &error));
	printf("Register1 bit 1: %d\n", get_bit(reg1, 1, &error));
	printf("Register1 bit 2: %d\n", get_bit(reg1, 2, &error));
	clear_bit(&reg1, 1);
	printf("\nAfter Clear Bit 1 Register1: %04x\n", reg1);
	printf("\nRegister1 bit 0: %d\n", get_bit(reg1, 0, &error));
	printf("Register1 bit 1: %d\n", get_bit(reg1, 1, &error));
	printf("Register1 bit 2: %d\n", get_bit(reg1, 2, &error));

	//RegisterSet ADT/Class
	printf("\nTESTING REGISTERSET\n");
	RegisterSet* reg_set = registerSetInitialize();
	int i = 0;
	for(i = 0; i < 8; i++)
	{
		printf("Register %i: %04x\n", i, getRegisterNum(reg_set, i));
	}

	printf("\nSETTING REGISTER 0 to be 1234 and 5 to be e42f\n");
	setRegisterNum(reg_set, 0, 0x1234);
	setRegisterNum(reg_set, 5, 0xe42f);
	for(i = 0; i < 8; i++)
	{
		printf("Register %i: %04x\n", i, getRegisterNum(reg_set, i));
	}
	
	return NO_ERROR;
}
*/


