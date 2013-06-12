OBJS = bit_man.o logic_gate.o Register.o FullAdder.o RippleCarryAdder.o ALU.o

all: ALUSimulator

ALUSimulator: ALUSimulator.c ALUSimulator.h bit_man.o logic_gate.o Register.o FullAdder.o RippleCarryAdder.o ALU.o
	gcc -g ALUSimulator.c $(OBJS) -o ALUSimulator.exe
#	./ALUSimulator.exe
	
ALU.o : ALU.c ALU.h RippleCarryAdder.o FullAdder.o Register.o logic_gate.o bit_man.o 
	gcc -c ALU.c
	
RippleCarryAdder.o : RippleCarryAdder.c FullAdder.o logic_gate.o bit_man.o RippleCarryAdder.h
	gcc -c RippleCarryAdder.c

FullAdder.o: FullAdder.c logic_gate.o bit_man.o FullAdder.h
	gcc -c FullAdder.c
	
logic_gate.o: logic_gate.c bit_man.o logic_gate.h
	gcc -c logic_gate.c

Register.o: Register.c bit_man.o Register.h
	gcc -c Register.c
	
bit_man.o: bit_man.c bit_def.h
	gcc -c bit_man.c