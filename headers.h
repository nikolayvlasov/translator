/*
 * headers.h
 *
 *  Created on: 4 ����. 2019 �.
 *      Author: VlasovNV
 */

#ifndef HEADERS_H_
#define HEADERS_H_

#define COMM_ONCD_BUFFER_SIZE 0x10000
#define COMM_ONCD_FRAME_SIZE 148
#define COMM_MEM_BUFFER_SIZE 0x1000
#define COMM_MEM_FRAME_SIZE 20
#define RESP_ONCD_BUFFER_SIZE 0x10000
#define RESP_ONCD_FRAME_SIZE 128
#define RESP_MEM_BUFFER_SIZE 0x1000
#define RESP_MEM_FRAME_SIZE 9

#include <QObject>
#include <QStack>
#include <QString>
#include <QThread>
#include <QMutex>
#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <QtNetwork>
#include "logs_/logs.h"

#define CONTAINER QByteArray
#define TCP_NICKNAME "nick"
#define TCP_IP QHostAddress::LocalHost//"192.168.0.43"//
#define TCP_PORT 7777
#define READYREAD_PAUSE 100




#endif /* HEADERS_H_ */
