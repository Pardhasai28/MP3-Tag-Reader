#include<stdio.h>
#include<string.h>
char *frame_mode(char str[])        //checks the command line argument and returns corresponding frame header ID
{
    if(strcmp(str,"-t")==0)
    return "TIT2";
    else if(strcmp(str,"-a")==0)
    return "TPE1";
    else if(strcmp(str,"-A")==0)
    return "TALB";
    else if(strcmp(str,"-y")==0)
    return "TYER";
    else if(strcmp(str,"-m")==0)
    return "TCOM";
    else if(strcmp(str,"-g")==0)
    return "TCON";
    else if(strcmp(str,"-c")==0)
    return "COMM";
    else
    return NULL;

}