#ifndef SHEDULER_H
#define SHEDULER_H
#include "headers.h"
#include "tcp_ip_client/tcp_ip_client.h"

using namespace std;

class My_thread
{
    public:
        My_thread(){cout << "My_thread" << endl;}
        virtual void    run() = 0;
        virtual void    stop() = 0;
        virtual ~My_thread(){cout << "~My_thread" << endl;}
};

class	tcp_ip_task: public My_thread, Logs
{
   public:
    tcp_ip_task(const char* s, QMutex& mutex, CONTAINER& req, CONTAINER& resp):Logs("tcp_ip_task.txt"), str(s)
   {
        cout << "tcp_ip_task" << endl;
        request = &req;
        response = &resp;
        mtx = &mutex;
        cycle = true;
        tcp_ip = new Tcp_ip_client(*request, *response, cycle);
   }
    void run();
    void stop();
    ~tcp_ip_task();
    tcp_ip_task() = delete;
    tcp_ip_task(tcp_ip_task&) = delete;
    void operator = (tcp_ip_task&) = delete;

   protected:
    const char*    str = "Hello";
    CONTAINER*    request = nullptr;
    CONTAINER*	response = nullptr;
    QMutex* mtx;
    uint64_t    id = 0;
    bool    cycle;
    Tcp_ip_client* tcp_ip;
};


class	my_task2: public My_thread, public Logs
{
    public:
    my_task2(const char* s, QMutex& mutex, CONTAINER &req, CONTAINER &resp): Logs("task2.txt"), str(s)
   {
        cout << "my_task2" << endl;
        request = &req;
        response = &resp;
        mtx = &mutex;
        cycle = true;
   }
    void run();

    void stop();
    ~my_task2(){cout << "~my_task2" << endl;}
    my_task2() = delete;
    my_task2(my_task2&) = delete;
    void operator = (my_task2&) = delete;

   protected:
    const char*    str = "world";
    CONTAINER*    request = nullptr;
    CONTAINER*	response = nullptr;
    QMutex* mtx;
    uint64_t    id = 0;
    bool    cycle;
};

typedef enum{tcp_ip_client, converter} Thread_types;

class Thread_worker : public QObject
{
    Q_OBJECT

    private:
        Thread_types thr_type;
        My_thread*   my_thr;
        QMutex* mtx;
        CONTAINER*  request = nullptr;
        CONTAINER*	response = nullptr;

    public:
        Thread_worker(Thread_types thr_t, QMutex &mutex, CONTAINER &req, CONTAINER &resp):thr_type(thr_t),my_thr(nullptr)
        {
            request = &req;
            response = &resp;
            mtx = &mutex;
            cout << "Thread_worker" << endl;
        }
        ~Thread_worker()
        {
            cout << "~Thread_worker" << endl;
            if(my_thr != nullptr)
            {
                delete my_thr;
            }
        }
        Thread_worker() = delete;
        Thread_worker(Thread_worker&) = delete;
        void operator = (Thread_worker&) = delete;

    public slots:
        void    process();

        void    stop();

    signals:
        void    finished();
};



class Session: public QObject
{
    Q_OBJECT

    public:
        Session(QCoreApplication& a)
        {
            app = &a;
            threads_number = 0;
            cout << "Session" << endl;
            cout << "add tcp/ip client" << endl;
            addThread(tcp_ip_client);
            cout << "add converter" << endl;
            addThread(converter);
        }
        uint64_t    get_threads_number();
        ~Session()
        {
            cout << "~Session" << endl;
        }
public slots:
        void reduce_threads();

signals:
        void    stop_all();

    private:
        CONTAINER request;
        CONTAINER response;
        QMutex  mtx;
        void    stopThreads();
        void    addThread(Thread_types thr_t);
        uint64_t threads_number;
        QCoreApplication* app;
};

#endif // SHEDULER_H
