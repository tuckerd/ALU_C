/*
* Author: Dr. Mobus
* TCSS 371
* Date 7 October 2012
* Assignment 2 Simulating Logic Gates
* logic_gate.c simulates a variety of logical gates
*/

#include <stdio.h>
#include "bit_def.h"
#include "logic_gate.h"
//Needs Object File From: bit_man.c

/*
* bit not(bit);
* Returns the logical NOT of the bit provided.
*/
bit not(bit a)
{
    bit r;

    a = maskBit(a);    // make sure no spurious bits get by!
    r = maskBit(~a);

    return r;
}


/*
* bit and(bit, bit);
* Takes two bits and returns the logical AND of the bits. 
*/
bit and(bit a, bit b) {
    bit r;

    a = maskBit(a);    // make sure no spurious bits get by!
    b = maskBit(b);
    r = a & b & 0x01;

    return r;
}

/*
* bit or(bit, bit);
* Takes two bits and returns the logical OR of the bits. 
*/
bit or(bit a, bit b) {
    bit r;

    a = maskBit(a);    // make sure no spurious bits get by!
    b = maskBit(b);
    r = maskBit(a | b);

    return r;
}

/*
* bit xor(bit, bit);
* Takes two bits and returns the logical EXCLUSIVE OR of the bits
*/
bit xor(bit a, bit b) 
{
    bit r;

    a = maskBit(a);    // make sure no spurious bits get by!
    b = maskBit(b);
    r = maskBit(a ^ b);

    return r;
}

/*
* bit nand(bit, bit);
* Takes two bits and returns the logical NOT AND of the bits
*/
bit nand(bit a, bit b) 
{
    bit r;

    a = maskBit(a);    // make sure no spurious bits get by!
    b = maskBit(b);
    r = maskBit(not(and(a, b)));

    return r;
}

/*
* bit nor(bit, bit);
* Takes two bits and returns the logical NOT OR of the bits
*/
bit nor(bit a, bit b) {
    bit r;

    a = maskBit(a);    // make sure no spurious bits get by!
    b = maskBit(b);
    r = maskBit(not(or(a , b)));

    return r;
}


// test driver code for AND. This can be expanded to complete this assignment
// Remember to comment this section out when compiling to an object file.
/*
int main(void) {
    bit a;
    a = 0x01; //Bit on
    
	bit b;
    b = 0x00; //Bit off

	printf("\nTESTING NOT GATE\n");
    printf("NOT %d = %d\n",b, not(b));
    printf("NOT %d = %d\n",a, not(a));

	printf("\nTESTING AND GATE\n");
    printf("%d AND %d = %d\n",b, b, and(b, b));
    printf("%d AND %d = %d\n",b, a, and(b, a));
    printf("%d AND %d = %d\n",a, b, and(a, b));
    printf("%d AND %d = %d\n",a, a, and(a, a));

	printf("\nTESTING OR GATE\n");
    printf("%d OR %d = %d\n",b, b, or(b, b));
    printf("%d OR %d = %d\n",b, a, or(b, a));
    printf("%d OR %d = %d\n",a, b, or(a, b));
    printf("%d OR %d = %d\n",a, a, or(a, a));

	printf("\nTESTING XOR GATE\n");
    printf("%d XOR %d = %d\n",b, b, xor(b, b));
    printf("%d XOR %d = %d\n",b, a, xor(b, a));
    printf("%d XOR %d = %d\n",a, b, xor(a, b));
    printf("%d XOR %d = %d\n",a, a, xor(a, a));

	printf("\nTESTING NAND GATE\n");
    printf("%d NAND %d = %d\n",b, b, nand(b, b));
    printf("%d NAND %d = %d\n",b, a, nand(b, a));
    printf("%d NAND %d = %d\n",a, b, nand(a, b));
    printf("%d NAND %d = %d\n",a, a, nand(a, a));

	printf("\nTESTING NOR GATE\n");
    printf("%d NOR %d = %d\n",b, b, nor(b, b));
    printf("%d NOR %d = %d\n",b, a, nor(b, a));
    printf("%d NOR %d = %d\n",a, b, nor(a, b));
    printf("%d NOR %d = %d\n",a, a, nor(a, a));
	}
*/
