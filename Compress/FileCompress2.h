#pragma once
#include <string>

namespace FileCompress2
{
	void Compress(const std::string &InputFilePath, const std::string &OutputFilePath);
	void UnCompress(const std::string &InputFilePath, const std::string &OutputFilePath);
};