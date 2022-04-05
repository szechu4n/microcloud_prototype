#ifndef DCNODE_H
#define DCNODE_H

#include "node.h"

#define FILTER_SIZE  1000

struct wav_hdr
{
    char 	chunkID[4]; 	// 4 letter code for RIFF
    int 	chunkSz; 	// Contains 36 + data size
    char 	format[4]; 	// 4 letter code for format (WAVE)
    //
    char 	subchunkID[4]; 	// contains "fmt "
    int 	subchunk_1Sz; 	// contains size for next 6 items
    short int audioFmt; 	// contains PCM = 1, which means WAV file wasnt compressed
    short int numChan; 	// number of channels, mono = 1, stereo = 2...
    int 	sampleRate; 	// should contain 48000
    int 	byteRate; 	// numChan*sampleRate*bitsPsample/8
    short int blockalign; // numChan*bitsPsample/8
    short int bitsPsample;// size of each sample, usually 8, 16, or more bits
    // 
    char 	subchunk_2ID[4];// contains "data"
    int 	subchunk_2Sz; 	// size of data, might be in bytes
};

struct dataNode
{
    uint16_t buffer[2]; 	// contains one sample of data max, maximum 2 channel stereo sample.
    uint16_t databuff[FILTER_SIZE];	// contains a dynamically allocated array depending on the size of the file
};

namespace MicroCloudNode
{
    namespace DataNode
    {
        void dataSetup();
        void dataUpdate();
        extern Task dataTask;
            /*(TASK_SECOND * 1 , TASK_FOREVER, &c3Loop)*/
    }
}

#endif // DCNODE_H