#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <systemd/sd-bus.h>

int main(int argc, char *argv[]) {
  sd_bus *bus = NULL;
  int r;
  r = sd_bus_open_user(&bus);

  if (r < 0) {
    fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-r));
    exit(0);
  }

  // lrc parse
  char path[] = "/home/ismael/Extra/Repositorios/Mios/waybar-lrc/lrc/circle.lrc";
  char* buffer = loadlrc(path);
  return 0;
}
