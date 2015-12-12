#include "stdafx.h"
#include "CppUnitTest.h"
#include <MD5.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MDFIVETest
{		
	TEST_CLASS(MD5Tests)
	{
	public:
		
		TEST_METHOD(leftRotateTest)
		{
			Assert::AreEqual(20, MD5::leftRotate(10,1), 0);
			// TODO: Your test code here
		}
		TEST_METHOD(castToCharTest)
		{
			char ar[4];
			MD5::castToChar(ar, 0x12345678);
			Assert::AreEqual(0x12, (int)(ar[0]), 0);
			Assert::AreEqual(0x34, (int)(ar[1]), 0);
			Assert::AreEqual(0x56, (int)(ar[2]), 0);
			Assert::AreEqual(0x78, (int)(ar[3]), 0);
		}
		TEST_METHOD(castLongToCharTest)
		{
			char ar[8];
			MD5::castLongToChar(ar, 0x1234567811223344);
			Assert::AreEqual(0x44, (int)ar[0], 0);
			Assert::AreEqual(0x33, (int)ar[1], 0);
			Assert::AreEqual(0x22, (int)ar[2], 0);
			Assert::AreEqual(0x11, (int)ar[3], 0);
			Assert::AreEqual(0x78, (int)ar[4], 0);
			Assert::AreEqual(0x56, (int)ar[5], 0);
			Assert::AreEqual(0x34, (int)ar[6], 0);
			Assert::AreEqual(0x12, (int)ar[7], 0);
		}
		TEST_METHOD(littleToBigEndianTest)
		{
			Assert::AreEqual(0x78563412, MD5::littleToBigEndian(0x12345678), 0);
		}
		TEST_METHOD(castCharToIntTest)
		{
			char ar[] = { 'a', 'b', 'c', 'd' };
			Assert::AreEqual(0x64636261, MD5::castCharToInt(ar), 0);
		}
		TEST_METHOD(emptyHash)
		{
			//case empty
			//before
			std::ofstream emptyHash;
			emptyHash.open("empty.txt");
			emptyHash.close();
			//test
			Assert::AreEqual(std::string("d41d8cd98f00b204e9800998ecf8427e"), MD5::calculateHash("empty.txt"), false);
			//after
			remove("empty.txt");
		}
		TEST_METHOD(lessThan448Bits){
			//case l<448 bit
			//before
			std::ofstream l448;
			l448.open("l448.txt");
			l448 << "Alles ist wunderbar";
			l448.close();
			//test
			Assert::AreEqual(std::string("c50148fc88daa43d85149ecdfb7f43e3"), MD5::calculateHash("l448.txt"), false);
			//after
			remove("l448.txt");

		}
		TEST_METHOD(equalTo448Bits){
			//case l = 448
			//before
			std::ofstream e448;
			e448.open("e448.txt");
			e448 << "Testujemy fantastyczne metody i musimy miec 56 znakow!!!";
			e448.close();
			//test
			Assert::AreEqual(std::string("2b38ea8cc9e99877945324212652b548"), MD5::calculateHash("e448.txt"), false);
			//after
			remove("e448.txt");

		}
		TEST_METHOD(moreThan448Bits){
			//case l > 448
			//before
			std::ofstream m448;
			m448.open("m448.txt");
			m448 << "Testujemy fantastyczne metody i musimy miec ponad 56 znakow!!!";
			m448.close();
			//test
			Assert::AreEqual(std::string("23709204281e62f210fc9f613c92eaa2"), MD5::calculateHash("m448.txt"), false);
			//after
			remove("m448.txt");

		}
		TEST_METHOD(equalTo512Bits){
			//case l = 512
			//before
			std::ofstream e512;
			e512.open("e512.txt");
			e512 << "Testujemy fantastyczne metody, musimy miec dokladnie 64 znaki!!!";
			e512.close();
			//test
			Assert::AreEqual(std::string("9a15857d94fd673c7a09689a180a749e"), MD5::calculateHash("e512.txt"), false);
			//after
			remove("e512.txt");

		}
		TEST_METHOD(moreThan512Bits){
			//case l > 512
			//before
			std::ofstream m512;
			m512.open("m512.txt");
			m512 << "Testujemy fantastyczne metody i musimy miec znacznie wiecej niz 64 znaki!!!";
			m512.close();
			//test
			Assert::AreEqual(std::string("6e1dbf5e493d45db99cd59eaf72db062"), MD5::calculateHash("m512.txt"), false);
			//after
			remove("m512.txt");


		}

	};
}