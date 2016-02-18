#define DLL_EXPORT
#include "MD5Func.h"

extern "C"{
//(B and C) or((not B) and D)
	DECLDIR int __stdcall FFunc(int b, int c, int d){
	return ((b & c) | (~b & d));
}
//(D and B) or ((not D) and C)
	DECLDIR int __stdcall GFunc(int b, int c, int d){
	return ((d & b) | (~d & c));
}
//B xor C xor D
	DECLDIR int __stdcall HFunc(int b, int c, int d){
	return (b ^ c ^ d);
}
//C xor (B or (not D))
	DECLDIR int __stdcall IFunc(int b, int c, int d){
	return (c ^ (b | ~d));
}

	DECLDIR void __stdcall UpdateHash(int * current, int * result){
	for (int i = 0; i < 4;i++)
	current[i] += result[i];
}
}