#if defined(__linux__) ||  defined(__CYGWIN__)
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#endif

#include "audiocommand.hpp"
#include "logger.hpp"
#include "workerthread.hpp"

#if DEBUG
class runtimer
{
    public:
    std::chrono::high_resolution_clock::time_point start;
    runtimer() : start(std::chrono::high_resolution_clock::now()){}
    ~runtimer()
    {
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        LOG_DEBUG("Total execution time :", std::chrono::duration_cast<std::chrono::seconds>(end-start).count());
    }
};
#endif
/*
    main function accepts a directory contaning waves audiofiles.
    It creates an audiocommand with each wave file and gives to 
    workerthread to run the command.
    The posix directory referrence is used for accessing directory.  
*/
int main(int argc, char **argv)
{
    int ret = EXIT_SUCCESS;
        
    if(argc == 2)
    {
#if DEBUG        
        runtimer t1;
#endif
        std::string dirPath(argv[1]);
        std::string fileName;
        LOG("Encoding application started");
#if defined(__linux__) || defined(__CYGWIN__)        
        DIR *dirp = opendir(dirPath.c_str());

        if(dirp != nullptr)
        {
            dirent *file;
            waveEncoder::workerThread threadPool;

            while((file = readdir(dirp)) != nullptr)
            {
                char *pos = strrchr(file->d_name, int('.')); 
                if( pos != nullptr)
                {
                    if(strcmp(pos, ".wav") == 0)
                    {
                        if(dirPath.back() == '/') 
                        {
                            fileName = dirPath + file->d_name;
                        }
                        else
                        {
                            fileName = dirPath + '/' + file->d_name;
                        }
                        std::unique_ptr<waveEncoder::command> command = std::make_unique<waveEncoder::audioCommand>(fileName);
                        threadPool.run(command);
                    }
                }
            }
            threadPool.wait();
        }
#endif
    }
    else
    {
        LOG("Error : No input argument");
        ret = EXIT_FAILURE;
    }
    LOG("Closing encoding application");
    return ret;
}
