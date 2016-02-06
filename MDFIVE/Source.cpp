
#include <windows.h>
#include <winbase.h>
#include <time.h>
#include "MD5.h"
#include "GUI.h"

[System::STAThread]
int main(array<System::String ^> ^args){
	//std::cout<<MD5::calculateHash("D:\\ISOS\\java.exe",true);
	MDFIVE::GUI^ windows = gcnew MDFIVE::GUI();
	windows->ShowDialog();

	return 0;
}
