#include <iostream>  
#include <stdio.h>
#include<stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <io.h>
#include <time.h>
#include "snappy.h"
#include "file.h" 
#include "FileCompress1.hpp"
#include "FileCompress2.h"
#include "Compressor.h" 
#include "lzss.h"
using namespace std;

void testSnappyCompress() {
	string inputDirPath = "D:\\data\\company work\\PDI\\test data\\CaptionDocumentBinary";
	string outputDirPath = "D:\\data\\company work\\PDI\\test data\\CaptionDocumentCompressSnappy";

	time_t nowtime;
	nowtime = time(NULL); //获取当前时间  
	cout << nowtime << endl;
	struct tm *local, *gm;
	local = localtime(&nowtime);  //获取当前系统时间  
	string timeStr = to_string(local->tm_year + 1900) + 
		"_" + to_string(local->tm_mon + 1) +
		"_" + to_string(local->tm_mday) +
		"_" + to_string(local->tm_hour) +
		"_" + to_string(local->tm_min) +
		"_" + to_string(local->tm_sec);

	string logFilePath = "D:\\data\\company work\\PDI\\test data\\compress data statistics\\caption_snappy_compress_" +
		timeStr + ".log";

	vector<string> fileList = File::folderTraversalSingleLayerName(inputDirPath);
	ofstream out(logFilePath, ios::trunc);
	if (out.is_open())
	{
		for (string fileName : fileList) {
			string binaryFielPath = inputDirPath + "\\" + fileName;
			string comFielPath = outputDirPath + "\\" + fileName;
			ifstream fin(comFielPath);
			if (fin) {
				fin.close();
				continue;
			}
			fin.close();
			string instr, outstr;

			int CompressBegin = GetTickCount();
			int binaryFileSize = File::ReadFileToStringOrDie(binaryFielPath.c_str(), &instr);
			snappy::Compress(instr.data(), instr.size(), &outstr);
			int compressFileSize = File::WriteStringToFileOrDie(outstr, comFielPath.c_str());
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
	const char* unComFielName = "D:\\data\\company work\\PDI\\test data\\1_compress";
	const char* toComFileName = "D:\\data\\company work\\PDI\\test data\\1__uncomress";

	string instr, outstr;

	int unCompressBegin = GetTickCount();
	File::ReadFileToStringOrDie(unComFielName, &instr);
	snappy::Uncompress(instr.data(), instr.size(), &outstr);
	File::WriteStringToFileOrDie(outstr, toComFileName);
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
	const char* comFielName = "D:\\data\\company work\\PDI\\test data\\1";
	const char* unComFielName = "D:\\data\\company work\\PDI\\test data\\1_compress";

	int CompressBegin = GetTickCount();
	FileCompress2::Compress(comFielName, unComFielName);
	int CompressEnd = GetTickCount();
	cout << "Compress time cost: " << CompressEnd - CompressBegin << " ms" << endl;

}

void testHuffmanUncompress2()
{
	const char* unComFielName = "D:\\data\\company work\\PDI\\test data\\1_compress";
	const char* toComFileName = "D:\\data\\company work\\PDI\\test data\\1_uncompress";

	int UncompressBegin = GetTickCount();
	FileCompress2::UnCompress(unComFielName, toComFileName);
	int UncompressEnd = GetTickCount();
	cout << "Uncompress time cost: " << UncompressEnd - UncompressBegin << " ms" << endl;
}
void  testLz77() {
	Compressor c("/home/facu/text.txt", 3);
	std::cout << c.get_TEXT_FILE() << std::endl;
	std::cout << c.get_TEXT_ENCONDED() << std::endl;
	c.save_file_encoded();
}

void testLzssCompress() {
	string inputDirPath = "D:\\data\\company work\\PDI\\test data\\CaptionDocumentBinary";
	string outputDirPath = "D:\\data\\company work\\PDI\\test data\\CaptionDocumentCompressLzss";
	string logFilePath = "D:\\data\\company work\\PDI\\test data\\compress data statistics\\caption_lzss_compress_log.txt";

	vector<string> fileList = File::folderTraversalSingleLayerName(inputDirPath);
	ofstream out(logFilePath, ios::trunc);
	if (out.is_open())
	{
		for (string filePath : fileList) {
			string comFielName = inputDirPath + "\\" + filePath;
			string unComFielName = outputDirPath + "\\" + filePath;

			string instr, outstr;

			int CompressBegin = GetTickCount();
			int binaryFileSize = File::ReadFileToStringOrDie(comFielName.c_str(), &instr);
			LZSS lzss;
			FILE* outputFile = fopen(unComFielName.c_str(), "wb");
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
	const char* unComFielName = "D:\\data\\company work\\PDI\\test data\\1_compress_lzss";
	const char* toComFileName = "D:\\data\\company work\\PDI\\test data\\1_uncompress_lzss";

	string instr, outstr;
	int unCompressBegin = GetTickCount();
	File::ReadFileToStringOrDie(unComFielName, &instr);
	LZSS lzss;
	lzss.UnCompress((unsigned char*)instr.c_str(), instr.size(), fopen(toComFileName, "wb"));
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

void testReadLog() {
	int effectiveNum = 3;
	string compressLogFilePath = "D:\\data\\company work\\PDI\\test data\\compress data statistics\\caption_lzss_compress_log.txt";
	string countCompressLogFilePath = "D:\\data\\company work\\PDI\\test data\\compress data statistics\\caption_lzss_compress_log_count.txt";

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
			output << to_string(my_Itr->first) << "\t" << to_string(getAverage(compressSizeVec)) << "\t" << to_string(getAverage(timeVec)) << endl;
		}
		output.close();
	}
	else {
		cout << "log file open error!!!" << endl;
	}
}
void test() {
	// Check for existence.  
	if ((_access("crt_ACCESS.C", 0)) != -1)
	{
		printf_s("File crt_ACCESS.C exists.\n");

		// Check for write permission.  
		// Assume file is read-only.  
		if ((_access("crt_ACCESS.C", 2)) == -1)
			printf_s("File crt_ACCESS.C does not have write permission.\n");
	}

}
void dsptime(const struct tm * ptm)
{
	cout << ptm->tm_year + 1900 << "年" << ptm->tm_mon + 1 << "月" << ptm->tm_mday << "日 ";
	cout << ptm->tm_hour << ":" << ptm->tm_min << ":" << ptm->tm_sec << " ";
	cout << " 星期" << ptm->tm_wday << " 当年的第" << ptm->tm_yday << "天 " << endl;
}
int main() {
	//testSnappyCompress();
	//testSnappyUncompress();
	//testHuffmanCompress1();
	//testHuffmanUncompress1();
	//testHuffmanCompress2();
	//testHuffmanUncompress2();
	//testLzssCompress();
	//testLzssUncompress();
	//testReadLog();
	time_t nowtime;
	nowtime = time(NULL); //获取当前时间  
	cout << nowtime << endl;
	struct tm *local, *gm;
	local = localtime(&nowtime);  //获取当前系统时间  
	dsptime(local);
	gm = gmtime(&nowtime);  //获取格林尼治时间  
	dsptime(gm);
	system("pause");
	return 0;
}
