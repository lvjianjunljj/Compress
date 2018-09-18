#pragma once
#include "HuffmanTree1.hpp"
#include <Windows.h>
#include <iostream>
#pragma warning(disable:4996)
using namespace std;
struct CharInfo
{
	char _ch;
	int _count;
	string _code;

	CharInfo(unsigned char ch = 0)
		:_ch(ch)
		, _count(0)
	{}

	CharInfo operator+(const CharInfo& x)
	{
		CharInfo tmp;
		tmp._count = _count + x._count;
		return tmp;
	}

	bool operator!=(const CharInfo& x) const
	{
		return _count != x._count;
	}

	bool operator<(const CharInfo& x) const
	{
		return _count < x._count;
	}

};

template<class T>
class FileCompress
{
public:
	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_infos[i] = i;
		}
	}

	void Compress(const char* filename)
	{
		//assert(filename);

		FILE* fOutFile = fopen(filename, "rb");
		//assert(fOutFile);

		char ch = fgetc(fOutFile);

		int charCount = 0;//统计字符总数

		while (!feof(fOutFile))
		{
			++charCount;
			_infos[(unsigned char)ch]._count++;

			ch = fgetc(fOutFile);
		}

		//创建Huffman树
		CharInfo invalid(0);
		HuffmanTree<CharInfo> t(_infos, 256, invalid);
		//由Huffman树生成Huffman编码
		_GenerateHuffmanCode(t.GetRoot());

		//压缩
		string compressFilename = filename;
		compressFilename += ".compress";
		FILE* fInCompress = fopen(compressFilename.c_str(), "wb");
		//assert(fInCompress);

		fseek(fOutFile, 0, SEEK_SET);
		ch = fgetc(fOutFile);
		char value = 0;
		int size = 0;
		while (!feof(fOutFile))
		{
			string& code = _infos[(unsigned char)ch]._code;

			for (size_t i = 0; i < code.size(); ++i)
			{
				value <<= 1;

				if (code[i] == '1')
				{
					value |= 1;
				}

				++size;

				if (size == 8)
				{
					fputc(value, fInCompress);
					size = 0;
					value = 0;
				}
			}

			ch = fgetc(fOutFile);
		}

		if (size > 0)//补位
		{
			value <<= (8 - size);
			fputc(value, fInCompress);
		}

		// create configuration file to make it easy when uncompress.
		string configFilename = filename;
		configFilename += ".config";
		FILE* fInConfig = fopen(configFilename.c_str(), "wb");
		//assert(fInConfig);

		string line;
		char buffer[128];

		//将字符总数写入配置文件第一行
		line += itoa(charCount, buffer, 10);
		line += "\n";
		fputs(line.c_str(), fInConfig);
		line.clear();

		for (size_t i = 0; i < 256; ++i)
		{
			if (_infos[i]._count)
			{
				line += _infos[i]._ch;
				line += ',';
				line += itoa(_infos[i]._count, buffer, 10);
				line += '\n';

				fputs(line.c_str(), fInConfig);
			}

			line.clear();
		}

		fclose(fOutFile);
		fclose(fInCompress);
		fclose(fInConfig);
	}

	void UnCompress(const char* filename)
	{
		// read the configuration file
		string configFilename = filename;
		configFilename += ".config";
		FILE* fOutConfig = fopen(configFilename.c_str(), "rb");
		//assert(fOutConfig);

		string line;

		//read the sum number of char
		_ReadLine(fOutConfig, line);
		int charCount = atoi(line.c_str());
		line.clear();

		while (_ReadLine(fOutConfig, line))
		{
			if (!line.empty())
			{
				unsigned char ch = line[0];
				_infos[ch]._count = atoi(line.substr(2).c_str());

				line.clear();
			}
			else
			{
				line.clear();
				_ReadLine(fOutConfig, line);

				unsigned char ch = '\n';
				_infos[ch]._count = atoi(line.substr(1).c_str());

				line.clear();
			}
		}

		// rebuild the Huffman Tree
		CharInfo invalid(0);
		HuffmanTree<CharInfo> t(_infos, 256, invalid);

		//读.compress文件，写.uncompress文件
		string compressFilename = filename;
		compressFilename += ".compress";
		FILE* fOutCompress = fopen(compressFilename.c_str(), "rb");
		//assert(fOutCompress);

		string uncompressFilename = filename;
		uncompressFilename += ".uncompress";
		FILE* fInUncompress = fopen(uncompressFilename.c_str(), "wb");
		//assert(fInUncompress);``

		HuffmanTreeNode<CharInfo>* root = t.GetRoot();
		HuffmanTreeNode<CharInfo>* cur = root;

		int pos = 7;
		char ch = fgetc(fOutCompress);
		while (1)
		{
			if (ch & (1 << pos))
				cur = cur->_right;
			else
				cur = cur->_left;

			if (cur->_left == NULL && cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fInUncompress);

				cur = root;

				if (--charCount == 0)//字符已读取完，遇到补位的0不再读取
				{
					break;
				}
			}

			--pos;
			if (pos == -1)
			{
				ch = fgetc(fOutCompress);
				pos = 7;
			}
		}

		fclose(fOutCompress);
		fclose(fInUncompress);

	}


protected:
	void _GenerateHuffmanCode(HuffmanTreeNode<CharInfo>* root)
	{
		if (root == NULL)
			return;

		_GenerateHuffmanCode(root->_left);
		_GenerateHuffmanCode(root->_right);

		if (root->_left == NULL && root->_right == NULL)
		{
			HuffmanTreeNode<CharInfo>* cur = root;
			HuffmanTreeNode<CharInfo>* parent = root->_parent;
			string& code = _infos[(unsigned char)cur->_weight._ch]._code;

			while (parent)
			{
				if (parent->_left == cur)
					code += '0';
				if (parent->_right == cur)
					code += '1';

				cur = parent;
				parent = cur->_parent;
			}

			reverse(code.begin(), code.end());
		}

	}

	bool _ReadLine(FILE* filename, string& line)
	{
		char ch = fgetc(filename);

		if (ch == EOF)
			return false;

		while (ch != EOF && ch != '\n')
		{
			line += ch;
			ch = fgetc(filename);
		}

		return true;
	}

protected:
	CharInfo _infos[256];
};