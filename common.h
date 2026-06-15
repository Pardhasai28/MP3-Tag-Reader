#define RED       "\033[1;31m"
#define RESET     "\033[0m"
#define GREEN     "\033[1;32m"
#define BBLUE     "\033[1;94m"
#define BCYAN     "\033[1;96m"
#define BMAGENTA  "\033[1;95m"
#define ORANGE    "\033[38;5;208m"
#define YELLOW    "\033[1;33m"
int view(char str[],FILE *fp);
void edit(char frame[],char new[],char file[],FILE *fp);
char *frame_mode(char str[]);
int validate(char str[],FILE *fp);