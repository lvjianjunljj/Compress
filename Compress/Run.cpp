#include <iostream>  
#include <stdio.h>
#include<stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <io.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "snappy.h"
#include "file.h" 
#include "FileCompress1.hpp"
#include "FileCompress2.h"
#include "Compressor.h" 
#include "lzss.h"
using namespace std;

void compressSnappy(string binaryDirPath, string compressDirPath, string logFilePrefixName) {
	time_t nowtime;
	nowtime = time(NULL); //获取当前时间  
	struct tm *local;
	local = localtime(&nowtime);  //获取当前系统时间  
	string timeStr = to_string(local->tm_year + 1900) +
		"_" + to_string(local->tm_mon + 1) +
		"_" + to_string(local->tm_mday) +
		"_" + to_string(local->tm_hour) +
		"_" + to_string(local->tm_min) +
		"_" + to_string(local->tm_sec);

	//string binaryDirPath = "D:\\data\\company work\\PDI\\test data\\dui doc data binary";
	//string comDirPath = "D:\\data\\company work\\PDI\\test data\\dui doc data compress snappy";
	//string logFilePath = "D:\\data\\company work\\PDI\\test data\\compress data statistics\\dui_snappy_compress_" +
		//timeStr + ".log";
	string logFilePath = logFilePrefixName + timeStr + ".log";

	vector<string> fileList = File::folderTraversalSingleLayerName(binaryDirPath);
	ofstream out(logFilePath, ios::trunc);
	if (out.is_open())
	{
		for (string fileName : fileList) {
			string binaryFilePath = binaryDirPath + "\\" + fileName;
			string comFilePath = compressDirPath + "\\" + fileName;
			ifstream fin(comFilePath);
			if (fin) {
				fin.close();
				continue;
			}
			fin.close();
			string instr, outstr;

			int CompressBegin = GetTickCount();
			int binaryFileSize = File::ReadFileToStringOrDie(binaryFilePath.c_str(), &instr);
			snappy::Compress(instr.data(), instr.size(), &outstr);
			int compressFileSize = File::WriteStringToFileOrDie(outstr, comFilePath.c_str());
			int CompressEnd = GetTickCount();

			out << binaryFileSize << "\t" << compressFileSize << "\t" << CompressEnd - CompressBegin << endl;
		}
		out.close();
	}
	else {
		cout << "log file open error!!!" << endl;
	}

}
void testSnappyUncompress() {
	const char* comFileName = "D:\\data\\company work\\PDI\\test data\\1_compress";
	const char* uncomFileName = "D:\\data\\company work\\PDI\\test data\\1__uncomress";

	string instr, outstr;

	int unCompressBegin = GetTickCount();
	File::ReadFileToStringOrDie(comFileName, &instr);
	snappy::Uncompress(instr.data(), instr.size(), &outstr);
	File::WriteStringToFileOrDie(outstr, uncomFileName);
	int unCompressEnd = GetTickCount();
	cout << "Uncompress time cost: " << unCompressEnd - unCompressBegin << " ms" << endl;

}

void testHuffmanCompress1() {
	FileCompress<CharInfo> compress;
	int CompressBegin = GetTickCount();
	compress.Compress("D:\\data\\company work\\PDI\\test data\\1");
	int CompressEnd = GetTickCount();
	cout << "Compress time cost: " << CompressEnd - CompressBegin << " ms" << endl;

}

void testHuffmanUncompress1()
{
	FileCompress<CharInfo> uncompress;
	int UncompressBegin = GetTickCount();
	uncompress.UnCompress("D:\\data\\company work\\PDI\\test data\\1_compress");
	int UncompressEnd = GetTickCount();
	cout << "Uncompress time cost: " << UncompressEnd - UncompressBegin << " ms" << endl;
}

void testHuffmanCompress2() {
	const char* comFileName = "D:\\data\\company work\\PDI\\test data\\1";
	const char* unComFileName = "D:\\data\\company work\\PDI\\test data\\1_compress";

	int CompressBegin = GetTickCount();
	FileCompress2::Compress(comFileName, unComFileName);
	int CompressEnd = GetTickCount();
	cout << "Compress time cost: " << CompressEnd - CompressBegin << " ms" << endl;

}

void testHuffmanUncompress2()
{
	const char* unComFileName = "D:\\data\\company work\\PDI\\test data\\1_compress";
	const char* toComFileName = "D:\\data\\company work\\PDI\\test data\\1_uncompress";

	int UncompressBegin = GetTickCount();
	FileCompress2::UnCompress(unComFileName, toComFileName);
	int UncompressEnd = GetTickCount();
	cout << "Uncompress time cost: " << UncompressEnd - UncompressBegin << " ms" << endl;
}
void  testLz77() {
	Compressor c("/home/facu/text.txt", 3);
	std::cout << c.get_TEXT_FILE() << std::endl;
	std::cout << c.get_TEXT_ENCONDED() << std::endl;
	c.save_file_encoded();
}

void compressLzss(string binaryDirPath, string compressDirPath, string logFilePrefixName) {
	time_t nowtime;
	nowtime = time(NULL); //获取当前时间  
	struct tm *local;
	local = localtime(&nowtime);  //获取当前系统时间  
	string timeStr = to_string(local->tm_year + 1900) +
		"_" + to_string(local->tm_mon + 1) +
		"_" + to_string(local->tm_mday) +
		"_" + to_string(local->tm_hour) +
		"_" + to_string(local->tm_min) +
		"_" + to_string(local->tm_sec);

	//string binaryDirPath = "D:\\data\\company work\\PDI\\test data\\dui doc data binary";
	//string comDirPath = "D:\\data\\company work\\PDI\\test data\\dui doc data compress lzss";
	//string logFilePath = "D:\\data\\company work\\PDI\\test data\\compress data statistics\\dui_lzss_compress_" +
		//timeStr + ".log";
	string logFilePath = logFilePrefixName + timeStr + ".log";

	vector<string> fileList = File::folderTraversalSingleLayerName(binaryDirPath);
	ofstream out(logFilePath, ios::trunc);
	if (out.is_open())
	{
		for (string fileName : fileList) {
			string binaryFilePath = binaryDirPath + "\\" + fileName;
			string comFilePath = compressDirPath + "\\" + fileName;
			ifstream fin(comFilePath);
			if (fin) {
				fin.close();
				continue;
			}
			fin.close();
			string instr, outstr;

			int CompressBegin = GetTickCount();
			int binaryFileSize = File::ReadFileToStringOrDie(binaryFilePath.c_str(), &instr);
			LZSS lzss;
			FILE* outputFile = fopen(comFilePath.c_str(), "wb");
			int compressFileSize = lzss.Compress((unsigned char*)instr.c_str(), instr.size(), outputFile);
			fclose(outputFile);
			int CompressEnd = GetTickCount();

			out << binaryFileSize << "\t" << compressFileSize << "\t" << CompressEnd - CompressBegin << endl;
		}
		out.close();
	}
	else {
		cout << "log file open error!!!" << endl;
	}
}
void testLzssUncompress() {
	const char* comFileName = "D:\\data\\company work\\PDI\\test data\\1_compress_lzss";
	const char* uncomFileName = "D:\\data\\company work\\PDI\\test data\\1_uncompress_lzss";

	string instr, outstr;
	int unCompressBegin = GetTickCount();
	File::ReadFileToStringOrDie(comFileName, &instr);
	LZSS lzss;
	lzss.UnCompress((unsigned char*)instr.c_str(), instr.size(), fopen(uncomFileName, "wb"));
	int unCompressEnd = GetTickCount();
	cout << "Uncompress time cost: " << unCompressEnd - unCompressBegin << " ms" << endl;


}

int changeToApproximateInt(int inputNum, int effectiveNum) {
	int level = 0;
	int tenHexEffectiveNum = pow(10, effectiveNum);
	while (inputNum > tenHexEffectiveNum) {
		inputNum /= 10;
		level++;
	}
	for (int i = 0; i < level; i++) {
		inputNum *= 10;
	}
	return inputNum;
}

void split(std::string s, string delim, std::vector<std::string>* ret)
{
	size_t last = 0;
	size_t index = s.find_first_of(delim, last);
	while (index != string::npos)
	{
		ret->push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(delim, last);
	}
	if (index - last > 0)
	{
		ret->push_back(s.substr(last, index - last));
	}
}

int getAverage(vector<int>& nums) {
	int sum = 0;
	for (int i : nums) {
		sum += i;
	}
	return sum / nums.size();
}

void countCompressSizeFromLog(string compressLogFilePath, string countCompressLogFilePath) {
	int effectiveNum = 3;
	//string compressLogFilePath = "D:\\data\\company work\\PDI\\test data\\statistics\\caption_lzss_compress_log.txt";
	//string countCompressLogFilePath = "D:\\data\\company work\\PDI\\test data\\statistics\\caption_lzss_compress_log_count.txt";

	map<int, vector<int>> compressSizeMap;
	map<int, vector<int>> timeMap;
	char buffer[256];
	fstream out;
	out.open(compressLogFilePath, ios::in);
	while (!out.eof())
	{
		out.getline(buffer, 256, '\n');//getline(char *,int,char) 
		vector<string> v;
		split(buffer, "\t", &v);
		if (v.size() < 3) {
			continue;
		}
		int fileSize = changeToApproximateInt(atoi(v[0].c_str()), effectiveNum);
		if (!compressSizeMap.count(fileSize)) {
			compressSizeMap[fileSize] = vector<int>();
		}
		if (!timeMap.count(fileSize)) {
			timeMap[fileSize] = vector<int>();
		}
		compressSizeMap[fileSize].push_back(atoi(v[1].c_str()));
		timeMap[fileSize].push_back(atoi(v[2].c_str()));
	}
	out.close();
	ofstream output(countCompressLogFilePath, ios::trunc);
	if (output.is_open())
	{
		for (map<int, vector<int>>::iterator my_Itr = compressSizeMap.begin(); my_Itr != compressSizeMap.end(); ++my_Itr) {
			vector<int> compressSizeVec = my_Itr->second;
			vector<int> timeVec = timeMap[my_Itr->first];
			output << my_Itr->first << "\t" << getAverage(compressSizeVec) << "\t" << getAverage(timeVec) << endl;
		}
		output.close();
	}
	else {
		cout << "log file open error!!!" << endl;
	}
}
void countCompressSizeFromFile(string binaryDirPath, string compressDirPath, string logFilePrefixName) {
	time_t nowtime;
	nowtime = time(NULL); //获取当前时间  
	struct tm *local;
	local = localtime(&nowtime);  //获取当前系统时间  
	string timeStr = to_string(local->tm_year + 1900) +
		"_" + to_string(local->tm_mon + 1) +
		"_" + to_string(local->tm_mday) +
		"_" + to_string(local->tm_hour) +
		"_" + to_string(local->tm_min) +
		"_" + to_string(local->tm_sec);

	//string binaryDirPath = "D:\\data\\company work\\PDI\\test data\\dui doc data binary";
	//string compressDirPath = "D:\\data\\company work\\PDI\\test data\\dui doc data compress snappy";
	//string logFilePath = "D:\\data\\company work\\PDI\\test data\\compress data statistics\\dui_snappy_compress_" +
		//timeStr + ".log";
	string logFilePath = logFilePrefixName + timeStr + ".log";

	map<string, int> binaryFileSizeMap = File::folderTraversalSingleLayerNameSize(binaryDirPath);
	map<string, int> compressFileSizeMap = File::folderTraversalSingleLayerNameSize(compressDirPath);

	ofstream out(logFilePath, ios::trunc);
	if (out.is_open())
	{
		for (map<string, int>::iterator itr = binaryFileSizeMap.begin(); itr != binaryFileSizeMap.end(); ++itr) {
			string fileName = itr->first;
			if (!compressFileSizeMap.count(fileName)) {
				cout << "file not exist!! filename: " << fileName << endl;
				continue;
			}

			out << itr->second << "\t" << compressFileSizeMap[fileName] << endl;

		}
		out.close();
	}
	else {
		cout << "log file open error!!!" << endl;
	}
}
bool startswith(const string& str, const string& startContent) {
	return str.length() >= startContent.length() && str.substr(0, startContent.length()) == startContent;
}

void logDataSummary(string logDirPath, string logDataSummaryFilePath, string logFilePrefixName) {
	vector<string> logFileList = File::folderTraversalSingleLayerName(logDirPath);
	ofstream out(logDataSummaryFilePath, ios::trunc);
	if (out.is_open())
	{
		for (string logFileName : logFileList) {
			if (startswith(logFileName, logFilePrefixName)) {
				string logFilePath = logDirPath + "\\" + logFileName;
				string instr;
				File::ReadFileToStringOrDie(logFilePath.c_str(), &instr);
				// Read the entire file, so there is a line break in the input content. 
				out << instr;
			}
		}
		out.close();
	}
	else {
		cout << "log file open error!!!" << endl;
	}
}


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
		compressSnappy(inputDirPath, outputDirPath, logFilePrefixName);
		cout << "compress file with snappy complete!!!" << endl;
	}
	else if (methodName == "compressLzss") {
		compressLzss(inputDirPath, outputDirPath, logFilePrefixName);
		cout << "compress file with lzss complete!!!" << endl;
	}
	else if (methodName == "countCompressSizeFromLog") {
		countCompressSizeFromLog(inputDirPath, outputDirPath);
		cout << "count compress size from log complete!!!" << endl;
	}
	else if (methodName == "countCompressSizeFromFile") {
		countCompressSizeFromFile(inputDirPath, outputDirPath, logFilePrefixName);
		cout << "count compress size from file complete!!!" << endl;
	}
	else if (methodName == "logDataSummary") {
		logDataSummary(inputDirPath, outputDirPath, logFilePrefixName);
		cout << "log data summary complete!!!" << endl;
	}
	else if (methodName == "") {

	}
	else if (methodName == "") {

	}
	else if (methodName == "") {

	}
	else if (methodName == "") {

	}
	else {
		cout << "not exist the method: " << methodName << endl;
	}

	//testSnappyCompress();
	//testSnappyUncompress();
	//testHuffmanCompress1();
	//testHuffmanUncompress1();
	//testHuffmanCompress2();
	//testHuffmanUncompress2();
	//testLzssCompress();
	//testLzssUncompress();
	//countCompressedSizeFromLog();
	//countCompressedSizeFromFile();
	return 0;
}
