# Configuración de construcción (debug/release)
# Para cambiar: make CONFIG=debug
CONFIG ?= debug

# Compilador y banderas base
CC       ?= clang
CFLAGS   ?= -Wall -Isrc $(shell pkg-config --cflags libsystemd)
SOURCES  := $(wildcard src/*.c)
LDLIBS   := $(shell pkg-config --libs libsystemd)
BUILDIR  := build/$(CONFIG)
BINARY   := waybar-module
RUNFLAGS := lrc/circle.lrc

OBJECTS  := $(SOURCES:src/%.c=$(BUILDIR)/%.o)

# Configuración específica para Debug/Release
ifeq ($(CONFIG),debug)
  CFLAGS += -O0 -g -DDEBUG
else ifeq ($(CONFIG),release)
  CFLAGS += -O2 -DNDEBUG
else
  $(error CONFIG debe ser "debug" o "release")
endif

.PHONY: all run debug release clean

all: $(BUILDIR)/$(BINARY)

debug:
	@$(MAKE) CONFIG=debug

release:
	@$(MAKE) CONFIG=release

$(BUILDIR)/$(BINARY): $(OBJECTS)
	@echo "Enlazando binario ($(CONFIG))..."
	$(CC) $(OBJECTS) -o $@ $(LDLIBS)

$(BUILDIR)/%.o: src/%.c | $(BUILDIR)
	@echo "Compilando $< ($(CONFIG))..."
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDIR):
	@mkdir -p $@

run: $(BUILDIR)/$(BINARY)
	@echo "Ejecutando $(BINARY) ($(CONFIG))..."
	@./$(BUILDIR)/$(BINARY) $(RUNFLAGS)

clean:
	@echo "Limpiando archivos de construcción..."
	@rm -rf build
