#ifndef WAVEENCODER_AUDIOCOMMAND_H
#define WAVEENCODER_AUDIOCOMMAND_H

#include"command.hpp"
#include"audioencoder.hpp"

namespace waveEncoder
{

class audioCommand : public command
{
    public:
        explicit audioCommand(std::string fname): m_Cmd(fname){}

        virtual void run() final  
        {
            m_Cmd.encodeWavToMp3();
        }
    private:
        audioEncoder m_Cmd;
}; 
} // waveEncoder

#endif  // WAVEENCODER_AUDIOCOMMAND_H