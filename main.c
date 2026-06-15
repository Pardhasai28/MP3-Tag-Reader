// Name          : V.Pardha Sai(25040B_056)
// Date          : 23/03/2026
// Project       : MP3 Tag Reader & Editor
// Description   :  // MP3 Tag Reader is a software application that reads and displays ID3 tag information from MP3 files.

                    // validate() -> Validates all command line arguments provided by the user.

                    // view() -> Displays MP3 tag details such as song name, artist, album, year, composer, genre, and comments.

                    // edit() -> Modifies MP3 tag details including song name, artist, album, year, composer, genre, and comments.

                    // frame_mode() -> Returns the appropriate frame header based on the given command line argument.


// Sample Input  : ./a.out -v song.mp3 -> For viewing the details
//                 ./a.out -e -t Newname song.mp3 -> For editing the details in the mp3 file
// Sample Output : 
// ================================================================================================
//                                         MP3 TAG INFORMATION
// ================================================================================================
// Song Name     : 
// Artists Name  : 
// Album Name    : 
// Song Year     : 
// Genre         : 
// Comment       : 
// ===============================================================================================
#include<stdio.h>
#include<string.h>
#include "common.h"

int main(int argc,char *argv[])     // Parse command-line arguments and perform MP3 tag operations
{
    int p,q;

    if(argc==2)
    {
        int cmp=strcmp(argv[1],"--help");       // Check for help option

        if(cmp==0)
        {
            printf(BMAGENTA"=====================================================================================================\n");
            printf(YELLOW"\t\t\t\t\tHELP\n"RESET);
            printf(BMAGENTA"=====================================================================================================\n"RESET);
            printf(YELLOW"Options:\n");
            printf(BBLUE"For viewing MP3 tag information\t./a.out -v <filename>\n");
            printf("For Editing MP3 tag information\t./a.out -e <tag> <text> <filename>\n");
            printf(YELLOW"Tag options for Editing:\n");
            printf(GREEN"-t\t->\t Edit Title\n");
            printf("-a\t->\t Edit Artist\n");
            printf("-A\t->\t Edit Album\n");
            printf("-y\t->\t Edit Year\n");
            printf("-m\t->\t Edit Composer name\n");
            printf("-c\t->\t Edit Content type\n");
            printf("-g\t->\t Edit Genre\n");
            printf(YELLOW"Egs:\n");
            printf(BBLUE"For Viewing:\t->\t");
            printf("./a.out -v filename.mp3\n\n");
            printf("For editing title:\t->\t");
            printf("./a.out -e -t Newtitle filename.mp3\n");
            printf(BMAGENTA"=====================================================================================================\n"RESET);
            return 0;
        }
    }

    if(argc>2)
    {
        p=strcmp(argv[1],"-v");
        q=strcmp(argv[1],"-e");

        if(p==0)        // Handle view operation
        {
            if(argc==3)
            {
                char *k=strstr(argv[2],".mp3");

                if(k==NULL || strcmp(k,".mp3")!=0)      // Validate MP3 file extension
                {
                    printf(BMAGENTA"================================================================================================\n"RESET);
                    printf(RED"ERROR: Give input an mp3 file\n");
                    printf(BMAGENTA"================================================================================================\n"RESET);
                    return 0;
                }

                FILE *fp;

                if((fp=fopen(argv[2],"rb"))==NULL)      // Check file availability
                {
                    printf(BMAGENTA"================================================================================================\n"RESET);
                    printf(RED"ERROR: File does not exist\n");
                    printf(BMAGENTA"================================================================================================\n"RESET);
                    return 0;
                }

                int result=validate(argv[2],fp);        // Validate MP3 file format

                if(result)
                {
                    view(argv[2],fp);                   // Display MP3 metadata
                }
            }
            else
            {
                printf(BMAGENTA"================================================================================================\n"RESET);
                printf(RED"ERROR: "RESET);
                printf(BBLUE"For viewing MP3 tag information\t./a.out -v <filename>\n");
                printf(BMAGENTA"================================================================================================\n"RESET);
            }
        }
        else if(q==0)   // Handle edit operation
        {
            if(argc!=5)     // Validate argument count
            {
                printf(BMAGENTA"================================================================================================\n");
                printf(BBLUE"For Editing MP3 tag information\t ./a.out -e <tag> <text> <filename>\n");
                printf(YELLOW"Tag options for Editing:\n");
                printf(GREEN"-t\t->\t Edit Title\n");
                printf("-a\t->\t Edit Artist\n");
                printf("-A\t->\t Edit Album\n");
                printf("-y\t->\t Edit Year\n");
                printf("-m\t->\t Edit Composer name\n");
                printf("-c\t->\t Edit Content type\n");
                printf("-g\t->\t Edit Genre\n");
                printf(BMAGENTA"================================================================================================\n");
            }

            if(argc==5)
            {
                char *frame=frame_mode(argv[2]);        // Get frame identifier for selected tag

                if(frame==NULL)                         // Validate tag option
                {
                    printf(BMAGENTA"================================================================================================\n");
                    printf(RED"Invalid argument \n"YELLOW"Give valid tag option to edit\n"RESET);
                    printf(GREEN"-t\t->\t Edit Title\n");
                    printf("-a\t->\t Edit Artist\n");
                    printf("-A\t->\t Edit Album\n");
                    printf("-y\t->\t Edit Year\n");
                    printf("-m\t->\t Edit Composer name\n");
                    printf("-c\t->\t Edit Content type\n");
                    printf("-g\t->\t Edit Genre\n");
                    printf(BMAGENTA"================================================================================================\n"RESET);
                    return 0;
                }

                char *k=strstr(argv[4],".mp3");

                if(k==NULL || strcmp(k,".mp3")!=0)     // Validate MP3 file extension
                {
                    printf(BMAGENTA"================================================================================================\n");
                    printf(RED"ERROR: Give input an mp3 file\n");
                    printf(BMAGENTA"================================================================================================\n"RESET);
                    return 0;
                }

                FILE *fp;

                if((fp=fopen(argv[4],"rb"))==NULL)      // Check file availability
                {
                    printf(BMAGENTA"================================================================================================\n");
                    printf(RED"ERROR: File does not exist\n");
                    printf(BMAGENTA"================================================================================================\n"RESET);
                    return 0;
                }

                int result=validate(argv[4],fp);       // Validate MP3 file format

                if(result)
                {
                    rewind(fp);                        // Reset file pointer to beginning
                    edit(frame,argv[3],argv[4],fp);   // Modify selected MP3 tag
                }
            }
        }
        else
        {
            printf(BMAGENTA"================================================================================================\n");
            printf(RED"ERROR: INVALID TAG\n"RESET);
            printf(BMAGENTA"================================================================================================\n");
            printf(BBLUE"For viewing MP3 tag information\t./a.out -v <filename>\n");
            printf("For Editing MP3 tag information\t./a.out -e <tag> <text> <filename>\n");
            printf(YELLOW"Tag options for Editing:\n");
            printf(GREEN"-t\t->\t Edit Title\n");
            printf("-a\t->\t Edit Artist\n");
            printf("-A\t->\t Edit Album\n");
            printf("-y\t->\t Edit Year\n");
            printf("-m\t->\t Edit Composer name\n");
            printf("-c\t->\t Edit Content type\n");
            printf("-g\t->\t Edit Genre\n");
            printf(BMAGENTA"================================================================================================\n"RESET);
        }
    }
    else
    {
        printf(BMAGENTA"================================================================================================\n");
        printf(RED"\t\t\t\tInvalid arguments provided\n");
        printf(BMAGENTA"================================================================================================\n");
        printf(YELLOW"Usage:\n------\n");
        printf(YELLOW"FOR VIEWING MP3 TAG INFORMATION:\n");
        printf(BBLUE"\t ./a.out -v <filename.mp3>\n\n");
        printf(YELLOW"FOR EDITING MP3 TAG INFORMATION:\n");
        printf(BBLUE"\t ./a.out -e <tag_option> <new_value> <filename.mp3>\n\n");
        printf(YELLOW"Tag options for Editing:\n");
        printf(GREEN"-t\t->\t Edit Title\n");
        printf("-a\t->\t Edit Artist\n");
        printf("-A\t->\t Edit Album\n");
        printf("-y\t->\t Edit Year\n");
        printf("-m\t->\t Edit Composer name\n");
        printf("-c\t->\t Edit Content type\n");
        printf("-g\t->\t Edit Genre\n");
        printf(ORANGE"FOR HELP:\n");
        printf(ORANGE"---------\n");
        printf(BBLUE"\t./a.out --help\n\n");
        printf(BMAGENTA"================================================================================================\n"RESET);
    }
}