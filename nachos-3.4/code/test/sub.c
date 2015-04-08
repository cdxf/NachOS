#include "syscall.h"
#include "copyright.h"
#define maxlen 32
int main()
{

      char* result;
      ReadString(result,2);
      PrintString(result);
PrintString("\nString 2:");
ReadString(result,2);
PrintString(result);
PrintString("\nHello");
Halt();
}
