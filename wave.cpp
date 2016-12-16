/**
 * Read and parse a wave file
 * Needed a custom parser for 64-bit processor
**/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "wave.h"

using namespace std;


struct HEADER header;

int main(int argc, char* argv[]){
	string filename = argv[1];
	fstream fs;

	fs.open("bass.wav", fstream::in);
	if (fs.is_open()) {

	    cout << "Reading " << filename << " file... " << endl;
	    // read header data

		char* buffer = new char[sizeof(header.chunk_ID)];


	    fs.read(buffer, sizeof(header.chunk_ID) );
		strcpy(header.chunk_ID, buffer);
		cout << "Chunk Descriptor: " << header.chunk_ID << endl;


	    fs.read(buffer, sizeof(header.chunk_size));
        cout << "Little endian to big endian conversion..." <<endl;
        header.chunk_size = buffer[0]<<0 |
                    buffer[1]<<8 |
                    buffer[2]<<16 |
                    buffer[3]<<24; //bitwise operation

        cout << "(5-8) Total size in bytes: " << header.chunk_size <<endl;



	    if (fs)
	      cout << "file read successfully." << endl;
	    else
	      std::cout << "error: only " << fs.gcount() << " could be read";
	    fs.close();

	    // ...buffer contains the entire file...




	    delete[] buffer;
	  }
	else{
		cout << "Error opening file" << endl;
	}
  

	fs.close();

	return 0;
}