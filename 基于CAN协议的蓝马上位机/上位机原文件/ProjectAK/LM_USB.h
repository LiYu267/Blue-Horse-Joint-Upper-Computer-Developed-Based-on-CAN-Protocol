// LM_USB.h : LM_USB DLL 的主头文件
extern "C" __declspec(dllexport) unsigned int __stdcall Init_can(unsigned char com_NUM,unsigned char Model,unsigned int CanBaudRate,unsigned char SET_ID_TYPE,unsigned char FILTER_MODE,unsigned char RXF[],unsigned char RXM[]);
extern "C" __declspec(dllexport) unsigned int __stdcall Quit_can();
extern "C" __declspec(dllexport) unsigned int __stdcall Can_send(unsigned char IDbuff[],unsigned char Databuff[],unsigned char FreamType,unsigned char Bytes);
extern "C" __declspec(dllexport) unsigned int __stdcall Can_receive(unsigned char IDbuff[],unsigned char Databuff[],unsigned char *FreamType,unsigned char *Bytes);

extern "C" __declspec(dllexport) unsigned int __stdcall Init_2can(unsigned char com_NUM,unsigned char Model,unsigned char SET_ID_TYPE,unsigned int Can1BaudRate,unsigned char FILTER1_MODE,unsigned char RXF1[],unsigned char RXM1[]
        																								                             ,unsigned int Can2BaudRate,unsigned char FILTER2_MODE,unsigned char RXF2[],unsigned char RXM2[]);
extern "C" __declspec(dllexport) unsigned int __stdcall Can_2send(unsigned char ROAD,unsigned char IDbuff[],unsigned char Databuff[],unsigned char FreamType,unsigned char Bytes);
extern "C" __declspec(dllexport) unsigned int __stdcall Can_2receive(unsigned char *ROAD,unsigned char IDbuff[],unsigned char Databuff[],unsigned char *FreamType,unsigned char *Bytes);
//extern "C"会指示编译器这部分代码按C语言（而不是C++）的方式进行编译。
//dllexport编译dll文件的时候,在dll头文件声明的变量名称前添加dllexport。表明这些东西可以被其他工程使用，即是把 dll中的相关代码(类，函数，全局变量)暴露出来为以后其他应用程序使用。
//__stdcall：Windows API默认的函数调用协议