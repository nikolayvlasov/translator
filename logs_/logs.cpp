/*
 * logs.cpp
 *
 *  Created on: 9 ����. 2019 �.
 *      Author: VlasovNV
 */
#include "logs.h"

void    Logs::write_to_file(const char*   str)
{
    try
	{
		file_out << str;
	}
	catch(const fstream::failure& ex)
	{
		std::cout << ex.what() <<endl;
        throw	Exeptions("can't write string in logs\n");
	}
}
void    Logs::write_to_file_id(uint64_t   id)
{
    try
	{
		file_out << "#" << id << endl;
	}
	catch(const fstream::failure& ex)
	{
		std::cout << ex.what() <<endl;
        throw	Exeptions("can't write id in logs\n");
	}
}

void    Logs::write_to_file_uint8(uint8_t   byte)
{
    try
    {
        file_out << (uint64_t)byte << endl;
    }
    catch(const fstream::failure& ex)
    {
        std::cout << ex.what() <<endl;
        throw	Exeptions("can't write uint8 in logs\n");
    }
}

