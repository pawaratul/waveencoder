#ifndef WAVEENCODER_AUDIOENCODER_H
#define WAVEENCODER_AUDIOENCODER_H
#include<string>

namespace waveEncoder
{

class audioEncoder
{
    public:
        explicit audioEncoder(std::string pWavefilename):m_Wavefilename(pWavefilename){ }
        void encodeWavToMp3();

    private:
        std::string m_Wavefilename;
};

}   // waveEncoder

#endif  // WAVEENCODER_AUDIOENCODER_H