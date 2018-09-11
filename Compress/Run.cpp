#include <iostream>  
#include "snappy.h"
#include "file.h" 
using namespace std;

void testSnappy() {
	const char* comFielName = "D:\\data\\test data\\2.sst";
	const char* unComFielName = "D:\\data\\test data\\2_compress.sst";
	string TO_COM_FILE_NAME = "D:\\data\\test data\\1_uncomress.sst";
	string instr, outstr;

	File::ReadFileToStringOrDie(comFielName, &instr);
	snappy::Compress(instr.data(), instr.size(), &outstr);
	File::WriteStringToFileOrDie(outstr, unComFielName);



	//File::ReadFileToStringOrDie(UNCOM_FILE_NAME, &instr);
	//snappy::Uncompress(instr.data(), instr.size(), &outstr);
	//File::WriteStringToFileOrDie(outstr, TO_COM_FILE_NAME);

}


int main() {
	testSnappy();
	system("pause");
}
