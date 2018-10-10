#pragma once
#include <string>
using namespace std;

namespace Operator {
	void compressSnappy(string binaryDirPath, string compressDirPath, string logFilePrefixName);
	void uncompressSnappy(string compressDirPath, string uncompressDirPath, string logFilePrefixName);
	void testSnappy(string binaryDirPath, string logFilePrefixName);

	void compressLzss(string binaryDirPath, string compressDirPath, string logFilePrefixName);
	void uncompressLzss(string compressDirPath, string uncompressDirPath, string logFilePrefixName);
	void testLzss(string binaryDirPath, string logFilePrefixName);

	void countCompressSizeFromLog(string compressLogFilePath, string countCompressLogFilePath, string valueRule);
	void countCompressDataFromLog(string compressLogFilePath, string countCompressLogFilePath, string valueRule);
	void countCompressSizeFromFile(string binaryDirPath, string compressDirPath, string logFilePrefixName);
	void logDataSummary(string logDirPath, string logDataSummaryFilePath, string logFilePrefixName);
	void convertDocToBinary(const string& docDirPath, const string& binaryDirPath, const string& logFilePrefixName);
	void printDocContentBasedonBinary(const string& binaryFilePath);
	void printCompressInfoFromLog(string compressLogFilePath);
}