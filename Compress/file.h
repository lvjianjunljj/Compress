#include <string>  
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

namespace File
{
	int ReadFileToStringOrDie(const char* inputFilePath, string* data);
	int WriteStringToFileOrDie(const string& data, const char* outputFilePath);
	vector<string> folderTraversalSingleLayerName(string dirPath);
	map<string, int> folderTraversalSingleLayerNameSize(string dirPath);
	void Txt2Binary(const char* inputFilePath, const char* outputFilePath);
}