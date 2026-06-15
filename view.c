#include<stdio.h>
#include<string.h>
#include"common.h"

void big_to_little(void *ptr,int size)        // Convert byte order from big endian to little endian
{
    char *swap=(char *)ptr;

    for(int i=0;i<size/2;i++)
    {
        char temp=swap[i];
        swap[i]=swap[size-i-1];
        swap[size-i-1]=temp;
    }
}

int validate(char str[],FILE *fp)             // Validate MP3 file format and version
{
    char tag[4];

    fread(tag,sizeof(char),3,fp);
    tag[3]='\0';

    int validtag = strcmp(tag,"ID3");         // Verify ID3 tag

    if(validtag)
    {
        printf(BMAGENTA"================================================================================================\n"RESET);
        printf(RED"Give a song file\n"RESET);
        printf(BMAGENTA"================================================================================================\n"RESET);
        return 0;
    }

    int version[2];

    fread(version,2,1,fp);

    if(version[0]!=3)                         // Verify ID3v2.3 version
    {
        printf(BMAGENTA"================================================================================================\n"RESET);
        printf(RED"Give input of song version 3\n");
        printf(BMAGENTA"================================================================================================\n"RESET);
        return 0;
    }

    fseek(fp,5,SEEK_CUR);                    // Skip remaining header bytes

    return 1;
}

int view(char str[],FILE *fp)                // Display MP3 metadata information
{
    printf(BMAGENTA"================================================================================================\n"RESET);
    printf(ORANGE"\t\t\t\t\tMP3 TAG INFORMATION\n"RESET);
    printf(BMAGENTA"================================================================================================\n"RESET);

    for(int i=0;i<6;i++)                     // Read required metadata frames
    {
        char frame_id[5];

        fread(frame_id,4,1,fp);
        frame_id[4]='\0';

        if(strcmp(frame_id,"TIT2")==0)       // Read song title
        {
            unsigned int size;

            fread(&size,4,1,fp);            // Read frame size
            big_to_little(&size,sizeof(int));

            fseek(fp,2,SEEK_CUR);           // Skip frame flags

            char meta[size];

            fread(meta,size,1,fp);          // Read frame data

            printf(YELLOW"Song Name     : ");

            for(int i=0;i<size;i++)
            {
                printf(GREEN"%c"RESET,meta[i]); // Display metadata
            }

            printf("\n");
        }

        if(strcmp(frame_id,"TCOM")==0)       // Read composer name
        {
            unsigned int size;

            fread(&size,4,1,fp);
            big_to_little(&size,sizeof(int));

            printf("%ls",&size);

            fseek(fp,2,SEEK_CUR);

            char meta[size];

            fread(meta,size,1,fp);

            printf(YELLOW"Composer Name : ");

            for(int i=0;i<size;i++)
            {
                printf(GREEN"%c",meta[i]);   // Display metadata
            }

            printf("\n");
        }

        if(strcmp(frame_id,"TPE1")==0)       // Read artist name
        {
            unsigned int size;

            fread(&size,4,1,fp);
            big_to_little(&size,sizeof(int));

            printf("%ls",&size);

            fseek(fp,2,SEEK_CUR);

            char meta[size];

            fread(meta,size,1,fp);

            printf(YELLOW"Artists Name  : ");

            for(int i=0;i<size;i++)
            {
                printf(GREEN"%c",meta[i]);   // Display metadata
            }

            printf("\n");
        }

        if(strcmp(frame_id,"TALB")==0)       // Read album name
        {
            unsigned int size;

            fread(&size,4,1,fp);
            big_to_little(&size,sizeof(int));

            printf("%ls",&size);

            fseek(fp,2,SEEK_CUR);

            char meta[size];

            fread(meta,size,1,fp);

            printf(YELLOW"Album Name    : ");

            for(int i=0;i<size;i++)
            {
                printf(GREEN"%c",meta[i]);   // Display metadata
            }

            printf("\n");
        }

        if(strcmp(frame_id,"TYER")==0)       // Read release year
        {
            unsigned int size;

            fread(&size,4,1,fp);
            big_to_little(&size,sizeof(int));

            printf("%ls",&size);

            fseek(fp,2,SEEK_CUR);

            char meta[size];

            fread(meta,size,1,fp);

            printf(YELLOW"Song Year     : ");

            for(int i=0;i<size;i++)
            {
                printf(GREEN"%c",meta[i]);   // Display metadata
            }

            printf("\n");
        }

        if(strcmp(frame_id,"TCON")==0)       // Read genre information
        {
            unsigned int size;

            fread(&size,4,1,fp);
            big_to_little(&size,sizeof(int));

            printf("%ls",&size);

            fseek(fp,2,SEEK_CUR);

            char meta[size];

            fread(meta,size,1,fp);

            printf(YELLOW"Genre         : ");

            for(int i=0;i<size;i++)
            {
                printf(GREEN"%c"RESET,meta[i]); // Display metadata
            }

            printf("\n");
        }

        if(strcmp(frame_id,"COMM")==0)       // Read comment information
        {
            unsigned int size;

            fread(&size,4,1,fp);

            big_to_little(&size,sizeof(int));

            printf("%ls",&size);

            fseek(fp,2,SEEK_CUR);

            char meta[size];

            fread(meta,size,1,fp);

            printf(YELLOW"Comment       : ");

            for(int i=0;i<4;i++)
            {
                printf(GREEN"%c",meta[i]);   // Display metadata
            }

            printf("\n");
        }
    }

    printf(BMAGENTA"===============================================================================================\n"RESET);

    fclose(fp);                              // Close MP3 file
}