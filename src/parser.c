#include "parser.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

char *loadlrc(const char *path) {
  int fd = open(path, O_RDONLY);
  if (fd < 0) {
    perror("Open");
    exit(0);
  }
  struct stat st;

  if (fstat(fd, &st) < 0) {
    perror("Stat");
    exit(0);
  }

  char *buffer = malloc(st.st_size + 1);
  if (buffer == NULL) {
    perror("Alocate");
    exit(0);
  }

  if (read(fd, buffer, st.st_size) < 0) {
    perror("Read");
    exit(0);
  }

  buffer[st.st_size] = '\0';

  printf("Archivo cargado correctamente\n");
  return buffer;
}

int parselrc(const char *buffer) {

  typedef struct letras {
    int tiempo;
    char *letra;
  } letras;

  // bucle de reads
  int i = 0;
  while (buffer[i] != '\n') {
    i++;
  }
  printf("%d\n", i);
  write(1, buffer, i + 1);
  write(1, "hola", 4);
  return 0;
}
