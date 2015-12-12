#include "stdafx.h"
#include "CppUnitTest.h"
#include <MD5.h>
#pragma managed
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
		//TEST_METHOD(castToCharTest)
		//{
		//	Assert::AreEqual(20, MD5::castToChar(), 0);
		//	// TODO: Your test code here
		//}
		//TEST_METHOD(castLongToCharTest)
		//{
		//	Assert::AreEqual(20, MD5::castLongToChar(10, 1), 0);
		//	// TODO: Your test code here
		//}
		//TEST_METHOD(littleToBigEndianTest)
		//{
		//	Assert::AreEqual(20, MD5::littleToBigEndian(10, 1), 0);
		//	// TODO: Your test code here
		//}
		//TEST_METHOD(castCharToIntTest)
		//{
		//	Assert::AreEqual(20, MD5::castCharToInt(10, 1), 0);
		//	// TODO: Your test code here
		//}
		TEST_METHOD(calculateHashTest)
		{
			Assert::AreEqual(std::string("d41d8cd98f00b204e9800998ecf8427e"), MD5::calculateHash("c:\\test.txt"),false);
			// TODO: Your test code here
		}

	};
}