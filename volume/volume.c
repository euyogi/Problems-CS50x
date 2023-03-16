// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    // Declara uma variável temporária para armazenar um byte do header
    uint8_t tempHeader;

    // Irá copiar o header, de acordo com seu tamanho dado por HEADER_SIZE
    for (int i = 0; i < HEADER_SIZE; i++)
    {
        fread(&tempHeader, sizeof(uint8_t), 1, input);
        fwrite(&tempHeader, sizeof(uint8_t), 1, output);
    }

    // TODO: Read samples from input file and write updated data to output file

    // Declara uma variável temporária para armazenar dois bytes do sample
    int16_t tempSample;

    // Irá ler desde o fim do header até o fim do arquivo, copiando os samples e os multiplicando pelo fator inserido pelo usuário
    while (fread(&tempSample, sizeof(int16_t), 1, input))
    {
        tempSample *= factor;
        fwrite(&tempSample, sizeof(uint16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
