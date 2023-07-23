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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE old_image[height][width];

    // Copying image to a new file
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            old_image[i][j] = image[i][j];
        }
    }

    // The two kernels
    int gx[3][3] = {{-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = {{-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Stores the 3x3 matrix used to define the edges
            int multiple_row[3] = {row - 1, row, row + 1};
            int multiple_col[3] = {col - 1, col, col + 1};

            int gxred, gxgreen, gxblue;
            gxred = gxgreen = gxblue = 0;

            int gyred, gygreen, gyblue;
            gyred = gygreen = gyblue = 0;

            // Loops from row-1 to row+1
            for (int edgerow = 0; edgerow < 3; edgerow++)
            {
                // Loops from col - 1 to col + 1 and considers each pixels
                for (int edgecol = 0; edgecol < 3; edgecol++)
                {
                    int nrow = multiple_row[edgerow];
                    int ncol = multiple_col[edgecol];
                    RGBTRIPLE pixel = old_image[nrow][ncol];

                    if (nrow < height && nrow >= 0 && ncol < width && ncol >= 0)
                    {
                        gxred += pixel.rgbtRed * gx[edgerow][edgecol];
                        gxgreen += pixel.rgbtGreen * gx[edgerow][edgecol];
                        gxblue += pixel.rgbtBlue * gx[edgerow][edgecol];

                        gyred += pixel.rgbtRed * gy[edgerow][edgecol];
                        gygreen += pixel.rgbtGreen * gy[edgerow][edgecol];
                        gyblue += pixel.rgbtBlue * gy[edgerow][edgecol];
                    }
                }
            }
            int newred = round(sqrt(gxred * gxred + gyred * gyred));
            int newblue = round(sqrt(gxblue * gxblue + gyblue * gyblue));
            int newgreen = round(sqrt(gxgreen * gxgreen + gygreen * gygreen));

            image[row][col].rgbtRed = newred > 255 ? 255 : newred;
            image[row][col].rgbtGreen = newgreen > 255 ? 255 : newgreen;
            image[row][col].rgbtBlue = newblue > 255 ? 255 : newblue;
        }
    }

    return;
}
