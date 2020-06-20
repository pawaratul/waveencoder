#ifndef WAVEENCODER_WORKERTHREAD_H
#define WAVEENCODER_WORKERTHREAD_H

#include<condition_variable>
#include<mutex>
#include<queue>
#include<thread>
#include<vector>

#include "command.hpp"

namespace waveEncoder
{

/*
    The workerThread class is handler class for pool of thread. It exposes inteface 
    "run" and "wait" for the client.
    It creates thread number of  threads based on cpu cores and process all the 
    commands available in queue. It also executes all the commands in the queue 
    untill all the commands processed. After processing all the commands based on 
    client requests it closes all the threads   
*/
class workerThread
{
    public:
        workerThread();
        void wait();
        void run(std::unique_ptr<command> &task);
    private:
        void update();
        uint m_noofthreads;
        bool m_istaskdone;
        std::queue<std::unique_ptr<command>> m_tasks;
        std::vector<std::thread> m_threads;
        std::vector<bool>m_threadstatus;
        std::mutex m_mtx;
        std::condition_variable m_cv;
        uint16_t m_taskcount;
};

}   //  waveEncoder

#endif  // WAVEENCODER_WORKERTHREAD_H
