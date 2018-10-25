# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "readline.h"
# include "asembler.h"
# include "charAnalisys.h"

extern int programLength;
extern struct symboltable SYMTAB[20];
extern struct operationtable  OPTAB[42];
extern char Label[10], Opcode[10], Operand[20];

void path2()
{
	FILE* source = fopen("asemfile","r");

	FILE* object = fopen("ObjectProgram","w");

	if((source == NULL) || (object == NULL))
	{
		fprintf(stderr,"file open error \n");
		exit(1);
	}


	int numofcolum;
	int startingadres;
	char listingLine[61];
	char ObjectCode[7];
	char* pEnd;
	int numberTemp;
	int LocCtr;
	int LineStartLocCtr;
	numofcolum = readline(source);
	while(numofcolum == 0)
	{
		numofcolum = readline(source);
	}
	if(!strcmp(Opcode,"START"))
	{
		strcat(listingLine, Label);
		numberTemp = strtol(Operand,&pEnd,16);
		numto(numberTemp, ObjectCode);
		strcat(listingLine, ObjectCode);
		numto(programLength, ObjectCode);
		strcat(listingLine, ObjectCode);
		printf("linstingLine %s\n", listingLine);


		startingadres = numberTemp;
		LocCtr = numberTemp;
		LineStartLocCtr = LocCtr;
		numofcolum = readline(source);
		while(numofcolum == 0)
		{
			numofcolum = readline(source);
		}
	}
	fprintf(object,"H%s\n",listingLine);
	strcpy(listingLine,"");
	printf("reset listingLine %s\n",listingLine);
	while(strcmp(Opcode,"END"))
	{
		int i;
		int Opfound = 0;
		int Symfound = 0;
		char Opvalue[3];
		int Opint;
		char Symvalue[5];
		int Symint;
		strcpy(ObjectCode,"");
		strcpy(Opvalue,"");
		strcpy(Symvalue,"");
		for(i = 0; i < 42; i++)
		{
			if(!strcmp(OPTAB[i].Operator, Opcode))
			{
				Opfound = 1;
				Opint = OPTAB[i].code;
				break;
			}
			
		}	
		if(Opfound == 1)
		{
			if(strcmp(Operand, "\t") != 0)
			{
				printf("befor loop\n");
				char * cutX;
				char Opercopy[20];
				strcpy(Opercopy, Operand);
				if(strchr(Opercopy,',')!=NULL)
				{
					cutX = strtok(Opercopy,",");

					for(i = 0; i < 20; i++)
					{
						if(!strcmp(SYMTAB[i].LABEL, cutX))
						{	
							Symfound = 1;	
							Symint = SYMTAB[i].LOCCTR;
							break;
						}
					}
				}
				else
				{
					for(i = 0; i < 20; i++)
					{
						if(!strcmp(SYMTAB[i].LABEL, Operand))
						{
							Symfound = 1;	
							Symint = SYMTAB[i].LOCCTR;
							break;
						}
					}
				}
				if(Symfound == 1)
				{
					operandto(Symint, Symvalue);
					printf("sym value %s\n", Symvalue);
				}
				else
				{
					fprintf(stderr,"Operand error \n");
					exit(1);
				}
			}

			else
			{
				operandto(0,Symvalue);
				printf("operand is empty\n");
			}
			opcodeto(Opint, Opvalue);
			strcat(ObjectCode,Opvalue);
			strcat(ObjectCode,Symvalue);
			printf("this is Objectcode %s\n", ObjectCode);
		}
		else if(!strcmp(Opcode,"BYTE"))
		{
			int convertnum = 0;
			convertnum = HexToInt(Operand,strlen(Operand));
			printf("convert number is %x \n", convertnum);
			if(convertnum > 255)
			{
				numto(convertnum, ObjectCode);
				printf("over 255 is it X,C %s\n", ObjectCode);
			}
			else
			{
				opcodeto(convertnum,Opvalue);
				strcpy(ObjectCode, Opvalue);
				printf("under 255 is it X,c %s\n", ObjectCode);
			}
		}
		else if(!strcmp(Opcode,"WORD"))
		{
			int temp;
			temp = atoi(Operand);
			numto(temp,ObjectCode);
		}
		else if(!strcmp(Opcode,"RESB"))
		{
			LocCtr = LocCtr + atoi(Operand);
		}
		else if(!strcmp(Opcode, "RESW"))
		{
			LocCtr = LocCtr + (atoi(Operand) * 3);
		}
		if(strlen(listingLine) > 55)
		{
			printf("this is 60 over listring line **********************\n");
			int textLength = strlen(listingLine)/2;
			printf("Length of listingLine %02X\n", textLength);
			fprintf(object,"T%06X%02X%s\n",LineStartLocCtr,textLength,listingLine);
			LocCtr += textLength;
			LineStartLocCtr = LocCtr;
			strcpy(listingLine,"");
		}
		strcat(listingLine,ObjectCode);
		printf("this is listingLine %s\n",listingLine);
		numofcolum = readline(source);
		while(numofcolum == 0)
		{
			numofcolum = readline(source);
		}
	}
	int textLength = strlen(listingLine)/2;

	printf("Length of listingLine %02X\n", textLength);
	fprintf(object,"T%06X%02X%s\n",LineStartLocCtr,textLength,listingLine);
	fprintf(object,"E%06X\n",startingadres);
	if((fclose(source)!=0) || (fclose(object) != 0))
	{
		fprintf(stderr,"file close error \n");
		exit(1);
	}
}
