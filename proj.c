#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *zcat_cmd;
    FILE *grep_cmd;
    char result[1024];
     
    /* simulates zcat command: use popen() to open the file and read from it */
    zcat_cmd = popen("zcat NYSprop.gz", "r");
    /* error if it fails to open */
    if (zcat_cmd == NULL) {
      perror("Error with popen");
      exit(EXIT_FAILURE);
    }

    /* simulates grep command: use popen() to extract only lines with the last name LEISER */
    /* prints results to a file called cResult.txt */
    grep_cmd = popen("grep '^LEISER ' >cResult.txt", "w");
    if (grep_cmd == NULL){
      perror("Error with popen");
      exit(EXIT_FAILURE);
    }

    while (fgets(result, sizeof(result), zcat_cmd) != NULL){
      fprintf(grep_cmd, "%s", result);
    }
    

    if (pclose(zcat_cmd) == -1 || pclose(grep_cmd) == -1)
      exit(EXIT_FAILURE);
    
    return 0;
}
