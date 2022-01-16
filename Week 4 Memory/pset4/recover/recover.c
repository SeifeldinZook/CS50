#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define blockSize 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    typedef uint8_t BYTE;
    BYTE buffer [blockSize];
    size_t bytesRead;
    FILE *currFile;
    char currFilename[100];
    int currFilenumber = 0;

    bool isFirstJPEG = false;
    bool isJPEG = false;

    while (true)
    {
        bytesRead = fread(buffer, sizeof(BYTE), blockSize, file);
        if (bytesRead == 0)
        {
            break;
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            isJPEG = true;
            if (!isFirstJPEG)
            {
                isFirstJPEG = true;
            }
            else
            {
                fclose(currFile);
            }
            sprintf(currFilename, "%03i.jpg", currFilenumber);
            currFile = fopen(currFilename, "w");
            fwrite(buffer, sizeof(BYTE), bytesRead, currFile);
            currFilenumber++;
        }
        else
        {
            if(isJPEG)
            {
                fwrite(buffer, sizeof(BYTE), bytesRead, currFile);
            }
        }
    }
    fclose(file);
    fclose(currFile);
    return 0;
}