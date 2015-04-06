#include "syscall.h"
#include "copyright.h"
#define maxlen 32
int main()
{

      int result;
      Print("Hello World \n");
      result = Sub(43, 23);
      result = Sub(21,result);
      Halt();
}
