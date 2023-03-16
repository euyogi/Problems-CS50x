#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }
    else if (strcmp(argv[1] + strlen(argv[1]) - 4, ".wav") != 0)
    {
        printf("Input is not a WAV file.");
        return 1;
    }
    else if (strcmp(argv[2] + strlen(argv[2]) - 4, ".wav") != 0)
    {
        printf("Output is not a WAV file.");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Error opening the file %s.", argv[1]);
        return 1;
    }

    // Read header into an variable
    WAVHEADER header;

    fread(&header, 1, sizeof(WAVHEADER), input);

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        printf("The file %s is not in WAV format.", argv[1]);
        return 1;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Error creating the file %s.", argv[2]);
        return 1;
    }

    // Write header to file
    fwrite(&header, 1, sizeof(WAVHEADER), output);

    // Use get_block_size to calculate size of block
    int blockSize = get_block_size(header);

    // Write reversed audio to file
    int blockQuantity = header.subchunk2Size / blockSize; // That's described in the exercise
    BYTE block[blockSize];
    for (int i = 1; i <= blockQuantity; i++)
    {
        fseek(input, - blockSize * i, SEEK_END); // This is important, it set's the file pointer to the end of the file
        fread(block, 1, blockSize, input);
        fwrite(block, 1, blockSize, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // According to exercise instructions
    if (header.format[0] == 'W' &&
        header.format[1] == 'A' &&
        header.format[2] == 'V' &&
        header.format[3] == 'E')
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // According to exercise instructions
    return header.numChannels * header.bitsPerSample / 8;
}