#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

const int HEADER_SIZE = 44;

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 3)
    {
        printf("Usage: ./volume input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    // Read header
    WAVHEADER header;
    fread(&header, HEADER_SIZE, 1, input);

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        printf("Wrong file format: only WAVE supported");
        return 3;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(uint8_t), HEADER_SIZE, output);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file
    int c;
    int cur_pos;
    fseek(output, block_size, cur_pos);
    while (1)
    {
        cur_pos = ftell(output);
        if (cur_pos == 44)
            break;

        fread(&c, sizeof(uint16_t), 1, input);
        fwrite(&c, sizeof(uint16_t), 1, output);
        fseek(output, -(sizeof(uint16_t) * 2), SEEK_CUR); // *2 because once written, the output will go forward 2 bytes
    }
}

int check_format(WAVHEADER header)
{
    const char* format_name = "WAVE";
    for (int i = 0; i < strlen(format_name); ++i)
    {
        if (header.format[i] != format_name[i])
            return 0;
    }

    return 1;
}

int get_block_size(WAVHEADER header)
{
    return header.numChannels * header.byteRate;
}