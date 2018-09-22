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
		ifstream in(inputFilePath, ios::binary);
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
		ofstream out(outputFilePath, ios::binary);
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

	long WriteStringToFileOrDie(unsigned char *data, const char* outputFilePath)
	{
		ofstream out(outputFilePath, ios::binary);
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

	void WriteStringToFileOrDie(unsigned char *data, const char* outputFilePath, const int& dataSize)
	{
		ofstream out(outputFilePath, ios::binary);
		if (out.is_open())
		{
			for (int i = 0; i < dataSize; i++) {
				out << *data++;

			}
			out.close();
		}
		else {
			cout << "write string to file has error, file path is \"" << outputFilePath << "\"." << endl;
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
}
