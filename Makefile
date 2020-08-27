FLAGS := -std=c99 -pedantic -Wall -Wextra
CFLAGS := ${FLAGS} -fPIC -g
LDFLAGS := ${CFLAGS} -shared

SRC = ${wildcard src/*.c}
OBJ = ${SRC:.c=.o}

all: a.out

update:
	git submodule update --init --recursive

libs/radix/libradix.a: update
	${MAKE} libradix.a -C libs/radix

libs/surrender/libsurrender.a: update
	${MAKE} libsurrender.a -C libs/surrender

a.out: ${OBJ} libs/surrender/libsurrender.a libs/radix/libradix.a
	${CC} $^ -lSDL2 -lm ${CFLAGS}

clean:
	rm -f a.out ${OBJ}
	${MAKE} clean -C libs/surrender
	${MAKE} clean -C libs/radix

.PHONY: update all clean
