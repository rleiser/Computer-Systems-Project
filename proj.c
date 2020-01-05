#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Bool prefix(const char *pat, const char *str)
{
  /* checks if a string is a prefix of another string */
  return strncmp(pat, str, strlen(pat)) == 0;
}

int main(void)
{
    FILE *cmd;
    char result[1024];
    char pat[] = "LEISER ";
    FILE *fp;
    
    /* simulates zcat command: use popen() to open the file and read from it */
    cmd = popen("zcat NYSprop.gz", "r");
    /* error if it fails to open */
    if (cmd == NULL) {
      perror("Error with popen");
      exit(EXIT_FAILURE);
    }

    /* open a new file that the results of the simulated pipeline will be added to */
    fp = fopen("cResult.txt", "w");
    /* error if it fails to open */
    if (fp == NULL){
      perror("Error opening cResult file");
      exit(EXIT_FAILURE);
    }
    

    /* reads a line at a time from a stream */
    while (fgets(result, sizeof(result), cmd)) {
      /* simulates grep command: if the pattern matches the line, print the line */ 
      if (prefix(pat, result) == 1){
	if (fprintf(fp, "%s", result) < 0){
	  exit(EXIT_FAILURE);
	}
      }
    }
    
    pclose(cmd);
    fclose(fp);
    return 0;
}
