#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *writeSnapshot;
FILE *writeError;
void add();
void addu();
void sub();
void and();
void or();
void xor();
void nor();
void nand();
void slt();
void sll();
void srl();
void sra();
void jr();
void addi();
void addiu();
void lw();
void lh();
void lhu();
void lb();
void lbu();
void sw();
void sh();
void sb();
void lui();
void andi();
void ori();
void nori();
void slti();
void beq();
void bne();
void bgtz();
void j();
void jal();
void printRegister();
int toBigEndian(unsigned int);
unsigned int imemory[5000];
unsigned int carryAddress;
unsigned int temp;
int reg[100], dmemory[5000], num;
int i = 0;
int l, k, halt = 0, tmp, tmpSigned, a, b, c, d, pc, sp, iNum, dNum, opcode;
int funct, rs, rt, rd, iCycle = 0, dCycle = 0, cycle = 0, Cshamt, CimmediateUnsigned;
short Cimmediate;

int toBigEndian(unsigned int K)
{
	a = K >> 24;
	b = (( k << 8 ) >> 24) << 8;

}
