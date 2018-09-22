#include <iostream>  
#include <string>
#include <io.h>
#include "Operator.h"
using namespace std;
int main(int argc, char *argv[]) {
	/*
	the length of command line input must be 4, that is the argc must be 5
	1. the selection of reflection method. example: compressSnappy
	2. the path of input directory.
	example: D:\\data\\company work\\PDI\\test data\\DuiDoc\\DuiDocumentBinary
	3. the path of output directory.
	example: D:\\data\\company work\\PDI\\test data\\DuiDoc\\DuiDocumentCompressSnappy
	4. the prefix name of log file.
	example: D:\\data\\company work\\PDI\\test data\\statistics\\dui_snappy_compress_
	*/
	if (argc != 5) {
		cout << "the length of command line input must be 4!!!" << endl;
		cout << "the input of directory path cannot end with \\" << endl;
		return -1;
	}
	string methodName = argv[1];
	string inputDirPath = argv[2];
	string outputDirPath = argv[3];
	string logFilePrefixName = argv[4];
	if (inputDirPath[inputDirPath.size() - 1] == '"') {
		inputDirPath = inputDirPath.substr(0, inputDirPath.size() - 1);
	}
	if (_access(inputDirPath.c_str(), 0) == -1)
	{
		cout << "input directory not exist!!! " << inputDirPath << endl;
		return -1;
	}
	if (outputDirPath[outputDirPath.size() - 1] == '"') {
		outputDirPath = outputDirPath.substr(0, outputDirPath.size() - 1);
	}
	if (_access(outputDirPath.c_str(), 0) == -1)
	{
		cout << "output directory not exist!!! " << outputDirPath << endl;
		return -1;
	}

	if (methodName == "compressSnappy") {
		Operator::compressSnappy(inputDirPath, outputDirPath, logFilePrefixName);
		cout << "compress file with snappy complete!!!" << endl;
	}
	else if (methodName == "uncompressSnappy") {
		Operator::uncompressSnappy(inputDirPath, outputDirPath, logFilePrefixName);
		cout << "uncompress file with snappy complete!!!" << endl;
	}
	else if (methodName == "compressLzss") {
		Operator::compressLzss(inputDirPath, outputDirPath, logFilePrefixName);
		cout << "compress file with lzss complete!!!" << endl;
	}
	else if (methodName == "uncompressLzss") {
		Operator::uncompressLzss(inputDirPath, outputDirPath, logFilePrefixName);
		cout << "uncompress file with lzss complete!!!" << endl;
	}
	else if (methodName == "countCompressSizeFromLog") {
		// The input name is not suitable, but this kind of writing is relatively simple
		Operator::countCompressSizeFromLog(inputDirPath, outputDirPath, logFilePrefixName);
		cout << "count compress size from log complete!!!" << endl;
	}
	else if (methodName == "countCompressSizeFromFile") {
		Operator::countCompressSizeFromFile(inputDirPath, outputDirPath, logFilePrefixName);
		cout << "count compress size from file complete!!!" << endl;
	}
	else if (methodName == "logDataSummary") {
		Operator::logDataSummary(inputDirPath, outputDirPath, logFilePrefixName);
		cout << "log data summary complete!!!" << endl;
	}
	else if (methodName == "convertDocToBinary") {
		Operator::convertDocToBinary(inputDirPath, outputDirPath, logFilePrefixName);
		cout << "convert doc file to binary file complete!!!" << endl;
	}
	else if (methodName == "printDocContentBasedonBinary") {
		Operator::printDocContentBasedonBinary(inputDirPath);
		cout << "log data summary complete!!!" << endl;
	}
	else {
		cout << "not exist the method: " << methodName << endl;
	}
	return 0;
}
