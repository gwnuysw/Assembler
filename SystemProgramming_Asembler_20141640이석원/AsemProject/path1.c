# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "readline.h"
# include "asembler.h"
char Label[10], Opcode[10], Operand[20];
int programLength;

struct symboltable SYMTAB[20];
struct operationtable OPTAB[42] = {{"ADD", 0x18},{"ADDF", 0x58},{"AND", 0x40},{"COMP", 0x28},
				{"COMPF", 0x88},{"DIV", 0x24},{"DIVF", 0x64},{"J",0x3C},
				{"JEQ",0x30},{"JGT",0x34},{"JLT", 0x34},{"JSUB",0x48},
				{"LDA",0x00},{"LDB",0x68},{"LDCH",0x50},{"LDF",0x70},
				{"LDL",0x08},{"LDS",0x6C},{"LDT",0x74},{"LDX",0x04},
				{"LPS",0xD0},{"MUL",0x20},{"MULF",0x60},{"OR",0x44},
				{"RD",0xD8},{"RSUB",0x4C},{"SSK",0xEC},{"STA",0x0C},
				{"STB",0x78},{"STCH",0x54},{"STF",0x80},{"STI",0xD4},
				{"STL",0x14},{"STS",0x7C},{"STSW",0xE8},{"STT",0x84},
				{"STX",0x10},{"SUB",0x1C},{"SUBF",0x5C},{"TD",0xE0},
				{"TIX",0x2C},{"WD",0xDC}};
void path1()
{
	FILE* source = fopen("asemfile","r");
	if(source == NULL)
	{
		fprintf(stderr,"file open error \n");
		exit(1);
	}
	char* pEnd;
	int NumofColum;
	int StartingAdres;
	int LOCCTR; 
	int i, k;
	for(k = 0; k < 20; k++)
	{
		SYMTAB[k].LOCCTR = -1;	
	}
	for(k = 0; k < 42; k++)
	{
		printf("OPTAB[%d] : %s %02X\n",k,OPTAB[k].Operator, OPTAB[k].code);
	}
				
	NumofColum = readline(source);

	while(NumofColum == 0)
	{
		NumofColum = readline(source);
	}
	if(!strcmp(Opcode, "START"))
	{
		StartingAdres = strtol(Operand, &pEnd, 16);
		LOCCTR = StartingAdres;
		
		NumofColum = readline(source);
		while(NumofColum == 0)
		{
			NumofColum = readline(source);
		}
	}
	else
	{
		StartingAdres = 0;
		LOCCTR = 0;
	}
	
	while(strcmp(Opcode,"END"))
	{
		if(NumofColum != 0)
		{
			if(Label[0] != '\t')
			{
				for(k = 0; k < 20; k++)
				{
					if(SYMTAB[k].LOCCTR == -1)
					{
						strcpy(SYMTAB[k].LABEL, Label);
						SYMTAB[k].LOCCTR = LOCCTR;
						break;
					}
					else if(!strcmp(SYMTAB[k].LABEL, Label))
					{
						fprintf(stderr,"duplicate symbol");
						exit(1);
					}
				}
			}
			
			//search OPTAB for OPCODE
			int searchopflag = 0;
		
			for(k = 0; k < 42; k++)
			{
				
				if(!strcmp(Opcode, OPTAB[k].Operator))
				{
					
					searchopflag = 1;
					break;
				}
			}
			if(searchopflag)
			{
				printf("present : %s %s LOCCTR : %X\n",Opcode,OPTAB[k].Operator, LOCCTR);
				LOCCTR += 3;
			}
			else if(!strcmp(Opcode, "WORD"))
			{
				printf("WORD present : %s LOCCTR : %X\n",Opcode,LOCCTR);
				LOCCTR += 3;
			}
			else if(!strcmp(Opcode, "RESW"))
			{
				printf("RESW %d LOCCTR : %X\n",atoi(Operand),LOCCTR);
				LOCCTR += (3 * atoi(Operand));
			}
			
			else if(!strcmp(Opcode, "RESB"))
			{
				int oper = atoi(Operand);
				LOCCTR += oper;
				printf("RESB %d LOCCTR : %X\n",oper, LOCCTR);
			}	
			else if(!strcmp(Opcode, "BYTE"))
			{
				int length;
				if(Operand[0] == 'C')
				{
					length = strlen(Operand)-3;
				}
				else if(Operand[0] == 'X')
				{
					length = (strlen(Operand)-3)/2;
				}
				LOCCTR += length;
			}
			else
			{
				fprintf(stderr,"invalid operation code");
				exit(1);
			}
			
		}
		NumofColum = readline(source);
		while(NumofColum == 0)
		{
			NumofColum = readline(source);
		}
	}
	programLength = LOCCTR - StartingAdres;
	
	for(k = 0; k < 20; k++)
	{	
		printf("Talbe %d \nLabel : %s location : %X\n", k, SYMTAB[k].LABEL,SYMTAB[k].LOCCTR);
	}
	printf("length : %X\n", programLength);
	if(fclose(source) != 0)
	{
		
		fprintf(stderr,"file close error \n");
		exit(1);
	}
}
