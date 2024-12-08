#include "helpers.h"
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define colours 3

void swap(BYTE *a, BYTE *b);
void box_blur(int x, int y, int height, int width, int upper_limit, int lower_limit, int left_limit, int right_limit, float boxes,
              RGBTRIPLE image[height][width], int blur_image[height][width][colours]);
void edge_values(int i, int j, int height, int width, RGBTRIPLE image[height][width], int edge_image[height][width][colours],
                 string type);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // finding sum of R, G, B and finding average
            int sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            float average = sum / 3.0;
            int new_value = round(average);

            // Changing the R, G, B values
            image[i][j].rgbtBlue = new_value;
            image[i][j].rgbtGreen = new_value;
            image[i][j].rgbtRed = new_value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&(image[i][j].rgbtBlue), &(image[i][(width - 1) - j].rgbtBlue));
            swap(&(image[i][j].rgbtGreen), &(image[i][(width - 1) - j].rgbtGreen));
            swap(&(image[i][j].rgbtRed), &(image[i][(width - 1) - j].rgbtRed));
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Creating an array to store new R,G,B value for each blurred pixel
    int blur_image[height][width][colours];
    // Finding new R,G,B value for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Middle pixels
            if (i != 0 && i != (height - 1) && j != 0 && j != (width - 1))
            {
                box_blur(j, i, height, width, (i - 1), (i + 1), (j - 1), (j + 1), 9.0, image, blur_image);
            }
            // Top row
            if (i == 0 && j != 0 && j != (width - 1))
            {
                box_blur(j, i, height, width, i, (i + 1), (j - 1), (j + 1), 6.0, image, blur_image);
            }
            // Bottom row
            if (i == (height - 1) && j != 0 && j != (width - 1))
            {
                box_blur(j, i, height, width, (i - 1), i, (j - 1), (j + 1), 6.0, image, blur_image);
            }
            // Left column
            if (i != 0 && i != (height - 1) && j == 0)
            {
                box_blur(j, i, height, width, (i - 1), (i + 1), j, (j + 1), 6.0, image, blur_image);
            }
            // Right column
            if (i != 0 && i != (height - 1) && j == (width - 1))
            {
                box_blur(j, i, height, width, (i - 1), (i + 1), (j - 1), j, 6.0, image, blur_image);
            }
            // Top left
            if (i == 0 && j == 0)
            {
                box_blur(j, i, height, width, i, (i + 1), j, (j + 1), 4.0, image, blur_image);
            }
            // Top right
            if (i == 0 && j == (width - 1))
            {
                box_blur(j, i, height, width, i, (i + 1), (j - 1), j, 4.0, image, blur_image);
            }
            // Bottom left
            if (i == (height - 1) && j == 0)
            {
                box_blur(j, i, height, width, (i - 1), i, j, (j + 1), 4.0, image, blur_image);
            }
            // Bottom right
            if (i == (height - 1) && j == (width - 1))
            {
                box_blur(j, i, height, width, (i - 1), i, (j - 1), j, 4.0, image, blur_image);
            }
        }
    }
    // Looping through all pixels and replacing their R,B,G values with blurred values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blur_image[i][j][0];
            image[i][j].rgbtGreen = blur_image[i][j][1];
            image[i][j].rgbtRed = blur_image[i][j][2];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Creating an array to store new R,G,B value for each edge pixel
    int edge_image[height][width][colours];

    // Gx and Gy matrices
    int GX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int GY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Finding new R,G,B value for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // For each new pixel, initialise all Gx and Gy values to be 0
            float GX_blue = 0;
            float GX_green = 0;
            float GX_red = 0;
            float GY_blue = 0;
            float GY_green = 0;
            float GY_red = 0;

            // looping through a 3x3 box around 1 pixel to find GX and GY for each colour
            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    if ((i + y) < 0 || (i + y) > (height - 1) || (j + x) < 0 || (j + x) > (width - 1))
                    {
                        continue;
                    }
                    else
                    {
                        GX_blue += image[i + y][j + x].rgbtBlue * GX[1 + y][1 + x];
                        GX_green += image[i + y][j + x].rgbtGreen * GX[1 + y][1 + x];
                        GX_red += image[i + y][j + x].rgbtRed * GX[1 + y][1 + x];

                        GY_blue += image[i + y][j + x].rgbtBlue * GY[1 + y][1 + x];
                        GY_green += image[i + y][j + x].rgbtGreen * GY[1 + y][1 + x];
                        GY_red += image[i + y][j + x].rgbtRed * GY[1 + y][1 + x];
                    }
                }
            }

            // Calculating new channel value for each colour in pixel
            // Blue
            double final_value_blue = round(sqrt((GX_blue * GX_blue) + (GY_blue * GY_blue)));
            if (final_value_blue <= 255)
            {
                edge_image[i][j][0] = final_value_blue;
            }
            else
            {
                edge_image[i][j][0] = 255;
            }

            // Green
            double final_value_green = round(sqrt((GX_green * GX_green) + (GY_green * GY_green)));
            if (final_value_green <= 255)
            {
                edge_image[i][j][1] = final_value_green;
            }
            else
            {
                edge_image[i][j][1] = 255;
            }

            // Red
            double final_value_red = round(sqrt((GX_red * GX_red) + (GY_red * GY_red)));
            if (final_value_red <= 255)
            {
                edge_image[i][j][2] = final_value_red;
            }
            else
            {
                edge_image[i][j][2] = 255;
            }
        }
    }
    // Looping through all pixels and replacing their R,B,G values with edge values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = edge_image[i][j][0];
            image[i][j].rgbtGreen = edge_image[i][j][1];
            image[i][j].rgbtRed = edge_image[i][j][2];
        }
    }
    return;
}

// Swap function
void swap(BYTE *a, BYTE *b)
{
    BYTE temp = *a;
    *a = *b;
    *b = temp;
}

// Box blur function
void box_blur(int x, int y, int height, int width, int upper_limit, int lower_limit, int left_limit, int right_limit, float boxes,
              RGBTRIPLE image[height][width], int blur_image[height][width][colours])
{
    // Blue
    int sum_blue = 0;
    for (int i = upper_limit; i <= lower_limit; i++)
    {
        for (int j = left_limit; j <= right_limit; j++)
        {
            sum_blue += image[i][j].rgbtBlue;
        }
    }
    int average_blue = round(sum_blue / (boxes));
    // Storing new blurred Blue value for pixel
    blur_image[y][x][0] = average_blue;

    // Green
    int sum_green = 0;
    for (int i = upper_limit; i <= lower_limit; i++)
    {
        for (int j = left_limit; j <= right_limit; j++)
        {
            sum_green += image[i][j].rgbtGreen;
        }
    }
    int average_green = round(sum_green / (boxes));
    // Storing new blurred Green value for pixel
    blur_image[y][x][1] = average_green;

    // Red
    int sum_red = 0;
    for (int i = upper_limit; i <= lower_limit; i++)
    {
        for (int j = left_limit; j <= right_limit; j++)
        {
            sum_red += image[i][j].rgbtRed;
        }
    }
    int average_red = round(sum_red / (boxes));
    // Storing new blurred Red value for pixel
    blur_image[y][x][2] = average_red;

    return;
}
