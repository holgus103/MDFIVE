
#include <windows.h>
#include <winbase.h>
#include <time.h>
#include "MD5.h"
#include "GUI.h"


int main(){
	std::cout<<MD5::calculateHash("D:\\ISOS\\java.exe",true);
	//MDFIVE::GUI^ windows = gcnew MDFIVE::GUI();
	//while (windows->Exit);

	return 0;
}
