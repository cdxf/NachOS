#include "syscall.h"
#include "copyright.h"
#define maxlen 32
int main()
{
        int len;
        OpenFileId fileid;
        char buffer[maxlen];
        char filename[maxlen +1];
        /*Create a file*/
        PrintString("Nhap ten file can tao: ");
        ReadString(filename,maxlen);
        if(CreateFile(filename) == 0) {
                PrintString("Da tao File Thanh Cong \n");
                PrintString("OpenFileId:");
                fileid = Open(filename,0);
                PrintInt(fileid);
                PrintChar('\n');
                PrintString("Nhap noi dung cua file: ");
                len = ReadString(buffer,maxlen);
                if(Write(buffer,len,fileid) != -1) {
                        PrintString("Da viet vao file thanh cong \n");
                        PrintString("Ban co the dung chuong trinh cat de xem noi dung file \n");
                }
                else{
                        PrintString("Viet vao file that bai\n");
                }
        }
        else{
                PrintString("Tao file that bai, file da ton tai hoac DISK chua duoc format \n");
                PrintString("Su dung lenh 'nachos -f' de format DISK\n");
        }
}
