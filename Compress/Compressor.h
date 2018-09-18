#pragma once

#ifndef _Compressor_H_ 
#define _Compressor_H_ 
#include <utility> 
#include <string> 

typedef unsigned int T_UI;

class Compressor
{
public:
	//Constructor 
	Compressor(const std::string &PATH, const T_UI minbytes = 3);

	/** GET BUFFERS **/
	std::string get_TEXT_FILE() const;
	std::string get_TEXT_ENCONDED() const;
	/** END GET BUFFERS **/

	void save_file_encoded();

private:
	/** BUFFERS **/
	std::string TEXT_FILE; // contains the text from an archive 
	std::string TEXT_ENCODED; // contains the text encoded 
	std::string W_buffer; // contains the string to analyze 
	std::string W_inspection; // contains the string where will search matches 
	/** END BUFFERS **/

	T_UI size_of_minbytes;
	T_UI size_w_insp; // The size of window inspection 
	T_UI actual_byte;

	std::pair< T_UI, T_UI> v_codes; // Values to code text 

	// Utilitaries functions 
	void change_size_insp() { size_w_insp = TEXT_FILE.length(); }
	bool inspection_empty() const;
	std::string convert_pair() const;
	// Encode algorythm 
	void lz77_encode();
};

#endif 