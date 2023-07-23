#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

void checkArguments(int argc);
void checkFile(FILE *file);
int isJPEG(BYTE buffer[]);

int main(int argc, char *argv[])
{
    // Basic function
    checkArguments(argc);
    FILE *card = fopen(argv[1], "r");
    checkFile(card);

    // Create a buffer file
    BYTE buffer[BLOCK_SIZE];

    // Filename
    char filename[8];
    FILE *image;
    int counter = 0;

    while (fread(buffer, BLOCK_SIZE, 1, card) == 1)
    {
        if (isJPEG(buffer) == 1)
        {
            // Checks for if counter is 0 or not (meaning 1 file is present or not)
            if (counter != 0)
            {
                // Close the previous file
                fclose(image);
            }
            sprintf(filename, "%03i.jpg", counter++);
            image = fopen(filename, "w");
            fwrite(buffer, BLOCK_SIZE, 1, image);
        }
        else if (counter > 0)
        {
            fwrite(buffer, BLOCK_SIZE, 1, image);
        }
    }
    fclose(card);
    fclose(image);
}

// Checks the number of arguments present in the command line
void checkArguments(int argc)
{
    if (argc != 2)
    {
        printf("./recover IMAGE\n");
        exit(1);
    }
}

// Checks if the file can be read or not
void checkFile(FILE *file)
{
    if (file == NULL)
    {
        printf("Could not open file.\n");
        exit(1);
    }
}

// Checks for the header of JPEG
int isJPEG(BYTE buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return 1;
    }
    return 0;
}