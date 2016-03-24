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
int BigEndian(unsigned int);
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
	memset(imemory,0,5000);
	memset(dmemory,0,5000);
	memset(reg,0,100);
	FILE *iimage;
	FILE *dimage;
	//Read File
	iimage=fopen("iimage.bin","rb");
	dimage=fopen("dimage.bin","rb");
	writeSnapshot=fopen("snapshot,rpt","w");
	writeError=fopen("error_dump.rpt","w");
	fread(&pc,sizeof(int),1,iimage);
	pc=BigEndian(pc);
	fread(&iNum,sizeof(int),1,iimage);
	iNum=BigEndian(iNum);
	iCycle=pc;
	i=pc;
	num=0;
	while(num!=iNum){
		fread(&imemory[iCycle],sizeof(int),1,iimage);
		iCycle=iCycle+4;
		num++;
	}
	fread(&reg[29],sizeof(int),1,dimage);
	reg[29]=BigEndian(reg[29]);
	sp=reg[29];
	fread(&dNum,sizeof(int),1,dimage);
	dNum=BigEndian(dNum);
	while(dCycle!=dNum){
		fread(&dmemory[dCycle],sizeof(int),1,dimage);
		dCycle++;
	}
	fclose(iimage);
	fclose(dimage);
	//Print Register
	printRegister();
	for(i=pc;i<iCycle;i+=4){
		imemory[i]=BigEndian(imemory[i]);
	}
	for(i=0;i<dCycle;i++){
		dmemory[i]=BigEndian(dmemory[i]);
	}
	for(i=pc;i<iCycle;){
		cycle++;
		opcode=imemory[i]>>26;
		funct=(imemory[i]<<26)>>26;
		rs=(imemory[i]<<6)>>27;
		rt=(imemory[i]<<11)>>27;
		rd=(imemory[i]<<16)>>27;
		Cshamt=(imemory[i]<<21)>>27;
		Cimmediate=((imemory[i]<<16)>>16);
		CimmediateUnsigned=Cimmediate&0x0000FFFF;
		carryAddress=(imemory[i]<<6)>>6;
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
	fclose(writeSnapshot);
	fclose(writeError);



}
int BigEndian(unsigned int k){
    a=k>>24;
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
	if((rsTmp==rtTmp)&&(regTmp_tmp!=rsTmp)){
		fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
	}
	reg[rd]=regTmp;
	if(rd==0){
		reg[rd]=0;
		return;
	}

}
void addu(){
	if(rd==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
	}
	int regTemp = reg[rs]+reg[rt];
	reg[rd] = regTemp;
	if(rd==0){
		reg[rd]=0;
		return;
	}
}
void sub(){
	if(rd==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
	}
	int regTemp=reg[rs]-reg[rt];
	int regTemp_Temp=regTemp>>31;
	int rsTemp=reg[rs]>>31;
	int rtTemp=(0-reg[rt])>>31;
	if((rsTemp==rtTemp)&&(regTemp_Temp!=rsTemp)){
		fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
	}
	reg[rd]=regTemp;
	if(rd==0){
		reg[rd]=0;
		return;
	}
}
void and(){
	if(rd==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
	}
	reg[rd]=reg[rs]&reg[rt];
}
void or(){
	if(rd==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
		return;
	}
	reg[rd]=reg[rs]|reg[rt];
}
void xor(){
	if(rd==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
		return;
	}
	reg[rd]=reg[rs]^reg[rt];
}
void nor(){
	if(rd==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
		return;
	}
	reg[rd]=~(reg[rs]|reg[rt]);
}
void nand(){
	if(rd==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
		return;
	}
	reg[rd]=~(reg[rs]&reg[rt]);
}
void slt(){
	if(rd==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
		return;
	}
	reg[rd]=(reg[rs]<reg[rt]);
}
void sll(){
	if(rd==0){
		if(!(rt==0&&Cshamt==0)){
			fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
			return;
		}
	}
	reg[rd]=reg[rt]<<Cshamt;
}
void srl(){
	if(rd==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
		return;
	}
	reg[rd]=reg[rt];
	for(l=0;l<Cshamt;l++){
		reg[rd]=(reg[rd]>>1)&0x7FFFFFFF;
	}
}
void sra(){
	if(rd==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
		return;
	}
	reg[rd]=reg[rt]>>Cshamt;
}
void jr(){
	i=reg[rs];
}
void addi(){
	if(rt==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
	}
	int regTemp=reg[rs]+Cimmediate;
	int regTemp_Temp=regTemp>>31;
	int rsTemp=reg[rs]>>31;
	int CTemp=Cimmediate>>15;
	if((rsTemp==CTemp)&&(regTemp_Temp!=rsTemp)){
		fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
	}
	reg[rt]=regTemp;
	if(rt==0){
		reg[rt]=0;
		return;
	}
}
void addiu(){
	if(rt==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
	}
	int regTemp=reg[rs]+Cimmediate;
	int regTemp_Temp=regTemp>>31;
	int rsTemp=reg[rs]>>31;
	int cTemp=Cimmediate>15;

	reg[rt]=regTemp;
	if(rt==0){
		reg[rt]=0;
		return;
	}
}
void lw(){
	if(rt==0){
        	fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
    	}
    	tmp=reg[rs]+Cimmediate;
    	if((reg[rs]>0&&Cimmediate>0&&tmp<0)||(reg[rs]<0&&Cimmediate<0&&tmp>0)){
        	fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
    	}
    	if(tmp<0||(tmp+3<0)||(tmp>1023)||(tmp+3)>1023){
        	fprintf(writeError, "In cycle %d: Address Overflow\n", cycle);
        	halt=1;
    	}
    	if(tmp%4!=0){
        	fprintf(writeError, "In cycle %d: Misalignment Error\n", cycle);
        	halt=1;
    	}
    	if(halt==1)return;
    	reg[rt]=dmemory[tmp/4];
    	if(rt==0){
        	reg[rt]=0;
        return;
    }
}
void lh(){
	if(rt==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
	}
	tmp=reg[rs]+Cimmediate;
	int tmpTemp=tmp>>31;
	int rsTemp=reg[rs]>>31;
	int cTemp=Cimmediate>>15;
	if((rsTemp==cTemp)&&(tmpTemp!=rsTemp)){
		fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
	}
	if(tmp<0||(tmp+1<0)||(tmp>1023)||(tmp+1)>1023){
		fprintf(writeError, "In cycle %d: Address Overflow\n", cycle);
		halt = 1;
	}
	if(tmp%2!=0){
		fprintf(writeError, "In cycle %d: Misalignment Error\n", cycle);
		halt = 1;
	}
	if(halt==1) return;
	if(rt==0){
		reg[rt]=0;
		return;
	}
	if(tmp%4==0)tmpSigned=dmemory[tmp/4]>>16;
	else if(tmp%4==2)tmpSigned=(dmemory[tmp/4]<<16)>>16;
	if(tmpSigned>>15==1)reg[rt]=tmpSigned|0xFFFF0000;
	else reg[rt]=tmpSigned;
}
void lhu(){
	if(rt==0){
		fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
	}
	tmp=reg[rs]+Cimmediate;
    	int tmpTmp=tmp>>31;
    	int rsTmp=reg[rs]>>31;
    	int cTmp=Cimmediate>>15;
    	if((rsTmp==cTmp)&&(tmpTmp!=rsTmp)){
        	fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
    	}
    	if(tmp<0||(tmp+1<0)||(tmp>1023)||(tmp+1)>1023){
        	fprintf(writeError, "In cycle %d: Address Overflow\n", cycle);
        	halt=1;
    	}
    	if(tmp%2!=0){
        	fprintf(writeError, "In cycle %d: Misalignment Error\n", cycle);
        	halt=1;
    	}
    	if(halt==1)return;
    	if(rt==0){
        	reg[rt]=0;
        	return;
    	}
    	temp=dmemory[tmp/4];
    	if(tmp%4==0)temp=temp>>16;
    	else if(tmp%4==2)temp=(temp<<16)>>16;
    	reg[rt]=temp;
}
void lb(){
	if(rt==0){
        	fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
    	}
    	tmp=reg[rs]+Cimmediate;
    	int tmpTmp=tmp>>31;
    	int rsTmp=reg[rs]>>31;
    	int cTmp=Cimmediate>>15;
    	if((rsTmp==cTmp)&&(tmpTmp!=rsTmp)){
        	fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
    	}
    	if(tmp<0||tmp>1023){
        	fprintf(writeError, "In cycle %d: Address Overflow\n", cycle);
        	halt=1;
    	}
    	if(halt==1)return;
    	if(rt==0){
        	reg[rt]=0;
        	return;
    	}
    	if(tmp%4==0)tmpSigned=dmemory[tmp/4]>>24;
    	else if(tmp%4==1)tmpSigned=(dmemory[tmp/4]<<8)>>24;
    	else if(tmp%4==2)tmpSigned=(dmemory[tmp/4]<<16)>>24;
    	else if(tmp%4==3)tmpSigned=(dmemory[tmp/4]<<24)>>24;
    	if(tmpSigned>>7==1)reg[rt]=tmpSigned|0xFFFFFF00;
    	else reg[rt]=tmpSigned;
}
void lbu(){
    	if(rt==0){
        	fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
    	}
    	tmp=reg[rs]+Cimmediate;
    	int tmpTmp=tmp>>31;
    	int rsTmp=reg[rs]>>31;
    	int cTmp=Cimmediate>>15;
    	if((rsTmp==cTmp)&&(tmpTmp!=rsTmp)){
        	fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
    	}
    	if(tmp<0||tmp>1023){
    	    	fprintf(writeError, "In cycle %d: Address Overflow\n", cycle);
        	halt=1;
    	}
    	if(halt==1)return;
    	if(rt==0){
        	reg[rt]=0;
        	return;
    	}
    	temp=dmemory[tmp/4];
    	if(tmp%4==0)temp=temp>>24;
    	else if(tmp%4==1)temp=(temp<<8)>>24;
    	else if(tmp%4==2)temp=(temp<<16)>>24;
    	else if(tmp%4==3)temp=(temp<<24)>>24;
    	reg[rt]=temp;
}
void sw(){
    	tmp=reg[rs]+Cimmediate;
    	int tmpTmp=tmp>>31;
    	int rsTmp=reg[rs]>>31;
    	int cTmp=Cimmediate>>15;
    	if((rsTmp==cTmp)&&(tmpTmp!=rsTmp)){
        	fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
    	}
    	if(tmp<0||(tmp+3<0)||(tmp>1023)||(tmp+3)>1023){
        	fprintf(writeError, "In cycle %d: Address Overflow\n", cycle);
        	halt=1;
    	}
    	if(tmp%4!=0){
        	fprintf(writeError, "In cycle %d: Misalignment Error\n", cycle);
        	halt=1;
    	}
    	if(halt==1)return;
    	dmemory[tmp/4]=reg[rt];
}
void sh(){
    	tmp=reg[rs]+Cimmediate;
    	int tmpTmp=tmp>>31;
    	int rsTmp=reg[rs]>>31;
    	int cTmp=Cimmediate>>15;
    	if((rsTmp==cTmp)&&(tmpTmp!=rsTmp)){
        	fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
    	}
    	if(tmp<0||(tmp+1<0)||(tmp>1023)||(tmp+1)>1023){
        	fprintf(writeError, "In cycle %d: Address Overflow\n", cycle);
        	halt=1;
    	}
    	if(tmp%2!=0){
        	fprintf(writeError, "In cycle %d: Misalignment Error\n", cycle);
        	halt=1;
    	}
    	if(halt==1)return;
    	tmpSigned=reg[rt]&0x0000FFFF;
    	if(tmp%4==0)dmemory[tmp/4]=(dmemory[tmp/4]&0x0000FFFF)+(tmpSigned<<16);
    	else if(tmp%4==2)dmemory[tmp/4]=(dmemory[tmp/4]&0xFFFF0000)+tmpSigned;
}
void sb(){
    	tmp=reg[rs]+Cimmediate;
    	int tmpTmp=tmp>>31;
    	int rsTmp=reg[rs]>>31;
    	int cTmp=Cimmediate>>15;
    	if((rsTmp==cTmp)&&(tmpTmp!=rsTmp)){
        	fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
    	}
    	if(tmp<0||tmp>1023){
        	fprintf(writeError, "In cycle %d: Address Overflow\n", cycle);
        	halt=1;
    	}
    	if(halt==1)return;
    	tmpSigned=reg[rt]&0x000000FF;
    	if(tmp%4==0)dmemory[tmp/4]=(dmemory[tmp/4]&0x00FFFFFF)+(tmpSigned<<24);
    	else if(tmp%4==1)dmemory[tmp/4]=(dmemory[tmp/4]&0xFF00FFFF)+(tmpSigned<<16);
    	else if(tmp%4==2)dmemory[tmp/4]=(dmemory[tmp/4]&0xFFFF00FF)+(tmpSigned<<8);
    	else if(tmp%4==3)dmemory[tmp/4]=(dmemory[tmp/4]&0xFFFFFF00)+tmpSigned;
}
void lui(){
    	if(rt==0){
        	fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
    	}
    	else reg[rt]=(int)(CimmediateUnsigned<<16);
}
void andi(){
    	if(rt==0){
        	fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
    	}
    	else reg[rt]=reg[rs]&CimmediateUnsigned;
}
void ori(){
    	if(rt==0){
        	fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
    	}
    	else reg[rt]=reg[rs]|CimmediateUnsigned;
}
void nori(){
    	if(rt==0){
        	fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
    	}
    	else reg[rt]=~(reg[rs]|CimmediateUnsigned);
}
void slti(){
    	if(rt==0){
        	fprintf(writeError, "In cycle %d: Write $0 Error\n", cycle);
    	}
    	else reg[rt]=(reg[rs]<Cimmediate);
}
void beq(){
    	int Cimmediate4=Cimmediate*4;
    	int pcTmp=i+Cimmediate4;
    	if((Cimmediate>0&&Cimmediate4<=0)||(Cimmediate<0&&Cimmediate4>=0)||(i>0&&Cimmediate4>0&&pcTmp<0)||(i<0&&Cimmediate4<0&&pcTmp>0)){
        	fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
    	}
    	if(reg[rs]==reg[rt])i=pcTmp;
}
void bne(){
    	int Cimmediate4=Cimmediate*4;
    	int pcTmp=i+Cimmediate4;
    	if((Cimmediate>0&&Cimmediate4<=0)||(Cimmediate<0&&Cimmediate4>=0)||(i>0&&Cimmediate4>0&&pcTmp<0)||(i<0&&Cimmediate4<0&&pcTmp>0)){
        	fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
    	}
    	if(reg[rs]!=reg[rt])i=pcTmp;
}
void bgtz(){
    	int Cimmediate4=Cimmediate*4;
    	int pcTmp=i+Cimmediate4;
    	if((Cimmediate>0&&Cimmediate4<=0)||(Cimmediate<0&&Cimmediate4>=0)||(i>0&&Cimmediate4>0&&pcTmp<0)||(i<0&&Cimmediate4<0&&pcTmp>0)){
        	fprintf(writeError, "In cycle %d: Number Overflow\n", cycle);
    	}
    	if(reg[rs]>0)i=pcTmp;
}
void j(){
    	i=((i>>28)<<28)+carryAddress*4;
}
void jal(){
    	reg[31]=i;
    	i=((i>>28)<<28)+carryAddress*4;
}
void printRegister(){
    	fprintf(writeSnapshot, "cycle %d\n", cycle);
    	for(k=0;k<32;k++){
        	fprintf(writeSnapshot, "$%02d: 0x%08X\n",k,reg[k]);
    	}
    	fprintf(writeSnapshot, "PC: 0x%08X\n\n\n", i);
}
