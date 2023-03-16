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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            // Define variáveis para o Gx e Gy de cada valor rgb, dois contadores e os fatores do algoritmo
            int blueGx = 0, greenGx = 0, redGx = 0, blueGy = 0, greenGy = 0, redGy = 0;
            int cX = 0, cY = 0;
            int factors[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

            // Verifica os pixeis em vorta do pixel principal e soma o produto de seus valores pelo fator
            for (int row = y - 1; row <= y + 1; row++)
            {
                for (int column = x - 1; column <= x + 1; column++)
                {
                    // Desconsidera 'pixeis que estariam fora da borda'
                    if ((row >= 0 && column >= 0) && (row <= height - 1 && column <= width - 1))
                    {
                        // Realiza a multiplicação do valor pelo fator
                        blueGx += (copy[row][column].rgbtBlue * factors[cY][cX]);
                        greenGx += (copy[row][column].rgbtGreen * factors[cY][cX]);
                        redGx += (copy[row][column].rgbtRed * factors[cY][cX]);

                        blueGy += (copy[row][column].rgbtBlue * factors[cX][cY]);
                        greenGy += (copy[row][column].rgbtGreen * factors[cX][cY]);
                        redGy += (copy[row][column].rgbtRed * factors[cX][cY]);
                    }
                    cX++;
                }
                cY++;
                cX = 0;
            }

            // Define e arredonda os valores rgb de acordo com o algoritmo 'Sobel Filter',
            int blue = round(sqrt(blueGx * blueGx + blueGy * blueGy));
            int green = round(sqrt(greenGx * greenGx + greenGy * greenGy));
            int red = round(sqrt(redGx * redGx + redGy * redGy));

            // Limita os valores a um máximo de 255
            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (red > 255)
            {
                red = 255;
            }

            // Muda os valores rgb do pixel para valores encontrados a partir do algoritmo 'Sobel Filter' acima
            image[y][x].rgbtBlue = blue;
            image[y][x].rgbtGreen = green;
            image[y][x].rgbtRed = red;
        }
    }
    return;
}
