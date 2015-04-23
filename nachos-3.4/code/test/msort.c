#include "syscall.h"
#include "copyright.h"
#define maxlen 32
//SORT PROGRAM

int main()
{
int i,j,n,temp;
int a[100];
PrintString("Nhap n: ");
n = ReadInt();
for(i=0;i<n;i++){
PrintString("Nhap so thu ");
PrintInt(i+1);
PrintString(": ");
a[i] = ReadInt();
}
//Sort
for(i=0; i<n; i++)
{
for(j=0; j<n-1; j++)
{
	if(a[j]>a[j+1])
	{
	temp=a[j];
	a[j]=a[j+1];
	a[j+1]=temp;
	}
}
}
//End sort
PrintString("Ket qua sap xep tang dan: ");
for(i =0;i<n;i++){
PrintInt(a[i]);
PrintString(" ");
}
Halt();
return 0;
}
