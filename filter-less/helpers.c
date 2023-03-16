#include "helpers.h"

#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Soma os valores rgb do pixel, calcula a média dessa soma e a arredonda
            int sum = image[y][x].rgbtBlue + image[y][x].rgbtGreen + image[y][x].rgbtRed;
            int average = round(sum / 3.0);

            // Muda os valores rgb do pixel para serem iguais a média
            image[y][x].rgbtBlue = average;
            image[y][x].rgbtGreen = average;
            image[y][x].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Declara variáveis rgb para o pixel
            int originalBlue = image[y][x].rgbtBlue;
            int originalGreen = image[y][x].rgbtGreen;
            int originalRed = image[y][x].rgbtRed;

            // Calcula as versões sépia do pixel
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

            // Limita a versão sépia a um máximo de 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Muda os valores rgb do pixel para suas versões sépia
            image[y][x].rgbtBlue = sepiaBlue;
            image[y][x].rgbtGreen = sepiaGreen;
            image[y][x].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        // Em vez de verificar todas as colunas de pixel, verificaremos apenas metade, pois ao
        // Trocar metade dos pixeis a outra metade também vai ser trocada
        for (int x = 0, temp; x < width / 2; x++)
        {
            // Troca o pixel na coluna x com o pixel na coluna inversa correspondente
            temp = image[y][x].rgbtBlue;
            image[y][x].rgbtBlue = image[y][width - 1 - x].rgbtBlue;
            image[y][width - 1 - x].rgbtBlue = temp;

            temp = image[y][x].rgbtGreen;
            image[y][x].rgbtGreen = image[y][width - 1 - x].rgbtGreen;
            image[y][width - 1 - x].rgbtGreen = temp;

            temp = image[y][x].rgbtRed;
            image[y][x].rgbtRed = image[y][width - 1 - x].rgbtRed;
            image[y][width - 1 - x].rgbtRed = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copia a imagem pois se não, ao desfocar um pixel, isso vai afetar o efeito no próximo
    RGBTRIPLE copy[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            copy[y][x].rgbtBlue = image[y][x].rgbtBlue;
            copy[y][x].rgbtGreen = image[y][x].rgbtGreen;
            copy[y][x].rgbtRed = image[y][x].rgbtRed;
        }
    }

    // Repete o processo para todos os pixeis
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Define variáveis para a soma de cada valor rgb, contador e raio do blur
            int blueSum = 0, greenSum = 0, redSum = 0, c = 0;
            int r = 1;

            // Verifica cada pixel e soma seus valores rgb de acordo com o raio
            // Ex: raio 1 a soma será feita para todas os pixeis até 1 de distância do pixel principal
            for (int row = y - r; row <= y + r; row++)
            {
                for (int column = x - r; column <= x + r; column++)
                {
                    if ((row >= 0 && column >= 0) && (row <= height - 1 && column <= width - 1))
                    {
                        blueSum += copy[row][column].rgbtBlue;
                        greenSum += copy[row][column].rgbtGreen;
                        redSum += copy[row][column].rgbtRed;
                        c++;
                    }
                }
            }

            // Tira a média da soma, de acordo com quantos pixels foram somados e arredondando
            int averageBlue = round(blueSum * 1.0 / c);
            int averageGreen = round(greenSum * 1.0 / c);
            int averageRed = round(redSum * 1.0 / c);

            // Muda os valores rgb do pixel para a média rgb dos pixels à sua volta
            image[y][x].rgbtBlue = averageBlue;
            image[y][x].rgbtGreen = averageGreen;
            image[y][x].rgbtRed = averageRed;
        }
    }
    return;
}
