#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    // By checking every line column of the image (all pixels)
    for (int line = 0; line < height; line++)
    {
        for (int column = 0; column < width; column++)
        {
            // If the values for red, green and blue, in the pixel (image[line[column]])
            // are all '0', than the pixel is black and we should change its color
            if (image[line][column].rgbtBlue == 0
                && image[line][column].rgbtGreen == 0
                && image[line][column].rgbtRed == 0)
            {
                image[line][column].rgbtBlue = 66;
                image[line][column].rgbtGreen = 94;
                image[line][column].rgbtRed = 133;
            }
        }
    }
}
