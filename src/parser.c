#include "parser.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct lyrics {
  int time;
  char *sentence;
  int length;
} lyrics;

typedef enum { R_MINS, R_SECS, R_MSEC, R_TEXT } State;

char *loadlrc(const char *path) {
  int fd = open(path, O_RDONLY);
  if (fd < 0) {
    perror("Open");
    exit(1);
  }
  struct stat st;

  if (fstat(fd, &st) < 0) {
    perror("Stat");
    exit(1);
  }

  char *buffer = malloc(st.st_size + 1);
  if (buffer == NULL) {
    perror("Allocate");
    exit(1);
  }

  if (read(fd, buffer, st.st_size) < 0) {
    perror("Read");
    exit(1);
  }

  buffer[st.st_size] = '\0';

  printf("Archivo cargado correctamente\n");
  close(fd);
  return buffer;
}

int parselrc(const char *buffer) {
  struct lyrics *song = malloc(sizeof(struct lyrics) * 100);
  for (int j = 0; j < 50; j++) {
    song[j].sentence = NULL;
    song[j].length = 0;
    song[j].time = 0;
  }

  int i = 0;
  int line = 0;
  State state = R_MINS;

  // temp vars for time count
  int current_num = 0;
  int mins = 0, secs = 0, msecs = 0;

  while (buffer[i] != '\0' && line < 100) {
    switch (state) {
    case R_MINS:
      if (buffer[i] == '[') {
        i++;
        current_num = 0;
        mins = secs = msecs = 0;
      } else if (isdigit(buffer[i])) {
        current_num = current_num * 10 + (buffer[i] - '0');
        i++;
      } else if (buffer[i] == ':') {
        mins = current_num;
        current_num = 0;
        state = R_SECS;
        i++;
      } else {
        i++;
      }
      break;

    // Seconds mode
    case R_SECS:
      if (isdigit(buffer[i])) {
        current_num = current_num * 10 + (buffer[i] - '0');
        i++;
      } else if (buffer[i] == '.') {
        secs = current_num;
        current_num = 0;
        state = R_MSEC;
        i++;
      } else {
        i++; // unexpected chars
      }
      break;

    // Milliseconds mode
    case R_MSEC:
      if (isdigit(buffer[i])) {
        current_num = current_num * 10 + (buffer[i] - '0');
        i++;
      } else if (buffer[i] == ']') {
        msecs = current_num;
        song[line].time = (mins * 60000) + (secs * 1000) + msecs;
        current_num = 0;
        state = R_TEXT;
        i++;
        song[line].sentence = (char *)&buffer[i];
      } else {
        i++;
      }
      break;

    // Text mode
    case R_TEXT:
      if (buffer[i] == '\n' || buffer[i] == '\0') {
        song[line].length = &buffer[i] - song[line].sentence;
        line++;
        state = R_MINS;
        i++;
      } else if (buffer[i] == '[') {
        if (song[line].sentence != NULL) {
          song[line].length = &buffer[i] - song[line].sentence;
          line++;
        }
        state = R_MINS;
      } else {
        i++;
      }
      break;
    }
  }

  if (state == R_TEXT && line < 100 && song[line].sentence != NULL) {
    song[line].length = &buffer[i] - song[line].sentence;
    line++;
  }

#ifdef DEBUG
  printf("Líneas parseadas: %d\n", line - 1);
  for (int j = 0; j < line; j++) {
    printf("Línea %d: Tiempo=%dms, Longitud=%d, Texto='%.*s'\n", j,
           song[j].time, song[j].length, song[j].length, song[j].sentence);
  }
#endif

  // TODO: free(song)
  return line;
}
