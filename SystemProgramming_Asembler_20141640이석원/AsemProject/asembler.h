#ifndef __asembler_
#define __asembler_
struct symboltable
{
	char LABEL[10];
	int LOCCTR;
};
struct operationtable
{
	char Operator[7];
	int code;
};
#endif
