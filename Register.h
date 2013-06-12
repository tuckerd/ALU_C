/*
* Author: Danielle Tucker
* TCSS 371
* Date 10 November 2012
* Project 3 - Ripple Carry Adder Simulation
* RegisterSet.h - includes, typdefs, and prototypes needed for simulating a register
*/

#ifndef REGISTER_H
#define REGISTER_H

#include "bit_def.h"

#define REGISTER_BIT_SIZE 16
#define NUM_OF_REGISTERS 8

//Register ADT/Class
/**
* Used to simulate a 16 bit register
*/
typedef unsigned short Register;

//Functions (operations on a register)
/**
*  Register initialize();
*  Returns a Register with bits set in register to random value.
*/
Register initialize();

/**
* int set_register(Register* this, unsigned short value);
* Sets the register to a 16 bit value.
* Returns an error if anything went wrong.
*/
int set_register(Register* this, unsigned short value);

/**
* Register get_register(Register this);
* Gets the value of the register.
*/
Register get_register(Register this);

/**
* bit get_bit(Register this, int bit_num, int * error);
* Gets the value of an individual bit (bit_num) in a Register.
* Error is set if bit_n is out of bounds (0-15 inclusive).
*/
bit get_bit(Register this, int bit_num, int * error);

/**
* int set_bit(Register* this, int bit_num);
* Sets (changes to 1) the bit in a register specified by bit_num.
* Error is set if bit_n is out of bounds (0-15 inclusive).*/
int set_bit(Register* this, int bit_num);

/**
* int clear_bit(Register* this, int bit_num);
* Clears (changes to 0) the bit in a register specified by bit_num.
* Error is set if bit_n is out of bounds (0-15 inclusive).*/
int clear_bit(Register* this, int bit_num);


//RegisterSet ADT/Class
/**
* Represents a group of 8 registers in a machine.
*/
typedef Register RegisterSet[8];

//Functions (operations on a register set)
/**
* RegisterSet* registerSetInitialize();
* Creates a RegisterSet, initilizes all of the values to a random value, and returns pointer to that array.
*/
//RegisterSet* registerSetInitialize();
int registerSetInitialize(Register* the_registers);

/**
* int setRegisterNum(RegisterSet* this, int index, unsigned short value);
* Sets the value of register number indicated by the index to value.
* Value will be ensured to be a 16 bit number, all bits above 15 will be cleared.
* Error is set if index is out of bounds (0-15 inclusive).
*/
int setRegisterNum(Register* this, int index, unsigned short value);

/**
* Register getRegisterNum(RegisterSet* this, int index);
* Gets the value of the register indicated by index.
*/
Register getRegisterNum(RegisterSet* this, int index);

#endif //#ifndef REGISTER_H
