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

- Clone the repo into your workspace. Do one time setting if required and Follow the Build steps 

OR

- Download the repo into your workspace. Do one time setting if required and Follow the Build steps

## Linux

### One time setting
    - Install MP3 encoding library with the command : 
		sudo apt install libmp3lame-dev

    - Install GNU C++ compiler : 
		sudo apt install g++


### Build
    - Open terminal, clone the repository "waveencoder" and go to the directory "waveencoder"

    - Build the souce code with :
      g++ sources/*.cpp  -I includes -lpthread /usr/lib/x86_64-linux-gnu/libmp3lame.a -o waveencoder -Wall

    - Build with macro to enable logs
      g++ sources/*.cpp  -I includes -lpthread /usr/lib/x86_64-linux-gnu/libmp3lame.a -o waveencoder -D INFO -D DEBUG -D RUNTIME


## Windows 

### One time setting
    - Install cygwin in windows 
    - Install packages packages > GNU C++ Compiler, Lame library 

### Build
    - Open cygwin terminal, clone the repository "waveencoder" and go to directory "waveencoder"

    - Build the souce code with
     *g++ sources/*.cpp  -I includes -lpthread /usr/lib/x86_64-linux-gnu/libmp3lame.a -o waveencoder -Wall -O2*

    - Build with macro INFO OR DEBUG to enable logs
      *g++ sources/*.cpp  -I includes -lpthread /usr/lib/x86_64-linux-gnu/libmp3lame.a -o waveencoder -D INFO -D DEBUG*


## WAVE to MP Conversion

    - The generated executable accept directory path as argument as below
           ./wavencoder <directory path of wave files> 

	- I have uploaded few wave files under the folder : waveencoder/resources. 
  - Convert all WAVE files in the directory resources to MP3 files, 
      ./waveencoder resources
