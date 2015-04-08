#include "syscall.h"
#include "copyright.h"
#define maxlen 32
int main()
{
int i;
PrintString("ASCII TABLE"); 

    for(i=0;i < 128;i++)
	{
	PrintInt(i);
	PrintChar(':');
	PrintChar((char) i);
	PrintChar('\n');
    }
	PrintString("\tEND ASCII TABLE");
}
