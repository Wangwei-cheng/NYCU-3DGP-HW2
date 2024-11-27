//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 
#include <fstream>
#include <iostream>
#include <string>
#include "reader_config.h"

#define CONFIG_FILE_NAME	    "00_game_config.txt"
#define Default_Data_File_Name  "00_game_data_01.txt"


using namespace std;

std::string READER_CONFIG::mDataFileName = Default_Data_File_Name;


READER_CONFIG::READER_CONFIG()
{

}


bool READER_CONFIG::readData()
{
	cout << "Begin READER_CONFIG::readData()" << endl;

	bool flgOK = false;
	using namespace std;
	std::ifstream* fp;
	fp = new std::ifstream(CONFIG_FILE_NAME, ios::in | ios::binary);
	if (fp == 0 || fp->fail()) {
		cout << "Cannot open data file:" << CONFIG_FILE_NAME << endl;
		return flgOK;
	}

	std::string key;
	double value;
	std::string vstring;
	while (!fp->eof()) {
		*fp >> key;

		cout << "Reading:" << key << endl;

		if (key.compare("GAME_DATA_FILE") == 0) {	// check the tag.
			*fp >> mDataFileName;					// read the following value that is a string.

			flgOK = true;
		}
		//////////////////////////////////////////////
		key.clear(); // clear the key content
		//////////////////////////////////////////////
	}
	report();
	cout << "End READER_DATA::readData()" << endl;

	return flgOK;
}

void READER_CONFIG::report()
{
	cout << "Begin READER_CONFIG::report()" << endl;
	cout << "mDataFileName:\t" << mDataFileName << endl;
	cout << "End READER_DATA::report()" << endl;
}


std::string READER_CONFIG::getDataFileName()
{
	return mDataFileName;
}