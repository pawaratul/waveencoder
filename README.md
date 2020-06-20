TASK

Write a C/C++ commandline application that encodes a set of WAV files to MP3

Requirements:

(1) application is called with pathname as argument, e.g. <applicationname> F:\MyWavCollection all WAV-files contained directly in that folder are to be encoded to MP3

(2) use all available CPU cores for the encoding process in an efficient way by utilizing multi-threading

(3) statically link to lame encoder library

(4) application should be compilable and runnable on Windows and Linux

(5) the resulting MP3 files are to be placed within the same directory as the source WAV files, the filename extension should be changed appropriately to .MP3

(6) non-WAV files in the given folder shall be ignored

(7) multithreading shall be implemented in a portable way, for example using POSIX pthreads.

(8) frameworks such as Boost or Qt shall not be used

(9) the LAME encoder should be used with reasonable standard settings (e.g. quality based encoding with quality level "good")


# waveencoder

## Linux

### One time setting
    - MP3 encoding library - lame library - 3.100. Install lame with thecommand *sudo apt install libmp3lame-dev*
    - Compiler - GNU C++ compiler 7.5.0. Install GNU compiler with below command *sudo apt install g++*
    - git - 2.17.1. Install git with command *sudo apt install git*


### Build
    - Open terminal, clone the repository "waveencoder" and go to the directory "waveencoder"
    - Build the souce code with
     *g++ sources/*.cpp  -I includes -lpthread /usr/lib/x86_64-linux-gnu/libmp3lame.a -o waveencoder*
    - Build with macro INFO OR DEBUG to enable logs
      *g++ sources/*.cpp  -I includes -lpthread /usr/lib/x86_64-linux-gnu/libmp3lame.a -o waveencoder -D INFO -D DEBUG*
    - Run the binary with 
   	  *./wavencoder <directory path of wave files>*


## Windows 

### One time setting
    - Install cygwin and Install below packages 
    - 

### Build
    - Open cygwin terminal, clone the repository "waveencoder" and go to directory "waveencoder"
    - Build the souce code with
     *g++ sources/*.cpp  -I includes -lpthread /usr/lib/x86_64-linux-gnu/libmp3lame.a -o waveencoder*
    - Build with macro INFO OR DEBUG to enable logs
      *g++ sources/*.cpp  -I includes -lpthread /usr/lib/x86_64-linux-gnu/libmp3lame.a -o waveencoder -D INFO -D DEBUG*
    - Run the binary with commandline
   	  *./wavencoder <directory path of wave files>*
