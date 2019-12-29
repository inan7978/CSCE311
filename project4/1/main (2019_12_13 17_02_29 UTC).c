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

int f2r = open("ANNA_KARENINA.txt", O_RDONLY);
int f2w = open("ANNA_KARENINA.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

char c;
int bytes;
while((bytes = read(f2r, &c, sizeof(c)))>0){
c = flipIt(c);
write(f2w, &c, sizeof(c));
}

close(f2r);
close(f2w);
printf("The file has been modified using open(), read(), and write(). Refresh to see changes.\n");

}
