#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

char* loadlrc(const char* path){
  int fd = open(path, O_RDONLY);
  if (fd < 0) {
    perror("Open");
    exit(0);
  }
  struct stat st;

  if (fstat(fd, &st) < 0){
    perror("Stat");
    exit(0);  
  }

  char* buffer = malloc(st.st_size + 1);
  if (buffer == NULL){
    perror("Alocate");
    exit(0);
  }
  
  if (read(fd, buffer, st.st_size) < 0){
    perror("Read");
    exit(0);
  }
  printf("Archivo cargado correctamente\n");
  return buffer;
}
