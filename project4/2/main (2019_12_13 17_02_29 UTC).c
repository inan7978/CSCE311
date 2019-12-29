#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

char flipIt(char c) {
  if(isupper(c)){
    return tolower(c);
} else {
  return toupper(c);
}
}
int main(void)
{
  FILE *pFile = fopen ("ANNA_KARENINA.txt", "r");
  long lSize;
  char * buffer;
  size_t result;

  fseek (pFile, 0, SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);

  buffer = (char*) malloc (sizeof(char)*lSize);
  result = fread (buffer,1,lSize,pFile);

  for (int i = 0; i < lSize; ++i){
    buffer[i] = flipIt(buffer[i]);
  }
  FILE * nFile = fopen ("ANNA_KARENINA.txt", "wb");
	fwrite (buffer, 1, lSize, nFile);
    fclose(nFile);
    fclose(pFile);
printf("The file has been modified using fopen(), fread(), and fwrite(). Refresh it in your text editor.\n");
return 0;
}
