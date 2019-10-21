/*
 * logs.h
 *
 *  Created on: 9 ����. 2019 �.
 *      Author: VlasovNV
 */

#ifndef LOGS_H_
#define LOGS_H_
#include "../headers.h"
using namespace	std;

class	Logs
{
	public:
		Logs(const char*    f_name = "logs.txt"):file_name(f_name)
		{
			file_out.exceptions(fstream::failbit | fstream::badbit);
			try
			{
				file_out.open(file_name, ios::out);
			}
			catch(const fstream::failure& ex)
			{
				std::cout << ex.what() <<endl;
				throw	Exeptions("can't open log file\n");
			}
        }

		class	Exeptions
		{
		public:
			Exeptions(const	char*	ex_str = ""):ex_string(ex_str)
			{
			}
			const	char*    what()
			{
				return ex_string;
			}
		protected:
			const	char*	ex_string;
		};

		void    write_to_file(const char*    str);
		void    write_to_file_id(uint64_t    id);
        void    write_to_file_uint8(uint8_t    byte);

		~Logs()
		{
            file_out.close();
        }
	protected:
		fstream   file_out;
		const	char*    file_name;
};



#endif /* LOGS_H_ */
