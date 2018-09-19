#include "file.h"  
#include <string>  
#include <fstream>
#include <iostream>
#include <sstream> 
#include <io.h>
#pragma warning(disable:4996)

namespace File
{
	long ReadFileToStringOrDie(const char* inputFilePath, string* data)
	{
		ifstream in(inputFilePath, ios::in);
		if (in.is_open()) {
			stringstream buffer;
			buffer << in.rdbuf();
			data->append(buffer.str());
			long fileSize = in.tellg();
			in.close();
			return fileSize;
		}
		else {
			return -1;
		}
	}

	long WriteStringToFileOrDie(const string& data, const char* outputFilePath)
	{
		ofstream out(outputFilePath, ios::trunc);
		if (out.is_open())
		{
			out << data;
			long fileSize = out.tellp();
			out.close();
			return fileSize;
		}
		else {
			return -1;
		}
	}

	struct
	{
		unsigned attrib;
		time_t time_create;
		time_t time_access;
		time_t time_write;
		_fsize_t size;
		char name[_MAX_FNAME];
	} _finddata_t;

	// Traverse all files under the folder
	vector<string> folderTraversalSingleLayerName(string dirPath) {
		vector<string> fileVec;
		std::string folderPath = dirPath + "\\*";
		//Handle for lookup
		long handle;
		struct _finddata_t fileinfo;
		//The first search
		handle = _findfirst(folderPath.c_str(), &fileinfo);
		if (handle == -1)
			return fileVec;
		do
		{
			string fileName = fileinfo.name;
			if (fileName == "." || fileName == "..") {
				continue;
			}
			//Add the file name of the found file
			fileVec.push_back(fileName);
		} while (!_findnext(handle, &fileinfo));

		_findclose(handle);
		return fileVec;
	}
	map<string, int> folderTraversalSingleLayerNameSize(string dirPath) {
		map<string, int> fileMap;
		std::string folderPath = dirPath + "\\*";
		//Handle for lookup
		long handle;
		struct _finddata_t fileinfo;
		//The first search
		handle = _findfirst(folderPath.c_str(), &fileinfo);
		if (handle == -1)
			return fileMap;
		do
		{
			string fileName = fileinfo.name;
			if (fileName == "." || fileName == "..") {
				continue;
			}
			//Add the file name of the found file
			fileMap[fileName] = fileinfo.size;
		} while (!_findnext(handle, &fileinfo));

		_findclose(handle);
		return fileMap;
	}

	//// Useless function
	//void Txt2BinaryFail(const char* inputFilePath, const char* outputFilePath)
	//{
	//	string data = "";
	//	FILE* fp = fopen(inputFilePath, "r");
	//	if (fp == NULL)
	//	{
	//		perror(inputFilePath);
	//		exit(1);
	//	}

	//	while (!feof(fp))
	//	{
	//		char buf[4096];
	//		size_t ret = fread(buf, 1, 4096, fp);
	//		if (ret == 0 && ferror(fp))
	//		{
	//			perror("fread");
	//			exit(1);
	//		}
	//		data.append(string(buf, ret));
	//	}
	//	cout << data << endl;
	//	fclose(fp);

	//	ofstream ofs;
	//	ofs.open(outputFilePath, ios::out | ios::binary);
	//	if (!ofs.is_open())
	//	{
	//		cout << "open out file fail!" << endl;
	//		return;
	//	}
	//	ofs.write(data.c_str(), strlen(data.c_str()));
	//	ofs.close();
	//}

	//// Useless function 
	//void Txt2Binary(const char* inputFilePath, const char* outputFilePath)
	//{
	//	FILE *fp;

	//	string data = "";
	//	fp = fopen(inputFilePath, "r");
	//	if (fp == NULL)
	//	{
	//		perror(inputFilePath);
	//		exit(1);
	//	}

	//	while (!feof(fp))
	//	{
	//		char buf[4096];
	//		size_t ret = fread(buf, 1, 4096, fp);
	//		if (ret == 0 && ferror(fp))
	//		{
	//			perror("fread");
	//			exit(1);
	//		}
	//		data.append(string(buf, ret));
	//	}
	//	cout << data << endl;
	//	fclose(fp);

	//	//fp = fopen("D:\\data\\company work\\PDI\\test data\\3test", "wt");
	//	//fprintf(fp, "%d", i);
	//	//fclose(fp);

	//	fp = fopen(outputFilePath, "wb");
	//	fwrite(&data, sizeof(data), 1, fp);
	//	fclose(fp);
	//	fp = fopen("D:\\data\\company work\\PDI\\test data\\3_binary2", "wt");
	//	fprintf(fp, "%d", data);
	//	fclose(fp);
	//}
}
