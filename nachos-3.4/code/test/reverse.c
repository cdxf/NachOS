#include "syscall.h"
#include "copyright.h"
#define maxlen 32
int main()
{
        int i;
        int len;
        int temp;
        OpenFileId fileid;
        char buffer[512];
        char scr[maxlen +1];
        char des[maxlen +1];
        /*Create a file*/
        PrintString("Nhap ten file nguon: ");
        ReadString(scr,maxlen);
        fileid = Open(scr,0);
        len = FileSize(fileid);
        if(fileid == -1) {
                PrintString("Khong tim thay file nguoi \n");
                return 0;
        }
        else{
                Read(buffer,len,fileid);
                for(i = 0; i < len; i++) {
                        if(buffer[i] == '\0') {
                                len = i - 1;
                        }
                }
                for(i = 0; i<len/2; i++) {
                        //swap
                        temp = buffer[i];
                        buffer[i] = buffer[len-i];
                        buffer[len-i] = temp;
                }
        }
        PrintString("Nhap ten file dich: ");
        ReadString(des,maxlen);
        CreateFile(des);
        fileid = Open(des,0);
        if(Write(buffer,len + 1,fileid) != -1) {
                PrintString("Dao file hoan tat, co the dung lenh cat de kiem tra \n ");
        }
        else{
                PrintString("Co loi trong qua trinh copy \n ");
        }
        return 0;
}
