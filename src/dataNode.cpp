// ***********************************************
// Program Title: wavManip.cpp
// Name: Andrew Sweeney
// Course Section: CPE-381-01
// Due Date: 03/04/20
// program description: file for manipulation of modified wav file 
// used to take each chunk of a simple header file and read from or write to
// another wav file
//
// Important variables:
// 	wav_hdr wav; a structure for storing the header file
// 		as well as using a buffer for data values read in.
//
// Functions are:  
//	void getNXT(FILE*); gets a 50 element array buffer for manipulation
// 	void writeNXT(FILE*); writes a 50 element array buffer to an outfile 
//
// 	Comments Key:
// 	| (OC) -> output checking
// 	| (NL) -> new location for data transfer (in/out)
// ***********************************************


#ifndef WAVMANIP_CPP
#define WAVMANIP_CPP

/*#include <cmath>

#include "dataNode.h"
// #include "48k_notch_2k_v2.h"

struct wav_hdr wav;
struct dataNode bf;


void MicroCloudNode::DataNode::dataUpdate()
{
    // check node statuses
    // if node statuses require attention, process the node statuses
    // check if new wave file has arrived
    // if new wave file has arrived, process it
    // end
}

void GetNextSample(wav_hdr input, dataNode& bfs, File * wavfile)
{
    // **********************************************
    // getNXT takes exactly one sample of a soundfile
    // and stores it in the buffer array. Handling is 
    // intended for the client code using the above
    // function, FileHandling.
    // **********************************************

    void *xptr = bfs.buffer; 					// declaring and loading xptr with buffer location
    fread(xptr, (input.bitsPsample/8), input.numChan, wavfile); 	// read in the data into the buffer
}



void WriteSample(wav_hdr output, dataNode* bfs, FILE * wavfile)
{
    // **********************************************
    // writeNXT takes exactly one sample of a wav
    // soundfile and writes it to another wav file.
    // Handling is intended for the client code using
    // the above function, FileHandling.
    // **********************************************

    void *xptr = bfs->buffer; 				// declaring and loading xptr with buffer location
    fwrite(xptr, (output.bitsPsample/8), output.numChan, wavfile); // writes buffer data to outfile
}



/*short int FindMaxInFile(wav_hdr input, dataNode& bfs, FILE * wavfile, int &chan)
{
  // ***************************************************
  // findMax takes exactly one sample at a time of a wav
  // soundfile and looks to see if its the largest
  // sample.
  // Handling is intended for the client code using
  // the above function, FileHandling.
  // ***************************************************

  void *xptr = bfs.buffer; 				// declaring and loading xptr with buffer location 
  long int bookmark = ftell(wavfile); 			// setting a bookmark for returning to data manipulation
  fread(xptr, (wav.bitsPsample/8), 1, wavfile); 	// reading one sample at a time so we can find max
  							// because it reads one sample at a time we
  short int max = std::abs(bfs.buffer[0]); 		// assumes max is first value
  chan = 1; int maxchan = 1;
  while(!feof(wavfile)) 
  {
    getNXT(input, bfs, wavfile); 			// still reading one sample at a time so we can find max
    if(max < std::abs(bfs.buffer[0]))
    { 
      max = std::abs(bfs.buffer[0]); 			// checks to see if bigger, if so it replaces it.
      maxchan = 1;
    } 
    else if(input.numChan == 2 && max < std::abs(bfs.buffer[1]))
    { 
      max = std::abs(bfs.buffer[1]); 			// checks to see if bigger, if so it replaces it.
      maxchan = 2;
    } 
  }
  chan = maxchan;
  //std::cout << chan << std::endl;
  fseek(wavfile, bookmark, SEEK_SET); 			// returns the file position to the start of the data 
  return max; 						// returns the max value
}



void SingleChannelFilter(const wav_hdr & input, dataNode* bfs, const uint16_t filter[FILTER_SIZE])
{  
  // **********************************************
  // MonoFilt takes exactly one sample of a wavfile
  // and filters it with either h1 or h2, depending
  // on sampling frequency. Handling is intended
  // for the client code using the above function,
  // FileHandling.
  // **********************************************
  for(int i = 0; j < FILTER_SIZE; i++)
    bfs->databuff[j] = 0; 				// initializes all values in array to zero for convolution sum
  while(!feof(wavfile)) 				// the sample processing algorithm
  {
    GetNextSample(input, bfs, wavfile); 			// gets sample for processing
    for(int i = (FILTER_SIZE); (i > 0); i--)
      bfs->databuff[i] = bfs->databuff[i-1]; 		// shifts for convolution sum

    bfs->databuff[0] = bfs->buffer[0]; 			// most recent input into very first element
    for(int k = 0; k < FILTER_SIZE; k++) 
        bfs->outbuffer[0] += bfs->databuff[k]*h1[k];                  // performs the actual convolution sum part 
    WriteSample(input, bfs, outfile); 			// writes file
  }
}
*/

#endif




