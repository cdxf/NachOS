#include "syscall.h"
#include "copyright.h"
#define maxlen 32
int main()
{
        int len;
        OpenFileId fileid;
        char buffer[512];
        char filename[maxlen +1];
        /*Create a file*/
        PrintString("Nhap ten file can doc: ");
        ReadString(filename,maxlen);
        fileid = Open(filename,0);
        Read(buffer,FileSize(fileid),fileid);
        PrintString("File doc duoc co kich thuoc la: ");
        PrintInt(FileSize(fileid));
        PrintChar('\n');
        PrintString("Noi dung file doc duoc: ");
        PrintString(buffer);
}
