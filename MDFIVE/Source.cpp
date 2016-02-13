
#include <windows.h>
#include <winbase.h>
#include <time.h>
#include "MD5.h"
#include "GUI.h"

[System::STAThread]
int __stdcall WinMain(_In_ HINSTANCE hInstance,	_In_ HINSTANCE hPrevInstance,	_In_ LPSTR     lpCmdLine,	_In_ int       nCmdShow){
	MDFIVE::GUI^ windows = gcnew MDFIVE::GUI();
	windows->ShowDialog();
	return 0;
}
