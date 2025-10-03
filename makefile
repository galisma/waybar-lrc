CC       ?= clang
CFLAGS   ?= -Wall -O2 -Isrc $(shell pkg-config --cflags libsystemd)
SOURCES  := $(wildcard src/*.c)
LDLIBS   := $(shell pkg-config --libs libsystemd)
BUILDIR  := build
BINARY   := waybar-module
RUNFLAGS := lrc/circle.lrc

OBJECTS  := $(SOURCES:src/%.c=${BUILDIR}/%.o)

.PHONY: all run clean

all: ${BUILDIR}/${BINARY}

${BUILDIR}/${BINARY}: ${OBJECTS}
	@echo "Enlazando binario..."
	${CC} ${OBJECTS} -o $@ ${LDLIBS}

${BUILDIR}/%.o: src/%.c | ${BUILDIR}
	@echo "Compilando $<..."
	${CC} ${CFLAGS} -c $< -o $@

${BUILDIR}:
	@mkdir -p $@

run: ${BUILDIR}/${BINARY}
	@echo "Ejecutando ${BINARY}..."
	@./${BUILDIR}/${BINARY} ${RUNFLAGS}
clean:
	@echo "Limpiando archivos de construcción..."
	@rm -rf ${BUILDIR} 
