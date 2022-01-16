#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // printf("height: %i\n", height);
    // printf("width: %i\n", width);

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            RGBTRIPLE pixel = image[h][w];
            int average = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
            image[h][w].rgbtRed = image[h][w].rgbtGreen = image[h][w].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            RGBTRIPLE pixel = image[h][w];

            int sepiaRed = round(.393 * pixel.rgbtRed + .769 * pixel.rgbtGreen + .189 * pixel.rgbtBlue);
            int sepiaGreen = round(.349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue);
            int sepiaBlue = round(.272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue);

            if (sepiaRed > 255)
            {
                image[h][w].rgbtRed = 255;
                image[h][w].rgbtGreen = sepiaGreen;
                image[h][w].rgbtBlue = sepiaBlue;
            }
            else if (sepiaGreen > 255)
            {
                image[h][w].rgbtRed = sepiaRed;
                image[h][w].rgbtGreen = 255;
                image[h][w].rgbtBlue = sepiaBlue;
            }
            else if (sepiaBlue > 255)
            {
                image[h][w].rgbtRed = sepiaRed;
                image[h][w].rgbtGreen = sepiaGreen;
                image[h][w].rgbtBlue = 255;
            }
            else
            {
                image[h][w].rgbtRed = sepiaRed;
                image[h][w].rgbtGreen = sepiaGreen;
                image[h][w].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    
    for (int h = 0; h < height; h++)
    {
        int currPos = 0;
        for (int w = width - 1; w >= 0; w--, currPos++)
        {
            temp[h][currPos] = image[h][w];
        }
    }

    // copy temp to image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = temp[h][w];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    
    // copy temp to image
    // for (int h = 0; h < height; h++)
    // {
    //     for (int w = 0; w < width; w++)
    //     {
    //         image[h][w] = temp[h][w];
    //     }
    // }
    return;
}
