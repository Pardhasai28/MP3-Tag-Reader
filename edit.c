#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include"common.h"

void big_to_little(void *ptr,int size);       // Convert byte order between big and little endian

void edit(char frame[],char new[],char file[],FILE *fp)    // Edit selected MP3 metadata frame
{
    if(fp == NULL)
    {
        printf(RED"Original file not opened\n"RESET);
        return;
    }

    FILE *fp2;                                // File pointer for temporary MP3 file

    if((fp2=fopen("newsong.mp3","w+"))==NULL)
    {
        printf(RED"New song file doesn't exist\n"RESET);
    }

    char firstbytes[10];

    fread(firstbytes,10,1,fp);                // Read MP3 header
    fwrite(firstbytes,10,1,fp2);             // Copy MP3 header

    for(int i=0;i<6;i++)
    {
        fread(firstbytes,1,4,fp);            // Read frame ID
        fwrite(firstbytes,1,4,fp2);          // Copy frame ID

        if(strcmp(firstbytes,frame)==0)      // Check for target frame
        {
            if(strcmp(firstbytes,"TYER")==0) // Validate year field
            {
                char *endptr;
                long year = strtol(new, &endptr, 10);

                if (*endptr != '\0' || year <= 0)
                {
                    printf(BMAGENTA"=====================================================================================================\n");
                    printf(RED "ERROR: Please provide a valid year.\n" RESET);
                    printf(BMAGENTA"=====================================================================================================\n");
                    return;
                }
            }

            unsigned int size=strlen(new);
            int backupsize=size;             // Store original size value

            big_to_little(&size,4);          // Convert size to big endian

            fwrite(&size,1,4,fp2);           // Write updated size

            int oldsize;

            fread(&oldsize,1,4,fp);          // Read existing frame size
            big_to_little(&oldsize,4);

            fread(firstbytes,1,2,fp);        // Read frame flags
            fwrite(firstbytes,1,2,fp2);      // Copy frame flags

            fwrite(new,1,backupsize,fp2);    // Write updated metadata

            fseek(fp,oldsize,SEEK_CUR);      // Skip old metadata

            printf(BMAGENTA"================================================================================================\n"RESET);
            printf(ORANGE"%s content is edited to %s in the mp3 file successfully\n"RESET,frame,new);
            printf(BMAGENTA"================================================================================================\n"RESET);
        }
        else                                 // Copy unchanged frame data
        {
            int size;

            fread(&size,1,4,fp);            // Read frame size
            big_to_little(&size,4);         // Convert size to little endian

            int oldsize=size;               // Store frame size

            big_to_little(&size,4);         // Convert size back to big endian

            fwrite(&size,1,4,fp2);          // Copy frame size

            char flags[2];

            fread(flags,1,2,fp);            // Read frame flags
            fwrite(flags,1,2,fp2);          // Copy frame flags

            char buffer[oldsize];

            fread(buffer,1,oldsize,fp);     // Read frame metadata
            fwrite(buffer,1,oldsize,fp2);   // Copy frame metadata
        }
    }

    char ch;

    while(fread(&ch,1,1,fp)!=0)             // Copy remaining audio data
    {
        fwrite(&ch,1,1,fp2);
    }

    fclose(fp);                             // Close original file
    fclose(fp2);                            // Close temporary file

    remove(file);                           // Delete original file
    rename("newsong.mp3",file);             // Rename temporary file
}