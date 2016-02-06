#define CHUNK_SIZE 64
#define BIT512 512
#define BIT448 448
#define ASM
#include "MD5.h"
#include <sstream>
#include <Windows.h>
#include <time.h>
	// Performs a simple rotation
	int MD5::leftRotate(unsigned int a, int i){
		return (a << i | a >> 32 - i);
	}
	// Writes an int to an array of char (big endian)
	void MD5::castToChar(char* ptr, int val){
		for (int i = 0; i < 4; i++){
			ptr[i] = (val & (0xFF000000 >> (i * 8)))>>((3-i)*8);
		}
	}
	// Writes an long long int to an array of char (little endian)
	void MD5::castLongToChar(char* ptr, long long int val){
		for (int i = 0; i < 8; i++){
			ptr[i] = 0xFF & (val >> (i * 8));
		}
	}
	// Returns an little endian int as big endian int
	int MD5::littleToBigEndian(int val){
		return ((val & 0x000000FF) << 24) | ((val & 0x0000FF00) << 8) | ((val & 0x00FF0000) >> 8) | ((val & 0xFF000000) >> 24);
	}
	// Returns an array of 4 char as an int (big endian)
	int MD5::castCharToInt(char* ptr){
		return (ptr[0] & 0x000000FF) | ((ptr[1] & 0x000000FF) << 8) | ((ptr[2] & 0x000000FF) << 16) | ((ptr[3] & 0x000000FF) << 24);
	}
	// Returns a MD5 hash for the file path supplied as parameter
	std::string MD5::calculateHash(std::string path, bool useAsm){
		typedef int(*MD5Func)(int, int, int);
		typedef void(*UpdateHash)(int,int);
		MD5Func FFunc = NULL;
		MD5Func GFunc = NULL;
		MD5Func HFunc = NULL;
		MD5Func IFunc = NULL;
		UpdateHash updateHash = NULL;
		HMODULE hModule = NULL;
		int arr[4] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
		int res[4];
		if (useAsm){
		hModule = LoadLibrary(TEXT("MDFIVEAsmDll.dll"));
		FFunc = (MD5Func)GetProcAddress(hModule, "FFunc");
		GFunc = (MD5Func)GetProcAddress(hModule, "GFunc");
		HFunc = (MD5Func)GetProcAddress(hModule, "HFunc");
		IFunc = (MD5Func)GetProcAddress(hModule, "IFunc");
		updateHash = (UpdateHash)GetProcAddress(hModule, "UpdateHash");
		}
		int shifts[64] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, //0-15
			5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, //15-31
			4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, //32-47
			6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 }; //48-63
		unsigned int sines[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, //0-3
			0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, //4-7
			0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, //8-11
			0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, //12-15
			0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, //16-19
			0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, //20-23
			0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, //24-27
			0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, //28-31
			0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, //32-35
			0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, //36-39
			0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, //40-43
			0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, //44-47
			0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, //48-51
			0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, //52-55
			0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, //56-59
			0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };//60-63
		// init hash parts
		std::ifstream input;
		input.open(path, std::ios::binary);
		input.seekg(0, input.end);
		long long int size = input.tellg();
		long long int remaining = size * 8;
		input.seekg(0, input.beg);
		bool cont = true;
		while (cont){// operate on chunk
			//prepare chunk of data
			char buffer[CHUNK_SIZE];
			input.read(buffer, CHUNK_SIZE);
			if (remaining < BIT512){
				int start;
				if (remaining >= 0){
					buffer[remaining / 8] = 0x80; //append 1 
					start = remaining / 8 + 1; // start writting 0s starting from remaining+1
				}
				else{
					start = 0; // start writing 0s starting from 0
				}
				int max;
				if (remaining >= BIT448){
					max = BIT512 / 8; //fill the rest with 0s as there is gonna be another chunk after this
				}
				else{
					max = BIT448 / 8; //fill with 0s only up to 448
				}
				for (int i = start; i < max; i++){
					buffer[i] = 0;
				}
				if (remaining < BIT448){
					castLongToChar(buffer + (BIT448 / 8), size * 8);
					cont = false;
				}
			}
			//divide chunk
			unsigned int M[16];
			for (int i = 0; i < 16; i++){
				M[i] = castCharToInt(buffer + i * 4);
			}
			res[0] = arr[0];
			res[1] = arr[1];
			res[2] = arr[2];
			res[3] = arr[3];
			unsigned int F;
			unsigned int temp;
			int g;
			//main loop
			for (int i = 0; i < 64; i++){
				if (useAsm){
					if (0 <= i && i <= 15){//F
						F = FFunc(res[1],res[2],res[3]);
						g = i;
					}
					else if (16 <= i && i <= 31){//G
						F = GFunc(res[1], res[2], res[3]);
						g = ((5 * i + 1) & 0x0F);
					}
					else if (32 <= i & i <= 47){//H
						F = HFunc(res[1], res[2], res[3]);
						g = ((3 * i + 5) & 0x0F);
					}
					else if (48 <= i & i <= 63){//I
						F = IFunc(res[1], res[2], res[3]);
						g = ((7 * i) & 0x0F);
					}
				}
				else{
					if (0 <= i && i <= 15){//F
						F = (res[1] & res[2]) | ((~res[1]) & res[3]);
						g = i;
					}
					else if (16 <= i && i <= 31){//G
						F = (res[3] & res[1]) | ((~res[3]) & res[2]);
						g = ((5 * i + 1) & 0x0F);
					}
					else if (32 <= i & i <= 47){//H
						F = res[1] ^ res[2] ^ res[3];
						g = ((3 * i + 5) & 0x0F);
					}
					else if (48 <= i & i <= 63){//I
						F = res[2] ^ (res[1] | (~res[3]));
						g = ((7 * i) & 0x0F);
					}
				}
				temp = res[3];
				res[3] = res[2];
				res[2] = res[1];
				res[1] = res[1] + MD5::leftRotate((res[0] + F + sines[i] + M[g]), shifts[i]);
				res[0] = temp;


			}
			if (useAsm){
				updateHash(arr[0], res[0]);
			}
			else{
				arr[0] += res[0];
				arr[1] += res[1];
				arr[2] += res[2];
				arr[3] += res[3];
			}
			remaining -= 512;
		}
		std::stringstream s;

		s << std::hex << littleToBigEndian(arr[0]);
		s << std::hex << littleToBigEndian(arr[1]);
		s << std::hex << littleToBigEndian(arr[2]);
		s << std::hex << littleToBigEndian(arr[3]);
		input.close();
		if (hModule!=NULL)
		FreeModule(hModule);
		return s.str();
	}