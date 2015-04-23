#include "syscall.h"
#include "copyright.h"
#define maxlen 32
int main()
{
	int num;
	PrintString("Nhap so: ");
     	num = ReadInt();
      	
	PrintString("So vua nhap la\n");
	PrintInt(num);
}
