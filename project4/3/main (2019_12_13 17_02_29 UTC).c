#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

char flipIt(char c) {
  if(isupper(c)){
    return tolower(c);
} else {
  return toupper(c);
}
}

int main(int argc, char** argv){
	int fd = open("ANNA_KARENINA.txt", O_RDWR, S_IRUSR | S_IWUSR);
	struct stat sb;

	if (fstat(fd,&sb) == -1){
		perror("couldn't get the file size.");
	}

	char *file_in_memory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	for (int i = 0; i < sb.st_size; i++){
		file_in_memory[i] = flipIt(file_in_memory[i]);
	}
	printf("The file has been modified using MMF I/O. Reload it in your text editor.");
	printf("\n");
}