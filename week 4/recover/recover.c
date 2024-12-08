#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max size of block of FAT FILE system
#define MAX_BLOCK_SIZE 512

// Initalise counter and file pointer
int JPEG_count = 0;
FILE *img = NULL;

int main(int argc, char *argv[])
{
    // Accept a single command-line arguement
    if (argc != 2)
    {
        printf("Usage: ./recover [file name]\n");
        return 1;
    }

    // Open forensic image for reading
    FILE *forensic_image = fopen(argv[1], "r");
    if (forensic_image == NULL)
    {
        printf("Forensic image cannot be opened for reading.\n");
        return 1;
    }

    // Create a buffer, an array of bytes, for 1 block of data
    uint8_t buffer[MAX_BLOCK_SIZE];

    // While there is data left to read
    while (fread(&buffer, 1, 512, forensic_image) == 512)
    {
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If first JPEG
            if (JPEG_count == 0)
            {
                // Make the first new JPEG file
                // Dynamically allocate memory
                char *s = "###.jpg";
                char *filename = malloc(strlen(s) + 1);

                // sprintf prints a "formatted" string into a buffer (a file)
                sprintf(filename, "%03i.jpg", JPEG_count);
                img = fopen(filename, "w");

                // Write data from buffer into new JPEG file via file pointer (img)
                fwrite(&buffer, 1, 512, img);
                JPEG_count++;
                free(filename);
            }
            // If not first JPEG
            else if (JPEG_count > 0)
            {
                // Close previous JPEG file (pointer now points to nothing)
                fclose(img);

                // Open new JPEG file
                // Dynamically allocate memory
                char *s = "###.jpg";
                char *filename = malloc(strlen(s) + 1);

                // sprintf prints a "formatted" string into a buffer (a file)
                sprintf(filename, "%03i.jpg", JPEG_count);
                // Reuse pointer
                img = fopen(filename, "w");

                // Write data from buffer into new JPEG file via file pointer (img)
                fwrite(&buffer, 1, 512, img);
                JPEG_count++;
                free(filename);
            }
        }
        // If already found JPEG
        else if (JPEG_count != 0)
        {
            // Continue writing to current JPEG file
            fwrite(&buffer, 1, 512, img);
        }
    }
    // Close remaining files (the last opened JPEG file and the forensic image itself)
    fclose(img);
    fclose(forensic_image);
}
