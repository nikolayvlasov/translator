#include "tcp_ip_client.h"

void Tcp_ip_client::readyRead()
{
    CONTAINER data = socket->readAll();
    CONTAINER::iterator iter;
    cout << "We recieve: ";
    for (iter = data.begin();iter < data.end();iter++)
    {
        cout << *iter << ", ";
    }
    cout << endl;
    response->push_back(data);
}

void Tcp_ip_client::execute()
{
    id++;
    write_to_file_id(id);
    write_to_file(":begin");
    write_to_file("\n");

    if(Is_connected)
    {
        socket->write(*request);
        socket->waitForReadyRead(READYREAD_PAUSE);
        CONTAINER::iterator iter;
        for (iter = request->begin();iter < request->end();iter++)
        {
            write_to_file_uint8(*iter);
        }
        request->clear();
    }

    write_to_file("end\n");
}

void Tcp_ip_client::connected()
{
    cout << "really connected!";
    socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
    socket->waitForReadyRead(READYREAD_PAUSE);
}

void Tcp_ip_client::disconnected()
{
    cout << "Disconnected!";
    Is_connected = false;
}

void Tcp_ip_client::bytesWritten(qint64 bytes)
{
    cout << "We wrote: " << bytes << endl;
}

Tcp_ip_client::~Tcp_ip_client()
{
    if(socket != nullptr)
    {
    delete socket;
    }
}
