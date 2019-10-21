#include "scheduler.h"

void tcp_ip_task::run()
{
    while(cycle)
    {
        mtx->lock();
        id++;
        cout << "1 begin #" << id << endl;
        tcp_ip->execute();
        cout << "1 end #" << id << endl;
        mtx->unlock();
    }
}

void tcp_ip_task::stop()
{
    cycle = false;
}

tcp_ip_task::~tcp_ip_task()
{
    cout << "~tcp_ip_task" << endl;
    if(tcp_ip != nullptr)
    {
        delete tcp_ip;
    }
}

void my_task2::run()
{
    while(cycle)
    {
        mtx->lock();
        id++;
        cout << "2 begin #" << id <<  endl;
        write_to_file_id(id);
        write_to_file(str);
        write_to_file(":begin");
        write_to_file("\n");

        request->append("4");
        request->append("5");
        request->append("6");
        request->append("7");

        CONTAINER::iterator iter;
        for (iter = response->begin();iter < response->end();iter++)
        {
            write_to_file_uint8(*iter);
        }
        response->clear();

        cout << "2 end #" << id << endl;
        write_to_file("end");
//      cycle = false;
        mtx->unlock();
    }
}

void my_task2::stop()
{
    cycle = false;
}

void Thread_worker::process()
{
    if  (thr_type == tcp_ip_client)
    {
        cout << "create tcp_ip_task" << endl;
        my_thr = new tcp_ip_task("bad idea", *mtx, *request, *response);
    }

    if  (thr_type == converter)
    {
        cout << "create my_task2" << endl;
        my_thr = new my_task2("well", *mtx, *request, *response);
    }
    if  (my_thr != nullptr)
    {
    cout << "run" << endl;
    my_thr->run();
    }
    cout << "finished" << endl;
    emit    finished();
    return;
}

void Thread_worker::stop()
{
    if(my_thr != nullptr)
    {
        my_thr->stop();
    }
    return;
}

uint64_t Session::get_threads_number()
{
    return threads_number;
}

void Session::reduce_threads()
{
    if(threads_number > 1)
    {
        threads_number--;
    }
    else
    {
        emit    stop_all();
    }
}

void Session::stopThreads()
{
    emit    stop_all();
}

void Session::addThread(Thread_types thr_t)
{
    Thread_worker* worker = new Thread_worker(thr_t, mtx, request, response);
    QThread*    thread = new QThread;
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(this, SIGNAL(stop_all()), worker, SLOT(stop));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(this, SIGNAL(stop_all()), app, SLOT(quit()));
    connect(thread, SIGNAL(finished()), this, SLOT(reduce_threads()));
    thread->start();
    threads_number++;
    return;
}
