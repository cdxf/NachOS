// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

  #include "copyright.h"
  #include "system.h"
  #include "syscall.h"
  #define MaxStringLength 256
//----------------------------------------------------------------------
// ExceptionHandler
//  Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
//  For system calls, the following is the calling convention:
//
//  system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions
//	are in machine.h.
//----------------------------------------------------------------------

// Input: - User space address (int)
//     - Limit of buffer (int)
// Output:- Buffer (char*)
// Purpose: Copy buffer from User memory space to System memory space



char* User2System(int virtAddr,int limit)
{
        int i; // index
        int oneChar;
        char* kernelBuf = NULL;
        kernelBuf = new char[limit +1]; //need for terminal string
        if (kernelBuf == NULL)
                return kernelBuf;
        memset(kernelBuf,0,limit+1);
        //printf("\n Filename u2s:");
        for (i = 0; i < limit; i++)
        {
                machine->ReadMem(virtAddr+i,1,&oneChar);
                kernelBuf[i] = (char)oneChar;
                //printf("%c",kernelBuf[i]);
                if (oneChar == 0)
                        break;
        }
        return kernelBuf;
}

// Input: - User space address (int)
//      - Limit of buffer (int)
//      - Buffer (char[])
// Output:- Number of bytes copied (int)
// Purpose: Copy buffer from System memory space to User memory space
int System2User(int virtAddr,int len,char* buffer)
{
        if (len < 0) return -1;
        if (len == 0) return len;
        int i = 0;
        int oneChar = 0;
        do {
                oneChar= (int) buffer[i];
                machine->WriteMem(virtAddr+i,1,oneChar);
                i++;
        } while(i < len && oneChar != 0);
        return i;
}

inline void syscallreturn(int result){
	machine->WriteRegister(2,result);
}
inline int syscallget(int i){
	return (machine->ReadRegister(i+3));
}

int op1, op2, result, n;
char* buffer = new char[MaxStringLength];
int virtAddr, len;
int openFileFlag = 0;
OpenFile* OpenFileTable[10];
void
//Varible for Readint()
ExceptionHandler(ExceptionType which)
{
        int type = machine->ReadRegister(2);
        // Input: reg4 -filename (string)
        // Output: reg2 -1: error and 0: success
        // Purpose: process the event SC_Create of System call
        // mã system call sẽ được đưa vào thanh ghi r2 (có thể xem lại phần xử lý cho
        // system call Halt trong tập tin start.s ở trên)
        // tham số thứ 1 sẽ được đưa vào thanh ghi r4
        // tham số thứ 2 sẽ được đưa vào thanh ghi r5
        // tham số thứ 3 sẽ được đưa vào thanh ghi r6
        // tham số thứ 4 sẽ được đưa vào thanh ghi r7
        // kết quả thực hiện của system call sẽ được đưa vào thanh ghi r2
        switch (which) {
        case NoException:
                return;
        case PageFaultException:
                DEBUG('a', "\n PageFaultExceptio");
                printf ("\n\n PageFaultExceptio");
                interrupt->Halt();
                break;
        case ReadOnlyException:
                DEBUG('a', "\n PageFaultExceptio");
                printf ("\n\n PageFaultExceptio");
                interrupt->Halt();
                break;
        case BusErrorException:
                DEBUG('a', "\n BusErrorException");
                printf ("\n\n BusErrorException");
                interrupt->Halt();
                break;
        case AddressErrorException:
                DEBUG('a', "\n AddressErrorException");
                printf ("\n\n AddressErrorException");
                interrupt->Halt();
                break;
        case OverflowException:
                DEBUG('a', "\n OverflowException");
                printf ("\n\n OverflowException");
                interrupt->Halt();
                break;
        case IllegalInstrException:
                DEBUG('a', "\n IllegalInstrException");
                printf ("\n\n IllegalInstrException");
                interrupt->Halt();
                break;
        case NumExceptionTypes:
                DEBUG('a', "\n NumExceptionTypes");
                printf ("\n\n NumExceptionTypes");
                interrupt->Halt();
                break;
        case SyscallException:
                switch (type) {
                case SC_Halt:
                        DEBUG('a', "\n Shutdown, initiated by user program.");
                        printf ("\n\n Shutdown, initiated by user program.");
			printf ("\n\n Disk: ");
			fileSystem->Print();
                        interrupt->Halt();
                        break;
                case SC_CreateFile:
                {
                        int virtAddr;
                        char* filename;
                        DEBUG('a',"\n SC_CreateFile call ...");
                        DEBUG('a',"\n Reading virtual address of filename");
                        // Lấy tham số tên tập tin từ thanh ghi r4
                        virtAddr = machine->ReadRegister(4);
                        DEBUG ('a',"\n Reading filename.");
                        filename = User2System(virtAddr,MaxStringLength+1);
                        if (filename == NULL)
                        {
                                printf("\n Not enough memory in system");
                                DEBUG('a',"\n Not enough memory in system");
                                syscallreturn(-1); // trả về lỗi cho chương
                                // trình người dùng
                                delete filename;
                                return;
                        }
                        DEBUG('a',"\n Finish reading filename.");
			printf(filename);
                        if (!fileSystem->Create(filename,0))
                        {
                                printf("\n Error create file '%s'",filename);
                                syscallreturn(-1);
                                delete filename;
                                return;
                        }

                       syscallreturn(0); // trả về cho chương trình
                        // người dùng thành công
                        delete filename;
                        break;
                }
                case SC_Exit:
                        DEBUG('a', "\n SC_Exit");
                        printf ("\n\n SC_Exit");
                        break;
                case SC_Exec:
                        DEBUG('a', "\n SC_Exec");
                        printf ("\n\n SC_Exec");
                        break;
                case SC_Join:
                        DEBUG('a', "\n SC_Join");
                        printf ("\n\n SC_Join");
                        break;
                case SC_Open:
		{
                        DEBUG('a', "\n SC_Open");
                        printf("\n\n SC_Open");
			int virtAddr;
                        char* filename;
                        virtAddr = syscallget(1);
                        DEBUG ('a',"\n Reading filename.");
                        filename = User2System(virtAddr,MaxStringLength+1);
			openFileFlag = syscallget(2);
			int id = -1;
			// 0 and 1 are used for SynchConsle
			for(int i=2; i<10;i++){
				if(OpenFileTable[i] != NULL) 
				{
					id = i;
					break;
				}
			}
			if(id = -1){
				syscallreturn(-1);
				DEBUG('a',"\n OpenFileTable can't contain more than 10 files.");
			}
			else{
				OpenFile* file = fileSystem->Open(filename);
				//Store OpenFile into OpenFileTable;
				OpenFileTable[id] = file;
				syscallreturn(0);
			}
                        break;
		}
                case SC_Read:
                        DEBUG('a', "\n SC_Read");
                        printf ("\n\n SC_Read");
                        break;
                case SC_Write:
                        DEBUG('a', "\n SC_Write");
                        printf ("\n\n SC_Write");
                        break;
                case SC_Close:
                        DEBUG('a', "\n SC_Close");
                        printf ("\n\n SC_Close");
                        break;
                case SC_Fork:
                        DEBUG('a', "\n SC_Fork");
                        printf ("\n\n SC_Fork");
                        break;
                case SC_Yield:
                        DEBUG('a', "\n SC_Yield");
                        printf ("\n\n SC_Yield");
                        break;
                case SC_Sub:
                        op1 = machine->ReadRegister (4);
                        op2 = machine->ReadRegister (5);
                        result = op1 - op2;
                        machine->WriteRegister (2, result);
                        printf("%d - %d = %d \n",op1,op2,result);
                        //interrupt->Halt();
                        break;
                case SC_ReadInt:
                        gSynchConsole->Read(buffer,256);
                        result = atoi(buffer);
                        for(int i = 0; i < strlen(buffer); i++)
                        {
				if(i == 0 && buffer[i] == '-') continue;
                                if(buffer[i]>'9' || buffer[i] < '0') {
                                        result = 0;
                                        break;
                                }
                        }
                        machine->WriteRegister (2, result);
                        break;
                case SC_ReadChar:
                        gSynchConsole->Read(buffer,MaxStringLength);
                        machine->WriteRegister (2, buffer[0]);
                        break;
                case SC_PrintChar:
                        buffer[0] = machine->ReadRegister(4);
                        buffer[1] = '\0';
                        gSynchConsole->Write(buffer,2);
                        break;
                case SC_PrintInt:
                        op1 = machine->ReadRegister(4);
                        //Chuyen int sang string
                        sprintf(buffer,"%d",op1);
                        gSynchConsole->Write(buffer,strlen(buffer));
                        break;
                case SC_PrintString:
                        virtAddr = machine->ReadRegister(4);
                        buffer = User2System(virtAddr,MaxStringLength);
                        gSynchConsole->Write(buffer,strlen(buffer));
                        break;
                case SC_ReadString:
                        virtAddr = machine->ReadRegister(4);
                        len = machine->ReadRegister(5);
                        gSynchConsole->Read(buffer,MaxStringLength);
                        System2User(virtAddr,len,buffer);
                        break;
                default:
                        printf("\n Unexpected user mode exception (%d %d)", which,type);
                        interrupt->Halt();
                }
                machine->registers[PrevPCReg] = machine->registers[PCReg];
                machine->registers[PCReg] = machine->registers[NextPCReg];
                machine->registers[NextPCReg] += 4;
        }
}
