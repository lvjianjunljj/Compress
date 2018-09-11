#include <string>  
#include <fstream>
#include <iostream>
using namespace std;

namespace File
{
	void ReadFileToStringOrDie(const char* filename, string* data);


	void WriteStringToFileOrDie(const string& str, const char* filename);
}