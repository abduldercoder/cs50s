#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            int gray = round((red + green + blue) /3.0);

            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }

}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Apply sepia formula
            int sepiared = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiagreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiablue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Cap values at 255 if they exceed it
            if (sepiared > 255) sepiared = 255;
            if (sepiagreen > 255) sepiagreen = 255;
            if (sepiablue > 255) sepiablue = 255;

            // Set the new RGB values
            image[i][j].rgbtRed = sepiared;
            image[i][j].rgbtGreen = sepiagreen;
            image[i][j].rgbtBlue = sepiablue;
        }
    }
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < (width/2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width-j-1] = temp;
        }

    }



}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary copy of the original image
    RGBTRIPLE temp[height][width];

    // Copy original image to temp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int count = 0;

            // Loop through the 3×3 grid around the pixel
            for (int di = -1; di <= 1; di++)  // Row offset
            {
                for (int dj = -1; dj <= 1; dj++)  // Column offset
                {
                    int ni = i + di;  // Neighbor row index
                    int nj = j + dj;  // Neighbor column index

                    // Check if the neighboring pixel is within the image boundaries
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalRed += temp[ni][nj].rgbtRed;
                        totalGreen += temp[ni][nj].rgbtGreen;
                        totalBlue += temp[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Compute the average color values and assign to the original image
            image[i][j].rgbtRed = round((float)totalRed / count);
            image[i][j].rgbtGreen = round((float)totalGreen / count);
            image[i][j].rgbtBlue = round((float)totalBlue / count);
        }
    }
}
