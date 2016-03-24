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

int main()
{	
	//Initial
	memset(iMemory,0,5000);
	memset(dMemory,0,5000);
	memset(reg,0,100);
	FILE *iimage;
	FILE *dimage;
	//Read File
	iimage=fopen("iimage.bin","rb");
	dimage=fopen("dimage.bin","rb");
	writeSnapshot=fopen("snapshot,rpt","w");
	writeError=fopen("error_dump.rpt","w");
	fread(&pc,sizeof(int),1,iimage);
	pc=toBidEndian(pc);
	fread(&iNum,sizeof(int),1,iimage);
	iNum=toBigEndian(iNum);
	iCycle=pc;
	i=pc;
	num=0;
	while(num!=iNum){
		fread(&iMemory[iCycle],sizeof(int),1,iimage);
		iCycle=iCycle+4;
		num++;
	}
	fread(&reg[29],sizeof(int),1,dimage);
	reg[29]=toBidEndian(reg[29]);
	sp=reg[29];
	fread(&dNum,sizeof(int),1,dimage);
	dNum=toBigEndian(dNum);
	while(dCycle!=dNum){
		fread(&dMemory[dCycle],sizeof(int),dimage);
		dCycle++;
	}
	fclose(iimage);
	fclose(dimage);
	//Print Register	
	printRegister();
	for(i=pc;i<iCycle;i+=4){
		iMemory[i]=toBigEndian(iMemory[i]);
	}
	for(i=0;i<dCycle;i++){
		dMemory[i]=toBigEndian(dMemory[i]);
	}
	for(i=pc;i<iCycle;){
		cycle++;
		opcode=iMemory[i]>>26;
		funct=(iMemory[i]<<26)>>26;
		rs=(iMemory[i]<<6)>>27;
		rt=(iMemory[i]<<11)>>27;
		rd=(iMemory[i]<<16)>>27;
		Cshamt=(iMemory[i]<<21)>>27;
		Cimmediate=((iMemory[i]<<16)>>16);
		CimmediateUnisgned=Cimmediate&0x0000FFFF;
		Caddress=(iMemory[i]<<6)>>6;
		i = i+4;
		if(opcode==0x00){
			if(funct==0x20)add();
			else if(funct==0x21)addu();
			else if(funct==0x22)sub();
			else if(funct==0x24)and();
			else if(funct==0x25)or();
			else if(funct==0x26)xor();
			else if(funct==0x27)nor();
			else if(funct==0x28)nand();
			else if(funct==0x2A)slt();
			else if(funct==0x00)sll();
			else if(funct==0x02)srl();
			else if(funct==0x03)sra();
			else if(funct==0x08)jr();
		}
		else if(opcode==0x08)addi();
		else if(opcode==0x09)addiu();
		else if(opcode==0x23)lw();
		else if(opcode==0x21)lh();
		else if(opcode==0x25)lhu();
		else if(opcode==0x20)lb();
		else if(opcode==0x24)lbu();
		else if(opcode==0x2B)sw();
		else if(opcode==0x29)sh();
		else if(opcode==0x28)sb();
		else if(opcode==0x0F)lui();
		else if(opcode==0x0C)andi();
		else if(opcode==0x0D)ori();
		else if(opcode==0x0E)nori();
		else if(opcode==0x0A)slti();
		else if(opcode==0x04)beq();
		else if(opcode==0x05)bne();
		else if(opcode==0x07)bgtz();
		else if(opcode==0x02)j();
		else if(opcode==0x03)jal();
		else if(opcode==0x3F)break;
		if(halt==1)break;
		//Print Register
		printRegister();
	}
	fclose(writeSnapShot);
	fclose(writeError);



}
int toBigEndian(unsigned int K)
{
	a=K>>24;
	b=((k<<8)>>24)<<8;
	c=((k>>8)<<24)>>8;
	d=k<<24;
	k=a+b+c+d;
	return k;
}
void add()
{
	if(rd==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
	}
	int regTmp=reg[rs]+reg[rt];
	int regTmp_tmp=regTmp>>31;
	int rsTmp=reg[rs]>>31;
	int rtTmp=reg[rt]>>31;
	if((rsTmp==rtTmp)&&(regTmp_tmp!=reTmp)){
		fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
	}
	reg[rd]=regTmp;
	if(rd==0){
		reg[rd]=0;
		return;
	}

}
void addiu(){
	if(rd==0){
		fprintf(writeError, "In cycle %d: Write &0 Error\n", cycle);
	}
}


