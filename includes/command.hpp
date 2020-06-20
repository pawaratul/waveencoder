#ifndef WAVEENCODER_COMMAND_H
#define WAVEENCODER_COMMAND_H

#include<memory>

namespace waveEncoder
{

class command
{
public:
    virtual ~command(){};
    virtual void run() = 0;
};

}   // waveEncoder

#endif  // WAVEENCODER_COMMAND_H