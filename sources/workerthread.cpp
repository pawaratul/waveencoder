#include <algorithm>

#include "logger.hpp"
#include "workerthread.hpp"

namespace waveEncoder
{
/*
    A constructor for workerThread thread class. It initializes all the variables
    and creates threads based no of cpu cores. The created threads are 
    made to wait on condtional variable untill command is available on queue.
    Also, since CPU load is not known, I have created 2 threads per core for 
    execution. The assumption is based on, If one thread is Blocked then schedular
    can fetch another thread to run and vice versa. 
*/
workerThread::workerThread(): m_noofthreads(0), m_istaskdone(false), m_taskcount(0)
{
    LOG("-->workerThread");   
    m_noofthreads = std::thread::hardware_concurrency() * 2; 
    m_threadstatus.resize(m_noofthreads, false);
    LOGI("workerThread - No of cores: ", m_noofthreads);
    for(uint8_t idx=0; idx<m_noofthreads-1;++idx)
    {
        m_threads.emplace_back([&](int thno)
        {
            while(m_istaskdone == false)
            {  
                std::unique_lock<std::mutex> lock(m_mtx);
                if(m_tasks.empty() == true)
                {
                    m_cv.wait(lock);
                }
                else
                {
                    m_threadstatus[thno] = true;
                    std::unique_ptr<command> task = std::move(m_tasks.front());
                    m_tasks.pop();
                    m_taskcount--;
                    lock.unlock();
                    task->run();
                }
                m_threadstatus[thno] = false;
            }
        }, idx);
    } 
    LOG("<--workerThread");
}
/*
    An interface which keeps main thread waiting until all the commands are 
    processed from queue. After all threads execution completed worker threads
    are set to exit
*/
void workerThread::wait()
{
    LOG("-->workerThread::wait");
    bool threadstatus = true;
    while(m_taskcount > 0 || threadstatus)
    {
        threadstatus = std::any_of(m_threadstatus.begin(), m_threadstatus.end(), [](bool status){ return status;});
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    m_istaskdone = true;
    m_cv.notify_all();
    for(uint8_t idx=0; idx<m_noofthreads-1;++idx)
    {
        if(m_threads[idx].joinable())
        {
            LOGI("workerThread - Closing thread  -", idx);
            m_threads[idx].join();
        }
    }
    m_threads.clear();
    LOG("<--workerThread::wait");

}

void workerThread::update()
{
    m_cv.notify_one();
    std::this_thread::yield();   
}

void workerThread::run(std::unique_ptr<command>& task)
{
    LOG("-->workerThread::run");
    std::unique_lock<std::mutex> lock(m_mtx);
    m_taskcount++;
    m_tasks.push(std::move(task));
    update();
    LOG("<--workerThread::run");
}
}   // waveEncoder
