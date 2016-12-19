/**
 * Read and parse an uncompressed wave file - (PCM)
 * Needed a custom parser for Qt to handle wave files
**/

#include <iostream>
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

		char* buffer4 = new char[4]; //4 byte buffer
        char* buffer2 = new char[2]; //2 byte buffer


	    fs.read(buffer4, sizeof(header.chunk_ID) );
		strcpy(header.chunk_ID, buffer4);
		cout << "(1-4) Chunk Descriptor: " << header.chunk_ID << endl;

	    fs.read(buffer4, sizeof(header.chunk_size));
        header.chunk_size = (buffer4[0]<<0) |
                (buffer4[1]<<8) |
                (buffer4[2]<<16) |
                (buffer4[3]<<24); //convert little endian to big endian

        cout << "(5-8) Total size in bytes: " << header.chunk_size <<endl;
        double mb = header.chunk_size/1048576.0;
        cout << "Total MB: " << mb << " MB" << endl;


        fs.read(buffer4, sizeof(header.format) );
        strcpy(header.format, buffer4);
        cout << "(9-12) File type: " << header.format << endl;

        fs.read(buffer4, sizeof(header.fmt_chunk_marker) );
        strcpy(header.fmt_chunk_marker, buffer4);
        cout << "(13-16) File type: " << header.fmt_chunk_marker << endl;


        fs.read(buffer4, sizeof(header.length_of_fmt));
        header.length_of_fmt = (buffer4[0]<<0) |
                               (buffer4[1]<<8) |
                               (buffer4[2]<<16) |
                               (buffer4[3]<<24) ;

        cout << "(17-20) Length of fmt header(subchunk): " << header.length_of_fmt << endl;

        fs.read(buffer2, (sizeof(buffer2)/4) ); //2 bytes
        header.format_type = (buffer2[0]<<0) | (buffer2[1]<<8);

        char format_name[3] = "";
        if(header.format_type == 1)
            strcpy(format_name,"PCM"); //only dealing with PCM
        else
            cout << "Audio not uncompressed (PCM)" << endl;


        cout << "(21-22) Audio Format: " << format_name << endl;


        fs.read(buffer2, (sizeof(buffer2)/4) );
        header.channels = (buffer2[0]<<0) | (buffer2[1]<<8);
        char num_channels[6] = "";
        if(header.channels == 2)
            strcpy(num_channels, "Stereo");
        else
            strcpy(num_channels, "Mono");

        cout << "(23-24) Number of channels: " << num_channels <<endl;

        fs.read(buffer4, sizeof(header.sample_rate)/2);
        header.sample_rate = (buffer4[0]<<0) |
                               (buffer4[1]<<8) |
                               (buffer4[2]<<16) |
                               (buffer4[3]<<24) ;

        cout << "(25-28) Sample rate: " << header.sample_rate << endl;




        if (fs)
	      cout << "file read successfully." << endl;
	    else
	      std::cout << "error: only " << fs.gcount() << " could be read";
	    fs.close();

	    // ...buffer contains the entire file...




	    delete[] buffer4;
        delete[] buffer2;
	  }
	else{
		cout << "Error opening file" << endl;
	}
  

	fs.close();

	return 0;
}