//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 
//header guard
#ifndef __READER_CONFIG_H__
#define __READER_CONFIG_H__

#include <string>

/**
 * READER_CONFIG reads a config file which stores a game data file name.
 *
 */
class READER_CONFIG {
protected:

	/**
	* mDataFileName stores the data file name.
	*/
	static std::string mDataFileName;
public:

	/**
	* No-arg constructor.
	*/
	READER_CONFIG();

	/**
	* This function reads data from a data file whose file name is stored in mDataFileName.
	*/
	static bool readData();

	/**
	*This function reports the content.
	*/
	static void report();

	/**
	*This function returns the data file name.
	*/
	static std::string getDataFileName();
};

#endif