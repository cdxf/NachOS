#include "syscall.h"
#include "copyright.h"
#define maxlen 32
int main()
{
    int len;
    OpenFileId fileid;
    char buffer[maxlen];
    char filename[maxlen +1];
    /*Read from Console Input*/
    Read(buffer,maxlen,0);
    /*And write to Console Output*/
    Write(buffer,maxlen,1);
}
