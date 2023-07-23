#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculates the average of the red, green and blue color
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // Same RGB values gives different shades of grey
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Temproray sepia variables
    int sepiaRed, sepiaGreen, sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Algorithm to calculate the sepia values of a pixel
            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // Checks if the value of sepia variable is more than 255 if yes then set it to 255 else the calculated value
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Creates a buffer array to store the image
    RGBTRIPLE buffer[height][width];

    // Copies the original structure to buffer array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        // Uses the swap and j variable to define the start and the end pixel of the image
        for (int j = 0, swap = width - 1; j < width; j++)
        {
            // Swaps the pixel at i height and j column with the i height and swap column pixel
            // Like row 1 column 1 with row 1 column (say) 10 (end)
            image[i][j] = buffer[i][swap];
            // Changes the end of the column to end - 1
            swap--;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];

    // Copies the original structure to temproray array because the previous pixel which is consider in making the blur effect will have
    // its value changed in the image variable
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }

    float totalred, totalgreen, totalblue;
    int count = 0;
    totalred = totalgreen = totalblue = 0;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Loops from col - 1 to col + 1 and considers each pixels
            for (int blurrow = row - 1; blurrow <= row + 1; blurrow++)
            {
                // Loops from col - 1 to col + 1 and considers each pixels
                for (int blurcol = col - 1; blurcol <= col + 1; blurcol++)
                {
                    // Checks for the boundary condition
                    if (blurcol >= 0 && blurrow >= 0 && blurrow < height && blurcol < width)
                    {
                        // Stores the total of all colors into their seperate variable
                        totalred += original[blurrow][blurcol].rgbtRed;
                        totalgreen += original[blurrow][blurcol].rgbtGreen;
                        totalblue += original[blurrow][blurcol].rgbtBlue;
                        // Because the avg denominator is equivalent total number of pixels which is calculated different for normal pixel and
                        // different for borderline pixels
                        count++;
                    }
                }
            }
            image[row][col].rgbtRed = round(totalred / count);
            image[row][col].rgbtBlue = round(totalblue / count);
            image[row][col].rgbtGreen = round(totalgreen / count);
            // Resets the variable
            count = 0;
            totalred = totalgreen = totalblue = 0;
        }
    }

    return;
}
