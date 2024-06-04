#ifndef WAV_H
#define WAV_H

/*
 * Brandon Baker and Bailey Compton
 * CIS 343 01 - Strucutres of Programming Language
 * Professor Woodring
 * Reversing a .wav File with C
*/

/*
 * The wav_header struct will be used to store the first 44 bytes of a .wav file
 *
 * Attributes:
 * 	file_header: Char pointer (byte array) that stores the first 44 bytes of a wav file 
 *
*/
typedef struct wav_header{

	char* file_header;

} wav_header;


/*
 * The wav_file struct will be used to store the contents of a wav file 
 * 
 * Attributes:
 * 	wav_header: Pointer to a wav_header struct that stores the first 44 bytes of a .wav file
 * 	fileSize: size_t value to keep track of the number of bytes in a .wav file
 *	byteArray: char* that stores all of the bytes in a .wav file
*/
typedef struct wav_file{

	wav_header* header;
	size_t fileSize;
	char* byteArray;

} wav_file;

/*
* The create_wav_header function will create a wav_header struct and store the 
* first 44 bytes of a .wav file
*
* Args:
* 	byteArray: Array of bytes (file contents)
*	fileSize: Size of the .wav file in bytes 
*
* Returns: 
*	wav_header struct
*/
wav_header create_wav_header(char* byteArray, size_t fileSize);

/*
* The read_wav_file function will read in the bytes of a .wav file 
*
* Args:
* 	path: path to a .wav file 
*	fileSize: Size of the .wav file in bytes 
*
* Returns: 
*	Memory address of a wav_file 
*/
wav_file* read_wav_file(const char* path, size_t* fileSize);

/*
* The write_wav_file function will create a new file and write the contents
* of the input file to the new .wav file 
*
* Args:
* 	path: Path to file 
*	wav: wav_file struct 
*
* Returns: 
*	0 if successfully written, 1 if there is an error
*/
int write_wav_file(const char* path, wav_file wav);

#endif
