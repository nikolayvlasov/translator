#ifndef TCP_IP_CLIENT_H
#define TCP_IP_CLIENT_H
#include <headers.h>

class Tcp_ip_client: public QObject, Logs
{
    Q_OBJECT
public:
    explicit Tcp_ip_client(CONTAINER& req, CONTAINER& resp, bool& c):Logs("Tcp_ip_client.txt"),request(&req),response(&resp)
    {
        cycle = &c;
        socket = new QTcpSocket (this);
        connect(socket, SIGNAL(connected()), this, SLOT(connected()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
        socket->connectToHost(TCP_IP, TCP_PORT);
        if(socket->waitForConnected(3000))
        {
            cout << "connect to server" << endl;
            Is_connected = true;
        }
        else
        {
            cout << "error connect to server" << endl;
            if(socket != nullptr)
            {
                socket->close();
            }
            Is_connected = false;
            *cycle = false;
        }

    }
    Tcp_ip_client() = delete;
    Tcp_ip_client(Tcp_ip_client&) = delete;
    void operator = (Tcp_ip_client&) = delete;
    void execute();
    ~Tcp_ip_client();

public slots:
    void    connected();
    void    disconnected();
    void    bytesWritten(qint64 bytes);
    void    readyRead();
private:
    CONTAINER* request;
    CONTAINER* response;
    uint64_t    id = 0;
    QTcpSocket*  socket;
    bool    Is_connected;
    bool*    cycle;


};

#endif // TCP_IP_CLIENT_H
