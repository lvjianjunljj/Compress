#include <iostream> 

#include <fstream> 
using std::ifstream;
using std::ofstream;

#include <string> 

#include <cstdlib> 

#include <sstream> 

#include "Compressor.h" 

Compressor::Compressor(const std::string& PATH, const T_UI minbytes)
{
	std::string buffer = "";
	TEXT_FILE = "";
	ifstream input_text(PATH.c_str(), std::ios::in);
	if (!input_text)
	{
		std::cerr << "Can't open the text file";
		std::exit(1);
	}
	while (!input_text.eof())
	{
		std::getline(input_text, buffer);
		TEXT_FILE += buffer;
		TEXT_FILE += "\n";
		buffer.clear();
	}
	input_text.close();
	change_size_insp();
	size_of_minbytes = minbytes;
	TEXT_ENCODED = "";
	W_buffer = "";
	W_inspection = "";
	v_codes.first = 0;
	v_codes.second = 0;
	actual_byte = 0;
	lz77_encode();
}

std::string Compressor::get_TEXT_FILE() const
{
	return TEXT_FILE;
}

std::string Compressor::get_TEXT_ENCONDED() const
{
	return TEXT_ENCODED;
}

bool Compressor::inspection_empty() const
{
	return (size_w_insp != 0);
}

std::string Compressor::convert_pair() const
{
	std::stringstream out;
	out << v_codes.first;
	out << "|";
	out << v_codes.second;
	return out.str();
}

void Compressor::save_file_encoded()
{
	std::string path("/home/facu/encoded.txt");
	ofstream out_txt(path.c_str(), std::ios::out);
	out_txt << TEXT_ENCODED << "\n";
	out_txt.close();
}

void Compressor::lz77_encode()
{
	while (inspection_empty())
	{
		W_buffer = TEXT_FILE.substr(actual_byte, 1);
		if (W_inspection.find(W_buffer) == W_inspection.npos)
		{
			// Cant find any byte from buffer 
			TEXT_ENCODED += W_buffer;
			W_inspection += W_buffer;
			W_buffer.clear();
			++actual_byte;
			--size_w_insp;
		}
		else
		{
			// We founded any byte from buffer in inspection 
			v_codes.first = W_inspection.find(W_buffer);
			v_codes.second = 1;
			while (W_inspection.find(W_buffer) != W_inspection.npos)
			{
				++actual_byte;
				--size_w_insp;
				v_codes.second++;
				W_inspection += TEXT_FILE[actual_byte - 1];
				W_buffer += TEXT_FILE[actual_byte];
			}
			++actual_byte;
			--size_w_insp;
			if (v_codes.second > size_of_minbytes)
				TEXT_ENCODED += convert_pair();
			else
				TEXT_ENCODED += W_buffer;
			W_buffer.clear();
		}
	}
}