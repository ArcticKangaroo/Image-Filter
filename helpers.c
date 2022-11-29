#include <math.h>
#include <stdio.h>

#include "helpers.h"

//convert image to grayscale - replace R, G, and B of each pixel with their average
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            BYTE avg = round(sum / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

//reflect image horizontally - traverse each pixel in left half of image and swap it with its equivalent on the right
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

//blur image - for each pixel, get average of surrounding pixels
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE og[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            og[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sumBlue = 0.0;
            double sumGreen = 0.0;
            double sumRed = 0.0;
            int count = 0;

            //run from pixel on top to pixel at bottom, and from pixel on left to pixel on right of original pixel
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    //check if pixel exists
                    if (k < 0 || k > height - 1 || l < 0 || l > width - 1)
                    {
                        continue;
                    }

                    sumBlue += og[k][l].rgbtBlue;
                    sumGreen += og[k][l].rgbtGreen;
                    sumRed += og[k][l].rgbtRed;
                    count++;
                }
            }


            BYTE avgBlue = round(sumBlue / count);
            BYTE avgGreen = round(sumGreen / count);
            BYTE avgRed = round(sumRed / count);

            image[i][j].rgbtBlue = avgBlue;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtRed = avgRed;
        }
    }

    return;
}

//detect edges - apply Sobel operator
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gxkernel[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gykernel[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    RGBTRIPLE og[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            og[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            double gxBlue = 0.0, gxGreen = 0.0, gxRed = 0.0;
            double gyBlue = 0.0, gyGreen = 0.0, gyRed = 0.0;

            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k < 0 || k > height - 1 || l < 0 || l > width - 1)
                    {
                        continue;
                    }

                    //[k - i -1][l - j - 1] determines weight of current pixel in kernel by its position with respect to original pixel
                    gxBlue += og[k][l].rgbtBlue * gxkernel[k - i + 1][l - j + 1];
                    gxGreen += og[k][l].rgbtGreen * gxkernel[k - i + 1][l - j + 1];
                    gxRed += og[k][l].rgbtRed * gxkernel[k - i + 1][l - j + 1];

                    gyBlue += og[k][l].rgbtBlue * gykernel[k - i + 1][l - j + 1];
                    gyGreen += og[k][l].rgbtGreen * gykernel[k - i + 1][l - j + 1];
                    gyRed += og[k][l].rgbtRed * gykernel[k - i + 1][l - j + 1];
                }
            }

            gxBlue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));
            gxGreen = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            gxRed = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));

            //cap at 255
            BYTE finalBlue = (gxBlue > 255) ? 255 : gxBlue;
            BYTE finalGreen = (gxGreen > 255) ? 255 : gxGreen;
            BYTE finalRed = (gxRed > 255) ? 255 : gxRed;

            image[i][j].rgbtBlue = finalBlue;
            image[i][j].rgbtGreen = finalGreen;
            image[i][j].rgbtRed = finalRed;
        }
    }
    return;
}
