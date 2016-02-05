// reference https://de.wikipedia.org/wiki/Message-Digest_Algorithm_5
#include <string>
#include <fstream>
#include <iostream>

namespace MD5{
	int leftRotate(unsigned int a, int i);
	void castToChar(char* ptr, int val);
	void castLongToChar(char* ptr, long long int val);
	int littleToBigEndian(int val);
	int castCharToInt(char* ptr);
	std::string calculateHash(std::string path, bool useAsm);
};