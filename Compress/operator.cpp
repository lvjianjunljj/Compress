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
#include "file-compress1.hpp"
#include "file-compress2.h"
#include "compressor.h" 
#include "lzss.h"
#include "operator.h"
using namespace std;

namespace Operator {

	int blobDataEachLen = 64;
	string hexIndexString = "0123456789abcdef";

	void compressSnappy(string binaryDirPath, string compressDirPath, string logFilePrefixName) {
		time_t nowtime;
		nowtime = time(NULL); //Get current time  
		struct tm *local;
		local = localtime(&nowtime);  //Get current system time  
		string timeStr = to_string(local->tm_year + 1900) +
			"_" + to_string(local->tm_mon + 1) +
			"_" + to_string(local->tm_mday) +
			"_" + to_string(local->tm_hour) +
			"_" + to_string(local->tm_min) +
			"_" + to_string(local->tm_sec);

		string logFilePath = logFilePrefixName + timeStr + ".log";

		vector<string> fileList = File::folderTraversalSingleLayerName(binaryDirPath);
		ofstream out(logFilePath, ios::trunc);
		if (out.is_open())
		{
			// Timing tool
			LARGE_INTEGER  qFreq, qCouStart, qCouEnd;
			double timeCost;
			for (string fileName : fileList) {
				string binaryFilePath = binaryDirPath + "\\" + fileName;
				string compressFilePath = compressDirPath + "\\" + fileName;
				ifstream fin(compressFilePath);
				if (fin) {
					fin.close();
					continue;
				}
				fin.close();
				string instr, outstr;

				int binaryFileSize = File::ReadFileToStringOrDie(binaryFilePath.c_str(), &instr);
				//int CompressBegin = GetTickCount();
				QueryPerformanceFrequency(&qFreq);
				QueryPerformanceCounter(&qCouStart);
				snappy::Compress(instr.data(), instr.size(), &outstr);
				//int CompressEnd = GetTickCount();
				QueryPerformanceCounter(&qCouEnd);
				timeCost = (qCouEnd.QuadPart - qCouStart.QuadPart) / (double)qFreq.QuadPart;
				int compressFileSize = File::WriteStringToFileOrDie(outstr, compressFilePath.c_str());

				//out << binaryFileSize << "\t" << compressFileSize << "\t" << CompressEnd - CompressBegin << endl;
				out << binaryFileSize << "\t" << compressFileSize << "\t" << timeCost * 1000000 << endl;
			}
			out.close();
		}
		else {
			cout << "log file open error!!!" << endl;
		}

	}
	void uncompressSnappy(string compressDirPath, string uncompressDirPath, string logFilePrefixName) {
		time_t nowtime;
		nowtime = time(NULL); //Get current time  
		struct tm *local;
		local = localtime(&nowtime);  //Get current system time  
		string timeStr = to_string(local->tm_year + 1900) +
			"_" + to_string(local->tm_mon + 1) +
			"_" + to_string(local->tm_mday) +
			"_" + to_string(local->tm_hour) +
			"_" + to_string(local->tm_min) +
			"_" + to_string(local->tm_sec);

		string logFilePath = logFilePrefixName + timeStr + ".log";

		vector<string> fileList = File::folderTraversalSingleLayerName(compressDirPath);
		ofstream out(logFilePath, ios::trunc);
		if (out.is_open())
		{
			// Timing tool
			LARGE_INTEGER  qFreq, qCouStart, qCouEnd;
			double timeCost;
			for (string fileName : fileList) {
				string compressFilePath = compressDirPath + "\\" + fileName;
				string uncompressFilePath = uncompressDirPath + "\\" + fileName;
				ifstream fin(uncompressFilePath);
				if (fin) {
					fin.close();
					continue;
				}
				fin.close();
				string instr, outstr;

				int compressFileSize = File::ReadFileToStringOrDie(compressFilePath.c_str(), &instr);
				//int uncompressBegin = GetTickCount();
				QueryPerformanceFrequency(&qFreq);
				QueryPerformanceCounter(&qCouStart);
				snappy::Uncompress(instr.data(), instr.size(), &outstr);
				//int uncompressEnd = GetTickCount();
				QueryPerformanceCounter(&qCouEnd);
				timeCost = (qCouEnd.QuadPart - qCouStart.QuadPart) / (double)qFreq.QuadPart;
				int uncompressFileSize = File::WriteStringToFileOrDie(outstr, uncompressFilePath.c_str());

				//out << uncompressFileSize << "\t" << compressFileSize << "\t" << uncompressEnd - uncompressBegin << endl;
				out << uncompressFileSize << "\t" << compressFileSize << "\t" << timeCost * 1000000 << endl;
			}
			out.close();
		}
		else {
			cout << "log file open error!!!" << endl;
		}
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
		nowtime = time(NULL); //Get current time  
		struct tm *local;
		local = localtime(&nowtime);  //Get current system time  
		string timeStr = to_string(local->tm_year + 1900) +
			"_" + to_string(local->tm_mon + 1) +
			"_" + to_string(local->tm_mday) +
			"_" + to_string(local->tm_hour) +
			"_" + to_string(local->tm_min) +
			"_" + to_string(local->tm_sec);

		string logFilePath = logFilePrefixName + timeStr + ".log";

		vector<string> fileList = File::folderTraversalSingleLayerName(binaryDirPath);
		ofstream out(logFilePath, ios::trunc);
		if (out.is_open())
		{
			// Timing tool
			LARGE_INTEGER  qFreq, qCouStart, qCouEnd;
			double timeCost;
			for (string fileName : fileList) {
				string binaryFilePath = binaryDirPath + "\\" + fileName;
				string compressFilePath = compressDirPath + "\\" + fileName;
				ifstream fin(compressFilePath);
				if (fin) {
					fin.close();
					continue;
				}
				fin.close();
				string instr;

				int binaryFileSize = File::ReadFileToStringOrDie(binaryFilePath.c_str(), &instr);
				LZSS lzss;

				//FILE* outputFile = fopen(comFilePath.c_str(), "wb");
				//int CompressBegin = GetTickCount();
				//int compressFileSize = lzss.Compress((unsigned char*)instr.c_str(), instr.size(), outputFile);
				//int CompressEnd = GetTickCount();
				//fclose(outputFile);

				unsigned char *outstr = new unsigned char[instr.size() * 2];
				//int compressBegin = GetTickCount();
				QueryPerformanceFrequency(&qFreq);
				QueryPerformanceCounter(&qCouStart);

				int compressFileSize = lzss.Compress((unsigned char*)instr.c_str(), instr.size(), outstr);
				//int compressEnd = GetTickCount();
				QueryPerformanceCounter(&qCouEnd);
				timeCost = (qCouEnd.QuadPart - qCouStart.QuadPart) / (double)qFreq.QuadPart;
				File::WriteStringToFileOrDie(outstr, compressFilePath.c_str(), compressFileSize);
				delete outstr;

				out << binaryFileSize << "\t" << compressFileSize << "\t" << timeCost * 1000000 << endl;
			}
			out.close();
		}
		else {
			cout << "log file open error!!!" << endl;
		}
	}
	void uncompressLzss(string compressDirPath, string uncompressDirPath, string logFilePrefixName) {
		time_t nowtime;
		nowtime = time(NULL); //Get current time
		struct tm *local;
		local = localtime(&nowtime);  //Get current system time  
		string timeStr = to_string(local->tm_year + 1900) +
			"_" + to_string(local->tm_mon + 1) +
			"_" + to_string(local->tm_mday) +
			"_" + to_string(local->tm_hour) +
			"_" + to_string(local->tm_min) +
			"_" + to_string(local->tm_sec);

		string logFilePath = logFilePrefixName + timeStr + ".log";

		vector<string> fileList = File::folderTraversalSingleLayerName(compressDirPath);
		ofstream out(logFilePath, ios::trunc);
		if (out.is_open())
		{
			// Timing tool
			LARGE_INTEGER  qFreq, qCouStart, qCouEnd;
			double timeCost;
			for (string fileName : fileList) {
				string compressFilePath = compressDirPath + "\\" + fileName;
				string uncompressFilePath = uncompressDirPath + "\\" + fileName;
				ifstream fin(uncompressFilePath);
				if (fin) {
					fin.close();
					continue;
				}
				fin.close();
				string instr;

				int compressFileSize = File::ReadFileToStringOrDie(compressFilePath.c_str(), &instr);
				LZSS lzss;

				//FILE* outputFile = fopen(uncompressFilePath.c_str(), "wb");
				//int uncompressBegin = GetTickCount();
				//int uncompressFileSize = lzss.UnCompress((unsigned char*)instr.c_str(), instr.size(), outputFile);
				//int uncompressEnd = GetTickCount();
				//fclose(outputFile);

				unsigned char *outstr = new unsigned char[instr.size() * 2];
				//int uncompressBegin = GetTickCount();
				QueryPerformanceFrequency(&qFreq);
				QueryPerformanceCounter(&qCouStart);

				int uncompressFileSize = lzss.UnCompress((unsigned char*)instr.c_str(), instr.size(), outstr);
				//int uncompressEnd = GetTickCount();
				QueryPerformanceCounter(&qCouEnd);
				timeCost = (qCouEnd.QuadPart - qCouStart.QuadPart) / (double)qFreq.QuadPart;
				File::WriteStringToFileOrDie(outstr, uncompressFilePath.c_str(), uncompressFileSize);
				delete outstr;

				out << uncompressFileSize << "\t" << compressFileSize << "\t" << timeCost * 1000000 << endl;
			}
			out.close();
		}
		else {
			cout << "log file open error!!!" << endl;
		}
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
	int getMedian(vector<int>& nums) {
		return nums[nums.size() / 2];
	}

	void countCompressSizeFromLog(string compressLogFilePath, string countCompressLogFilePath, string valueRule) {
		int effectiveNum = 3;

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
				int saveValue;
				if (valueRule == "average") {
					saveValue = getAverage(compressSizeVec);
				}
				else {
					saveValue = getMedian(compressSizeVec);
				}
				output << my_Itr->first << "\t" << saveValue << "\t" << getAverage(timeVec) << endl;
			}
			output.close();
		}
		else {
			cout << "log file open error!!!" << endl;
		}
	}
	void countCompressSizeFromFile(string binaryDirPath, string compressDirPath, string logFilePrefixName) {
		time_t nowtime;
		nowtime = time(NULL); //Get current time  
		struct tm *local;
		local = localtime(&nowtime);  //Get current system time  
		string timeStr = to_string(local->tm_year + 1900) +
			"_" + to_string(local->tm_mon + 1) +
			"_" + to_string(local->tm_mday) +
			"_" + to_string(local->tm_hour) +
			"_" + to_string(local->tm_min) +
			"_" + to_string(local->tm_sec);

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

	int charToByte(char c) {
		return  hexIndexString.find(c);
	}
	char byteToChar(int b) {
		return  hexIndexString[b];
	}

	//十六进制字符串转换为字节流  
	void HexStrToByte(const char* source, char* dest, int sourceLen)
	{
		for (int i = 0; i < sourceLen; i += 2)
		{
			int high = charToByte(tolower(source[i]));
			int low = charToByte(tolower(source[i + 1]));

			dest[i / 2] = (char)((high << 4) | low);
		}
	}

	//字节流转换为十六进制字符串
	void ByteToHexStr(const char* dest, char* source, int destLen)
	{
		for (int i = 0; i < destLen; i++)
		{
			int num = dest[i];
			int high = (num >> 4) & 0xf;
			int low = num & 0xf;

			source[i * 2] = byteToChar(high);
			source[i * 2 + 1] = byteToChar(low);
		}
	}

	vector<string> getBlobStrVec(string docFilePath) {
		//string docFilePath = "D:\\data\\company work\\PDI\\test data\\2";
		string instr;

		int binaryFileSize = File::ReadFileToStringOrDie(docFilePath.c_str(), &instr);
		int startIndex = instr.find("m_dataBlob\": [");
		int endIndex = instr.find("],");
		string blobContent = instr.substr(startIndex + 15, endIndex - startIndex - 15);
		vector<string> blobStrVec;
		while (blobContent.find("\"") < blobContent.length()) {
			int start = blobContent.find("\"");
			blobContent = blobContent.substr(start + 1, blobContent.length() - start - 1);
			int end = blobContent.find("\"");
			blobStrVec.push_back(blobContent.substr(0, end));
			blobContent = blobContent.substr(end + 1, blobContent.length() - end - 1);
		}
		return blobStrVec;
	}

	void convertDocToBinary(const string& docDirPath, const string& binaryDirPath, const string& logFilePrefixName) {
		vector<string> fileList = File::folderTraversalSingleLayerName(docDirPath);
		for (string fileName : fileList) {
			string docFilePath = docDirPath + "\\" + fileName;
			string binaryFilePath = binaryDirPath + "\\" + fileName;
			ifstream fin(binaryFilePath);
			if (fin) {
				fin.close();
				continue;
			}
			fin.close();
			vector<string> blobStrVec = getBlobStrVec(docFilePath);
			ofstream out(binaryFilePath, ios::binary);
			if (out.is_open())
			{
				for (string blobStr : blobStrVec) {
					char *dst = new char[blobStr.length() / 2];
					HexStrToByte(blobStr.c_str(), dst, blobStr.length());
					for (int i = 0; i < blobStr.length() / 2; i++) {
						out << dst[i];
					}
					delete dst;
				}
				out.close();
			}

		}
	}
	void printDocContentBasedonBinary(const string& binaryFilePath) {
		string instr;
		File::ReadFileToStringOrDie(binaryFilePath.c_str(), &instr);
		char *dest = new char[instr.length() * 2 + 1];
		ByteToHexStr(instr.data(), dest, instr.length());
		dest[instr.length() * 2] = '\0';
		string outstr(dest);
		int start = 0;
		while (start < outstr.length()) {
			cout << outstr.substr(start, min(blobDataEachLen, outstr.length() - start)) << endl;
			start += blobDataEachLen;
		}
		delete dest;
	}
}