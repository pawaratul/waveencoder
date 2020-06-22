#include "audioencoder.hpp"
#include "lame/lame.h"
#include "logger.hpp"

namespace waveEncoder
{

struct  waveFormat{
    char            riffid[4];      // RIFF
    uint32_t        chsize;         // riff chunk size  (16,18,40)
    char            waveid[4];      // wave id      
    char            fmtid[4];       // FMT header       
    uint32_t        subchunk1Size;  // Size of the fmt chunk                                
    uint16_t        formatcode;     // format code 0x0001=PCM  0x0003=IEEE Float,0x0006=alaw,0x0007=mulaw,0xFFFE=Extensible 
    uint16_t        noofChannels;   // Number of interleaved channels                   
    uint32_t        samplesPerSec;  // Sampling rate (blocks per sec)                             
    uint32_t        avgbytesPerSec; // bytes per second 
    uint16_t        blockAlign;     // Data block size 
    uint16_t        bitsPerSample;  // bits per sample      
    char            dataid[4];      // "data"  string   
    uint32_t        subchunk2Size;  // Sampled data length    
};
/*
    The thread function which reads given wave file and encode into
    mp3 format using lame library. The encoded file is stored in the 
    given location 
*/
void audioEncoder::encodeWavToMp3()
{
    std::string str("Encoding Wave File  : " + m_Wavefilename);
    LOG(str);
    waveFormat wave{0};
    std::string mp3filename(m_Wavefilename);
    auto pos = mp3filename.find(".wav");
    if(pos != std::string::npos)
    {
        mp3filename.replace(pos, mp3filename.size(), ".mp3");
    }

    lame_global_flags *gfp = lame_init();    
    lame_set_quality(gfp, 5);
    lame_init_params(gfp);

    const uint data_size = 65536;
    size_t noofreadbytes, noofwritebytes;

    short int readbuffer[2*data_size];
    u_char writebuffer[data_size];
    FILE *wavefile = fopen(m_Wavefilename.c_str(), "rb");

    if(wavefile != NULL)
    {
        FILE *mp3file = fopen(mp3filename.c_str(), "wb");
        try
        {
            noofreadbytes = fread(&wave, 4, 40, wavefile);
            do
            {
                noofreadbytes = fread(readbuffer, 2*sizeof(short int), data_size, wavefile);
                if(noofreadbytes == 0)
                {
                    noofwritebytes = lame_encode_flush(gfp, writebuffer, data_size);
                }
                else
                {
                    noofwritebytes = lame_encode_buffer_interleaved(gfp, readbuffer, noofreadbytes, 
                                        writebuffer, data_size);
                }
                fwrite(writebuffer, noofwritebytes, 1, mp3file);

            }while(noofreadbytes != 0);        }
        catch(const std::exception& e)
        {
            LOG(e.what());
        }
      
        fclose(mp3file);
    }
    else
    {
        LOG_DEBUG("audioEncoder Wavefile open error : ", ferror(wavefile));
    }

    fclose(wavefile);
    lame_close(gfp);
    str.erase();
    str = "Encoding Successful : " + mp3filename;
    LOG(str);
}

}   // waveEncoder