#include <stdio.h>
#include <stdlib.h>
#include "wav.h"

/*
 * Brandon Baker and Bailey Compton
 * CIS 343 01 - Strucutres of Programming Language
 * Professor Woodring
 * Reversing a .wav File with C
*/

int main(int argc, char** argv){

	//read the wav file
	size_t fileSize;
	wav_file* wav = read_wav_file(argv[1], &fileSize);

	// Find the amount of bytes per samples
	char bytes[2] = { wav->header->file_header[34], wav->header->file_header[35]};
	short* bitsPerSample = (short*) bytes;
	short bytesPerSample = (*bitsPerSample / 8) * 2;

	// Interpret byte array as int*
	int* samples_array = (int*) wav->byteArray; 
	int numSamples = (fileSize - 44) / bytesPerSample;
	int* revSamples = malloc(fileSize);

	// Pointer starts at beginning of non header
	int* spotInArray = samples_array + 11;

	// Reverse the Samples and store in new array
	for(int i = numSamples; i >= 11; i--){
		revSamples[i] = *spotInArray;

		// Increment pointer next mem address
		spotInArray++;
	}

	// Create final byte array to return using header bytes, and new, reversed samples
	char* revInBytes = (char*) revSamples;
	char* byteArrayToReturn = malloc(fileSize);
	for(int i = 0; i < fileSize; i++){
		if(i < 44){
			byteArrayToReturn[i] = wav->byteArray[i];
		} else {
			byteArrayToReturn[i] = revInBytes[i];
		}
	}

	wav->byteArray = byteArrayToReturn;

	// write to new wav file
	write_wav_file(argv[2], *wav);

	// Print Out Relevant Information
	printf("\nInput file - %s", argv[1]);
	printf("\nOutput file - %s", argv[2]);

	// bytes 24 - 27, sample rate
	char sampleRate[4] = { wav->header->file_header[24], wav->header->file_header[25], wav->header->file_header[26], wav->header->file_header[27]};
	int* sRate = (int*) sampleRate;
	printf("\nSample Rate - %d", *sRate);
	printf("\nFile Size - %zu Bytes", fileSize);

	// bytes 22 - 23, number of channels
	char numChannels[2] = { wav->header->file_header[22], wav->header->file_header[23]};
	u_int16_t* numChan = (u_int16_t*) numChannels;
	printf("\nNumber of Channels - %d\n", *numChan);

	// free allocated memory
	free(revSamples);
	free(byteArrayToReturn);
	free(wav->header->file_header);
	free(wav->header);
	free(wav);
	
	return 0;
}
