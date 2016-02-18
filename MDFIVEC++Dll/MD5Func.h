#ifndef _MD5FUNC_
#define _MD5FUNC_

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

extern "C"{
	DECLDIR  int __stdcall FFunc(int b, int c, int d);
	DECLDIR  int __stdcall GFunc(int b, int c, int d);
	DECLDIR  int __stdcall HFunc(int b, int c, int d);
	DECLDIR  int __stdcall IFunc(int b, int c, int d);
	DECLDIR void __stdcall UpdateHash(int * current, int * result);
}

#endif