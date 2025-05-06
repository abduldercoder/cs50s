#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Define a byte type for clarity
typedef uint8_t BYTE;

// Block size used by the camera/memory card
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover\n");
        return 1;
    }

    // Open memory card file
    FILE *inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open card.raw\n");
        return 1;
    }

    // Buffer for reading blocks
    BYTE buffer[BLOCK_SIZE];

    // Track if we're currently writing to a JPEG
    bool jpeg_found = false;

    // Count of JPEGs found
    int jpeg_count = 0;

    // File pointer for current output JPEG
    FILE *outptr = NULL;

    // Filename buffer
    char filename[8]; // ###.jpg\0

    // Read blocks until end of card
    while (fread(buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        // Check if block starts with JPEG signature
        bool is_jpeg_header =
            buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0; // Check if fourth byte starts with 1110

        // If we found a new JPEG signature
        if (is_jpeg_header)
        {
            // If we were already writing to a JPEG, close that file
            if (jpeg_found)
            {
                fclose(outptr);
            }

            // Start a new JPEG file
            jpeg_found = true;

            // Create filename (e.g., 001.jpg, 002.jpg, etc.)
            sprintf(filename, "%03i.jpg", jpeg_count);
            jpeg_count++;

            // Open new output file
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                printf("Could not create %s\n", filename);
                return 1;
            }

            // Write the current block to the output file
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }
        // If we've already found a JPEG and this block is part of it
        else if (jpeg_found)
        {
            // Continue writing to the current JPEG file
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }
    }

    // Close the last JPEG file if one was open
    if (jpeg_found)
    {
        fclose(outptr);
    }

    // Close the memory card file
    fclose(inptr);

    return 0;
}
