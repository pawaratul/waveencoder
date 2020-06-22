#ifndef WAVEENCODER_LOGGER_H
#define WAVEENCODER_LOGGER_H

#include<iostream>
#include<thread>
#include<mutex>

#define LOG(msg)  waveencoder::logger::get().log(msg)
#define LOG_DEBUG(msg, v)  waveencoder::logger::get().log(msg, v)

namespace waveencoder
{

/*
    The logger is singleton class which exposes 2 interface. It prints the thread id
    under execution along with given string and integer information
*/
class logger
{
public:
    static logger& get() {
    static logger instance;
    return instance;
  }

    void log(std::string str)
    {        
        mtx.lock();
        std::cout << __TIME__ << " - " << str << std::endl;
        mtx.unlock();
    }

    void log(std::string str, uint64_t v)
    {
#if DEBUG        
        mtx.lock();
        std::cout << __TIME__ << " - " << str << v << std::endl;
        mtx.unlock();
#endif        
    }
private:
    logger() = default;
    ~logger() = default;
    logger(const logger&) = delete;
    logger& operator=(const logger&) = delete;
    std::mutex mtx;
};

}

#endif // WAVEENCODER_LOGGER_H
