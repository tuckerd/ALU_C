/*
* Author: Danielle Tucker
* TCSS 371
* Date 10 November 2012
* Project 3 - Ripple Carry Adder Simulation
* ALUSimulator.h - includes, typdefs, and prototypes 
* needed for the user interface for the ALU.
*/
//ALU ADT/Class

#ifndef ALU_SIMULATOR_H
#define ALU_SIMULATOR_H

#include "bit_def.h"
#include "Register.h"
#include "RippleCarryAdder.h"

//Helper Function Prototypes
/**
* getRegisterInputs(Register* my_registers)
* The user is prompted to initialize the registers up to a 
* user specified max or 8 whichever is less.
*/
getRegisterInputs(Register* my_registers);

/**
* int getOperation()
* The user is prompted (by console) of their choice of valid operations and the
* choice is returned.  Primitive error checking is performed (1<=operation<=6)
*/
int getOperation();

/**
* getOperands(ALU* alu, Register* my_registers, 
*			int* source1, int* source2, int* operation, int* destination)
* Using console prompts, the inputs, operations, and destination register are determined.
* The register and alu are seeded with the appropiate values for the next phase in the calculation.
* Primitive error checking is performed on the register number choosen.
*/
getOperands(ALU* alu, Register* my_registers, 
			int* source1, int* source2, int* operation, int* destination);

/**
* Register performOperation(ALU* alu, int* source1, int* source2, int* operation, int* destination)
* Using the provided ALU which assumes have been set up with the inputs, the operation
* is performed and then the result is returned.  Note, the provided ALU's flags will 
* be set.
*/
Register performOperation(ALU* alu, int* source1, int* source2, int* operation, int* destination);

/**
* reportFlags(ALU* alu);
* Reports to the console the state of the flags in the ALU in human readable form. 
*/
reportFlags(ALU* alu);

#endif //#ifndef ALU_SIMULATOR_H