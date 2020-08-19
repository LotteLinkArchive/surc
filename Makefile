FLAGS := -std=c99 -pedantic -Wall -Wextra
CFLAGS := ${FLAGS} -fPIC
LDFLAGS := ${CFLAGS} -shared

SRC = ${wildcard src/*.c}
OBJ = ${SRC:.c=.o}

all: a.out

libs/radix/libradix.a: .gitmodules
	${MAKE} libradix.a -C libs/radix

libs/surrender/libsurrender.a: .gitmodules
	${MAKE} libsurrender.a -C libs/surrender

a.out: ${OBJ} libs/surrender/libsurrender.a libs/radix/libradix.a
	${CC} $^ -lSDL2 ${CFLAGS}

clean:
	rm -f a.out ${OBJ}
	${MAKE} clean -C libs/surrender
	${MAKE} clean -C libs/radix

.PHONY: all clean
