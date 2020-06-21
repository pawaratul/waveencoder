#ifndef WAVEENCODER_LOGGER_H
#define WAVEENCODER_LOGGER_H

#include<iostream>
#include<thread>
#include<mutex>

#define LOG(msg)  waveencoder::logger::get().log(msg)
#define LOGI(msg, v)  waveencoder::logger::get().log(msg, v)

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
#if INFO        
        mtx.lock();
        std::cout << "0x" << std::hex << std::this_thread::get_id() << " : " << str << std::endl;
        mtx.unlock();
#endif
    }

    void log(std::string str, uint64_t v)
    {
#if DEBUG        
        mtx.lock();
        std::cout << __TIME__ << " : " << str << int64_t(v) << std::endl;

        // std::cout << "0x" << std::hex << std::this_thread::get_id() << " : " << str << v << std::endl;
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
