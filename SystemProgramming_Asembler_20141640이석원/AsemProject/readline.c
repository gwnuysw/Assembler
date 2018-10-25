# include <stdio.h>
# include <stdlib.h>
# include <string.h>
extern char Label[10], Opcode[10], Operand[10];

int readline(FILE* line) 
{
	int i , j, k;
	
	char * colum[4];
	char string[50];
	
	
	if(fgets(string, 50, line) != NULL)
	{
		if(string[0] != '.' && string[0] != '\n')
		{
			for(i = 1, colum[0] = strtok(string," \t\n"); colum[i-1] != NULL; i++)
			{
				colum[i] = strtok(NULL," \t\n");
			}

			if(i == 4)
			{
				strcpy(Label,colum[0]);
				strcpy(Opcode,colum[1]);
				strcpy(Operand,colum[2]);
			}
			
			else if(i == 3)
			{
				strcpy(Label, "\t");
				strcpy(Opcode, colum[0]);
				strcpy(Operand, colum[1]);
			}
			else if(i == 2)
			{
				strcpy(Label, "\t");
				strcpy(Opcode, colum[0]);
				strcpy(Operand, "\t");
			}
		}
		else
		{
			i = 1;
		}
	}	
	printf("read %s %s %s\n", Label, Opcode, Operand);
	return i-1;
}
