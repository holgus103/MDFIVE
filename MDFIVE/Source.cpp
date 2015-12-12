// według https://de.wikipedia.org/wiki/Message-Digest_Algorithm_5

#define ASM
#include <windows.h>
#include <winbase.h>
#include <time.h>
#include "MD5.h"


int main(){
	int F = 0, B = 0xefcdab89, C = 0x98badcfe, D = 0x10325476;
	clock_t time, end;
	typedef int(*MD5Func)(int B, int C, int D);
	HMODULE hModule = LoadLibrary(TEXT("MDFIVEDll.dll"));
	MD5Func FFunc = (MD5Func)GetProcAddress(hModule, "FFunc");
	MD5Func GFunc = (MD5Func)GetProcAddress(hModule, "GFunc");
	MD5Func HFunc = (MD5Func)GetProcAddress(hModule, "HFunc");
	MD5Func IFunc = (MD5Func)GetProcAddress(hModule, "IFunc");
	time = clock();
	for (int i = 0; i < 10000000;i++)
	F = FFunc(B, C,D);
	end = clock();
	std::cout << "F asm: " <<  end - time << std::endl;
	time = clock();
	for (int i = 0; i < 10000000; i++)
	F = (B & C) | ((~B) & D);
	end = clock();
	std::cout << "F c: " << end - time << std::endl;
	/*time = clock();
	F = GFunc(B, C, D);
	end = clock();
	std::cout << "G asm: " << time - end << std::endl;
	time = clock();
	F = (D & B) | ((~D) & C);
	end = clock();
	std::cout << "G c: " << time - end << std::endl;
	time = clock();
	F = HFunc(B, C, D);
	end = clock();
	std::cout << "H asm: " << time - end << std::endl;
	time = clock();
	F = B ^ C ^ D;
	end = clock();
	std::cout << "H c: " << time - end << std::endl;
	time = clock();
	F = IFunc(B, C, D);
	end = clock();
	std::cout << "I asm: " << time - end << std::endl;
	time = clock();
	F = C ^ (B | (~D));
	end = clock();
	std::cout << "I c: " << time - end << std::endl;
	time = clock();*/
	FreeModule(hModule);
	//calculateHash("C:\\test.txt");
	return 0;
}
