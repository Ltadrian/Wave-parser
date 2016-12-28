#ifndef WAVE_H
#define WAVE_H

/**
 * WAVE file header format
 * unsigned_int for little endian conversions
 */
struct HEADER
{
    char chunk_ID[4];                           // RIFF string
    std::uint32_t  chunk_size;                  // overall size of
    char format[4];                             // WAVE string
    char fmt_chunk_marker[4];                   // fmt string with trailing null char
    std::uint32_t length_of_fmt;                // length of the format data
    std::uint16_t  format_type;                 // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
    std::uint16_t  channels;                    // no.of channels
    std::uint32_t  sample_rate;                 // sampling rate (blocks per second)
    std::uint32_t  byte_rate;                   // SampleRate * NumChannels * BitsPerSample/8
    std::uint16_t  block_align;                 // NumChannels * BitsPerSample/8
    std::uint16_t  bits_per_sample;             // bits per sample, 8- 8bits, 16- 16 bits etc
    char data_chunk_header [4];                 // DATA string or FLLR string
    std::uint32_t  data_size;                   // NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
};


/**
 * Wave file data handler and accessor.
 */
class Wave
{

public:
    Wave(const std::string& filename);
    ~Wave();

    void load(const std::string& filename);

    std::string getFilename() const
    {
        return m_filename;
    }


    uint32_t getNumChannels() const
    {
        return header.channels;
    }


    bool isMono() const
    {
        return header.channels == 1;
    }


    bool isStereo() const
    {
        return header.channels == 2;
    }

    uint32_t getSampleRate() const
    {
        return header.sample_rate;
    }

    uint32_t getByteRate() const
    {
        return header.byte_rate;
    }

    uint16_t getBitsPerSample() const
    {
        return header.bits_per_sample;
    }


private:

    /**
     * File name for .wav file
     */
    std::string m_filename;

    /**
     * Header structure
     */
     HEADER header;
};

#endif //WAVE_H