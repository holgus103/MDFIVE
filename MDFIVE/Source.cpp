#define NO_COMP
#define CHUNK_SIZE 64
#include <string>
#include <fstream>
#include <iostream>
inline int leftRotate(unsigned int a, int i){
	return (a << i | a >> 32 - i);
}
void castToChar(char* ptr, int val){
	for (int i = 0; i < 4; i++){
		ptr[i] = (val & (0xFF000000 >> (i*8)));
	}
}

void castLongToChar(char* ptr, long int val){
	for (int i = 0; i < 8; i++){
		ptr[i] = (val & (0xFF00000000000000 >> (i * 8)));
	}
}

int castCharToInt(char* ptr){
	return (ptr[0] | 0x00000000) | (ptr[1] | 0x00000000) | (ptr[2] | 0x00000000) | (ptr[3] | 0x00000000);
}
char* calculateHash(std::string path){
	int shifts[64] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, //0-15
		5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, //15-31
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, //32-47
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 }; //48-63
#ifndef NO_COMP
	// Precomputed sines
	int sines[64];
	for(int i=0;i<64;i++){
		sines[i] = floor(232 × abs(sin(i + 1)))
	}
#else
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
#endif
	// init hash parts
	std::ifstream input;
	input.open(path, std::ios::binary);
	unsigned int a0 = 0x67452301;  //A
	unsigned int b0 = 0xefcdab89;  //B
	unsigned int c0 = 0x98badcfe;  //C
	unsigned int d0 = 0x10325476;  //D
	input.seekg(0,input.end);
	long int size = input.tellg();
	long int remaining = size;
	input.seekg(0, input.beg);
	bool overflow = false;
	//append 1
	//append 0
	while (remaining >0 && !overflow){// operate on chunk
		//prepare chunk of data
		char buffer[CHUNK_SIZE];
		if (overflow){
			for (int i = 0; i < 56; i++){
				buffer[i] = 0;
			}
			castLongToChar(buffer + 56, size);
			if ((size % 64) == 0){
				buffer[0] = 0x80;
			}
		}
		else{
			input.read(buffer, CHUNK_SIZE);
			if (remaining < 56){
				buffer[remaining] = 0x80;
				for (int i = remaining + 1; i < 56; i++){
					buffer[i] = 0;
				}
				castLongToChar(buffer + 56, size);
			}
			else if (remaining >= 56 && remaining < 64){
				buffer[remaining] = 0x80;
				for (int i = remaining + 1; i < 64; i++){
					buffer[i] = 0;
				}
				overflow = true;
			}
			else if (remaining == 64){
				overflow = true;
			}
		}
		//divide chunk
		unsigned int M[16];
		for (int i = 0; i < 16; i++){
			M[i] = castCharToInt(buffer + i * 4);
		}
		unsigned int A = a0;
		unsigned int B = b0;
		unsigned int C = c0;
		unsigned int D = d0;
		unsigned int F;
		unsigned int temp;
		int g;
		for (int i = 0; i < 64; i++){
			if (0 <= i && i <= 15){
				F = (B & C) | ((~B) & D);
				g = i;
			}
			else if (16 <= i && i <= 31){
				F = (D & B) | ((~D) & C);
				g = (5 * i + 1) % 16;
			}
			else if (32 <= i & i <= 47){
				F = B ^ C ^ D;
				g = (3 * i + 5) % 16;
			}
			else if (48 <= i & i <= 63){
				F = C ^ (B | (~D));
				g = (7 * i) % 16;
			}
			temp = D;
			D = C;
			C = B;
			B = B + leftRotate((A + F + sines[i] + M[g]), shifts[i]);
			A = temp;
		}
		a0 += A;
		b0 += B;
		c0 += C;
		d0 += D;
		remaining -= 64;
	}
	char hash[16];
	castToChar(hash, a0);
	castToChar(hash + 4, b0);
	castToChar(hash + 8, c0);
	castToChar(hash + 12,d0);
	return hash;
}


int main(){
	std::cout<<calculateHash("C:\\test.txt");
	return 0;
}
