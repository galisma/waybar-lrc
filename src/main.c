#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }
  
  sd_bus *bus = NULL;
  int r;
  r = sd_bus_open_user(&bus);

  if (r < 0) {
    fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-r));
    exit(0);
  }

  // lrc parse
  char *path = argv[1];
  char *buffer = loadlrc(path);
  return 0;
}
