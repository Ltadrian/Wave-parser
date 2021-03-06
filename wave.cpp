/**
 * Read and parse an uncompressed wave file - (PCM)
 * Needed a custom parser for Qt to handle wave files
**/

#include <iostream>
#include <fstream>
#include "wave.h"

using namespace std;

Wave::Wave(const std::string &filename) {
    m_filename = filename;
    load(m_filename);
}


Wave::~Wave(){
}


void Wave::load(const std::string &filename) {

    fstream fs;
    fs.open(filename, fstream::in);
    if (fs.is_open()) {

        cout << "Reading " << filename << " file... " << endl;
        // read header data

        unsigned char buffer4[4]; //4 byte buffer
        unsigned char buffer2[2]; //2 byte buffer

        cout << "Size of arrays" << sizeof(buffer4) << "\n";
        cout << "Size of arrays" << sizeof(buffer2) << "\n";

        fs.read(reinterpret_cast<char*>(buffer4), sizeof(header.chunk_ID) );
        strcpy( header.chunk_ID, (char *) (buffer4));
        cout << "(1-4) Chunk Descriptor: " << header.chunk_ID << endl;

        fs.read(reinterpret_cast<char*>(buffer4), sizeof(header.chunk_size));
        header.chunk_size = (buffer4[0]<<0) |
                            (buffer4[1]<<8) |
                            (buffer4[2]<<16) |
                            (buffer4[3]<<24); //convert little endian to big endian

        cout << "(5-8) Total size in bytes: " << header.chunk_size <<endl;
        double mb = header.chunk_size/1048576.0;
        cout << "Total MB: " << mb << " MB" << endl;


        fs.read(reinterpret_cast<char*>(buffer4), sizeof(header.format) );
        strcpy(header.format, (char*) buffer4);
        cout << "(9-12) File type: " << header.format << endl;

        fs.read(reinterpret_cast<char*>(buffer4), sizeof(header.fmt_chunk_marker) );
        strcpy(header.fmt_chunk_marker, (char*) buffer4);
        cout << "(13-16) File type: " << header.fmt_chunk_marker << endl;


        fs.read(reinterpret_cast<char*>(buffer4), sizeof(header.length_of_fmt));
        header.length_of_fmt = (buffer4[0]<<0) |
                               (buffer4[1]<<8) |
                               (buffer4[2]<<16) |
                               (buffer4[3]<<24) ;

        cout << "(17-20) Length of fmt header(subchunk): " << header.length_of_fmt << endl;

        fs.read(reinterpret_cast<char*>(buffer2), sizeof(buffer2) ); //2 bytes
        header.format_type = (buffer2[0]<<0) | (buffer2[1]<<8);

        char format_name[3] = "";
        if(header.format_type == 1)
            strcpy(format_name,"PCM"); //only dealing with PCM
        else
            cout << "Audio not uncompressed (PCM)" << endl;


        cout << "(21-22) Audio Format: " << format_name << endl;


        fs.read(reinterpret_cast<char*>(buffer2), sizeof(buffer2) );
        header.channels = (buffer2[0]<<0) | (buffer2[1]<<8);
        char num_channels[6] = "";
        if(header.channels == 2)
            strcpy(num_channels, "Stereo");
        else
            strcpy(num_channels, "Mono");

        cout << "(23-24) Number of channels: " << num_channels <<endl;

        fs.read(reinterpret_cast<char*>(buffer4), sizeof(header.sample_rate));

        header.sample_rate =   (buffer4[0]<<0) |
                               (buffer4[1]<<8) |
                               (buffer4[2]<<16) |
                               (buffer4[3]<<24) ;

        cout << "(25-28) Sample rate: " << header.sample_rate << endl;


        fs.read(reinterpret_cast<char*>(buffer4), sizeof(header.byte_rate));

        header.byte_rate =   (buffer4[0]<<0) |
                             (buffer4[1]<<8) |
                             (buffer4[2]<<16) |
                             (buffer4[3]<<24) ;

        cout << "(29-32) Byte rate: " << header.byte_rate << endl;

        fs.read(reinterpret_cast<char*>(buffer2), sizeof(buffer2) );

        header.block_align =   (buffer2[0]<<0) |
                               (buffer2[1]<<8);

        cout << "(33-34) Block Align: " << header.block_align << endl;


        fs.read(reinterpret_cast<char*>(buffer2), sizeof(buffer2) );

        header.bits_per_sample =   (buffer2[0]<<0) |
                                   (buffer2[1]<<8);

        cout << "(35-36) Bits per sample: " << header.bits_per_sample << endl;

        fs.read(reinterpret_cast<char*>(buffer4), sizeof(header.data_chunk_header) );
        strcpy(header.data_chunk_header, (char*) buffer4);
        cout << "(37-40) Chunk Descriptor: " << header.data_chunk_header << endl;

        fs.read(reinterpret_cast<char*>(buffer4), sizeof(header.data_size));

        header.data_size =  (buffer4[0]<<0) |
                            (buffer4[1]<<8) |
                            (buffer4[2]<<16) |
                            (buffer4[3]<<24) ;

        cout << "(41-44) File size: " << header.data_size << endl;
        mb = header.data_size/1048576.0;
        cout << "Total MB: " << mb << " MB" << endl;

        if (fs)
            cout << "file read successfully." << endl;
        else
            std::cout << "error: only " << fs.gcount() << " could be read";
        fs.close();



    }
    else{
        cout << "Error opening file" << endl;
    }


    fs.close();

}



