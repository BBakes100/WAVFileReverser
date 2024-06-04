#include <stdio.h>
#include "file_lib.h"
#include "wav.h"

/*
 * Brandon Baker and Bailey Compton
 * CIS 343 01 - Strucutres of Programming Language
 * Professor Woodring
 * Reversing a .wav File with C
*/

// Function to fetch the first 44 bytes of a .wav file and build a wav_header struct 
wav_header create_wav_header(char* byteArray, size_t fileSize){

	wav_header header;
	header.file_header = malloc(44);

	for(int i = 0; i < 44; i++){
		*(header.file_header+i) = *(byteArray + i);
	}

	// Check bytes 0-3 are 'RIFF'
	if(!(*(header.file_header) == 'R') || !(*(header.file_header + 1) == 'I') ||
		!(*(header.file_header + 2) == 'F') || !(*(header.file_header + 3) == 'F')){
		printf("ERROR: Bytes 0-3 are not RIFF");
		free(header.file_header);
		exit(1);
	}

	char secondCheck[4] = { *(header.file_header+4), *(header.file_header+5), *(header.file_header+6), *(header.file_header+7)};
	int* second = (int *) secondCheck;

	// Check Integer in bytes 4-7 is file size - 8
	if(*second != (fileSize - 8)){
		printf("ERROR: Bytes 4-7 Do not equal fize size - 8");
		free(header.file_header);
		exit(1);
	}

	// Check bytes 8-11 are 'WAVE'
	if(!(*(header.file_header + 8) == 'W') || !(*(header.file_header + 9) == 'A') ||
		!(*(header.file_header + 10) == 'V') || !(*(header.file_header + 11) == 'E')){
		printf("ERROR: Bytes 8-11 are not WAVE");
		free(header.file_header);
		exit(1);
	}

	char thirdCheck[2] = { header.file_header[22], header.file_header[23]};
	short* third = (short*) thirdCheck;

	// Check file has 2 channels
	if(*third != 2){
		printf("ERROR: File does not have exactly 2 channels");
		free(header.file_header);
		exit(1);
	}

	char fourthCheck[4] = { header.file_header[20], header.file_header[21]};
	int* fourth = (int *) fourthCheck;

	// Check format type is 1
	if(*fourth != 1){
		printf("ERROR: Format type is not 1");
		free(header.file_header);
		exit(1);
	}

	return header;
}

// Function that reads in wav file content
wav_file* read_wav_file(const char* path, size_t* fileSize){

	// Read .wav file
	char* file = read_file(path, fileSize);

	// Create wav_file from return bytes and set contents of wav_file
	wav_header* header = malloc(sizeof(wav_header));
	*header = create_wav_header(file, *fileSize);

	wav_file* wav = malloc(sizeof(wav_file));
	wav->header = header;
	wav->fileSize = *fileSize;
	wav->byteArray = file;

	// return pointer to new wav file
	return wav;
}

// Function that writes the wav file to a new file
int write_wav_file(const char* path, wav_file wav){
	
	return write_file(path, wav.byteArray, wav.fileSize);
}
