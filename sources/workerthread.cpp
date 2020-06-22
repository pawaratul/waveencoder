#include <algorithm>

#include "logger.hpp"
#include "workerthread.hpp"

namespace waveEncoder
{
/*
    A constructor for workerThread thread class. It initializes all the variables
    and creates threads based no of cpu cores. The created threads are 
    made to wait on condtional variable untill task is available on queue.
    One main thread and one each thread is created for one core for better 
    execution. 
*/
workerThread::workerThread(): m_noofthreads(0), m_istaskdone(false), m_taskcount(0)
{
    m_noofthreads = std::thread::hardware_concurrency(); 
    m_threadstatus.resize(m_noofthreads, false);
    LOG_DEBUG("workerThread - No of cores: ", m_noofthreads);
    for(uint8_t idx=0; idx<m_noofthreads;++idx)
    {
        LOG_DEBUG("Created workerThread : ", idx);
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
}
/*
    An interface which keeps main thread waiting until all the commands are 
    processed from queue. After all threads execution completed worker threads
    are set to exit
*/
void workerThread::wait()
{
    bool threadstatus = true;
    while(m_taskcount > 0 || threadstatus)
    {
        threadstatus = std::any_of(m_threadstatus.begin(), m_threadstatus.end(), [](bool status){ return status;});
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    m_istaskdone = true;
    m_cv.notify_all();
    for(uint8_t idx=0; idx<m_noofthreads;++idx)
    {
        if(m_threads[idx].joinable())
        {
            LOG_DEBUG("Closing workerThread  : ", idx);
            m_threads[idx].join();
        }
    }
    m_threads.clear();
}

void workerThread::update()
{
    m_cv.notify_one();
    std::this_thread::yield();   
}

void workerThread::run(std::unique_ptr<command>& task)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_taskcount++;
    m_tasks.push(std::move(task));
    update();
}
}   // waveEncoder
