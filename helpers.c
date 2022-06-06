#include <math.h>
#include <cs50.h>

#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int result = round((image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0);

            image[h][w].rgbtRed = image[h][w].rgbtGreen = image[h][w].rgbtBlue = result;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w< width; w++)
        {
            int r, g, b;

            r = image[h][w].rgbtRed;
            g = image[h][w].rgbtGreen;
            b = image[h][w].rgbtBlue;


            int red = round(0.393 * r + 0.769 * g + 0.189 *b);
            int green = round(0.349 * r + 0.686 * g + 0.168 * b);
            int blue = round(0.272 * r + 0.534 * g + 0.131 * b);
            if ( red > 255)
            {
                image[h][w].rgbtRed = 255;
            }
            else
            {
                image[h][w].rgbtRed = red;
            }
            if (green > 255)
            {
                image[h][w].rgbtGreen = 255;
            }
            else
            {
                image[h][w].rgbtGreen = green;
            }
            if (blue > 255)
            {
                image[h][w].rgbtBlue = 255;
            }
            else
            {
                image[h][w].rgbtBlue = blue;
            }
        }
    }
}

void swap(RGBTRIPLE * a, RGBTRIPLE * b)
{
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2 ; w++)
        {
            swap(&image[h][w], &image[h][width - 1 - w]);
        }
    }
}

bool is_valid_pixel(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}

RGBTRIPLE get_blurred_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int redValue, blueValue, greenValue; redValue = blueValue = greenValue = 0;
    int numofvalidpixels = 0;
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            int new_i = i + di;
            int new_j = j + dj;
            if (is_valid_pixel(new_i, new_j, height, width))
            {
                numofvalidpixels++;
                redValue += image[new_i][new_j].rgbtRed;
                blueValue += image[new_i][new_j].rgbtBlue;
                greenValue += image[new_i][new_j].rgbtGreen;
            }
        }
    }
    RGBTRIPLE blurred_pixel;
    blurred_pixel.rgbtBlue = round((float) blueValue / numofvalidpixels);
    blurred_pixel.rgbtGreen = round((float) greenValue / numofvalidpixels);
    blurred_pixel.rgbtRed = round((float) redValue / numofvalidpixels);
    return blurred_pixel;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = get_blurred_pixel(i, j, height, width, image);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j< width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
}