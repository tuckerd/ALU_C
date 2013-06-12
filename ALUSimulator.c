/*
* Author: Danielle Tucker
* TCSS 371
* Date 10 November 2012
* Project 3 - Ripple Carry Adder Simulation
* ALUSimulator.c - User interface for the use of the ALU and Registers.
*/
#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "ALU.h"
#include "Register.h"

// Requires the following object files
// bit_man.o logic_gate.o Register.o FullAdder.o RippleCarryAdder.o ALU.o

/**
* getRegisterInputs(Register* my_registers)
* The user is prompted to initialize the registers up to a 
* user specified max or 8 whichever is less.
*/
getRegisterInputs(Register* my_registers)
{
	int num_registers = 0;
	
	printf("Input number of registers to initialize (1 up to 8): ");
	scanf("%d", &num_registers);
	if(num_registers < 0) num_registers = 0;
	if(num_registers > 8) num_registers = 8;
	printf("\nInput values as 16 bit hexadecimal numbers, e.g. FA35 (no leading 0x)\n");

	printf("\nRegisters will be loaded in order from R0 to R%d\n", num_registers-1);

	int i = 0;
	int value;
	for(i = 0; i < num_registers; i++)
	{
		printf("Input Register %i: ", i);
		scanf("%x", &value);
		my_registers[i] = value;
	}

}
/**
* int getOperation()
* The user is prompted (by console) of their choice of valid operations and the
* choice is returned.  Primitive error checking is performed (1<=operation<=6)
*/
int getOperation()
{
	int operation = 0;
	printf("\nOperations - 1) ADD, 2) SUB, 3) NEG, 4) NOT, 5) AND, 6) OR\n");
	do
	{
		printf("Input operation: ");
		scanf("%d", &operation);
	}while(operation > 6 || operation < 1);
	return operation;
}

/**
* getOperands(ALU* alu, Register* my_registers, 
*			int* source1, int* source2, int* operation, int* destination)
* Using console prompts, the inputs, operations, and destination register are determined.
* The register and alu are seeded with the appropiate values for the next phase in the calculation.
* Primitive error checking is performed on the register number choosen.
*/
getOperands(ALU* alu, Register* my_registers, 
			int* source1, int* source2, int* operation, int* destination)
{
	printf("\nSpecify registers to operate on\n");
	do
	{
		printf("Source1: ");
		scanf("%d", source1);
	}while (*source1 < 0 || *source1 > 7);

	putOperandA(alu, my_registers[*source1]);
	if (*operation != 4 && *operation != 3)
	{
		do
		{
			printf("Source2: ");
			scanf("%d", source2);
		}while (*source2 < 0 || *source2 > 7);
		putOperandB(alu, my_registers[*source2]);
	}

	do
	{
		printf("Destination: ");
		scanf("%d", destination);
	}while(*destination < 0 || *destination > 7);
}

/**
* Register performOperation(ALU* alu, int* source1, int* source2, int* operation, int* destination)
* Using the provided ALU which assumes have been set up with the inputs, the operation
* is performed and then the result is returned.  Note, the provided ALU's flags will 
* be set.
*/
Register performOperation(ALU* alu, int* source1, int* source2, int* operation, int* destination)
{
	char op_string[8];
	switch(*operation)
	{
		case 1:
			strcpy(op_string, "+");
			printf("\nRegister %d %s Register%d --> Register %d\n", *source1, op_string, *source2, *destination);
			ALUadd(alu);
			break;
		case 2:
			strcpy(op_string, "-");
			printf("\nRegister %d %s Register %d --> Register %d\n", *source1, op_string, *source2, *destination);
			ALUsub(alu);
			break;
		case 3:
			strcpy(op_string, "NEGATE");
			printf("\nRegister %d %s --> Register %d\n", *source1, op_string, *destination);
			ALUneg(alu);
			break;
		case 4:
			strcpy(op_string, "NOT");
			printf("\nRegister %d %s --> Register %d\n", *source1, op_string, *destination);
			ALUnot(alu);
			break;
		case 5:
			strcpy(op_string, "AND");
			printf("\nRegister %d %s Register %d --> Register %d\n", *source1, op_string, *source2, *destination);
			ALUand(alu);
			break;
		case 6:
			strcpy(op_string, "OR");
			printf("\nRegister %d %s Register %d --> Register %d\n", *source1, *op_string, source2, *destination);
			ALUor(alu);
			break;
		default:
			strcpy(op_string, "ERR");
			printf("ERROR in determining Operation Type");
			break;
	}
	
	return getResult(alu);
}

/**
* Reports to the console the state of the flags
*/
reportFlags(ALU* alu)
{
	Register flags = getALUFlags(alu);
	int error = 0;
	bit flag_n = get_bit(flags, 15, &error);
	bit flag_z = get_bit(flags, 14, &error);
	bit flag_c = get_bit(flags, 13, &error);
	bit flag_o = get_bit(flags, 12, &error);
	printf("\nCondition codes: N = %d, Z = %d, C = %d, O = %d\n", flag_n, flag_z, flag_c, flag_o);
}

int main()
{
	Register my_registers[8];
	registerSetInitialize(my_registers);
	ALU* alu = ALUConstructor();
	int source1, source2, operation, destination = 0;
	Register result;

	printf("ALU Simulator, by Danielle Tucker\n\n");

	getRegisterInputs(my_registers);
	operation = getOperation();
	getOperands(alu, my_registers, &source1, &source2, &operation, &destination);
	result = performOperation(alu, &source1, &source2, &operation, &destination);
	
	my_registers[destination] = result;
	printf("Result in Register %d: %04x\n", destination, result);

	reportFlags(alu);

	printf("\nState of Registers\n");
	int i = 0;
	for(i = 0; i < 8; i++)
	{
		printf("Register %i: %04x\n", i, my_registers[i]);
	}
	return NO_ERROR;
}
