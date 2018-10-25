#ifndef __charAnalisys_
#define __charAnalisys_
void numto(double number, char * ObjectCode);
void operandto(int symint, char * Symbolvalue);
int HexToInt(char buf[], int strsize);  //기타 단어들을 중 x'???' c'???'를 변환 합니다. 
void opcodeto(int symint, char * Symbolvalue);
#endif
