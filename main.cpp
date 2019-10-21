/*
 * main.cpp
 *
 *  Created on: 11 ����. 2019 �.
 *      Author: VlasovNV
 */
#include "scheduler/scheduler.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    try
	{

	cout << "Congratulation program is begin" << endl;

    Session create(a);
    return a.exec();
    }
	catch(std::exception& e)
	{
	     std::cerr<<"error occurred. error text is :\"" <<e.what()<<"\"\n";
	     return 1;
    }
}


