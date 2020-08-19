FLAGS := -std=c99 -pedantic -Wall -Wextra -Wl, --allow-multiple-definition
CFLAGS := ${FLAGS} -fPIC -Ofast -g -march=core2 -mtune=generic -lm
LDFLAGS := ${CFLAGS} -shared

SRC = ${wildcard src/*.c}
OBJ = ${SRC:.c=.o}

all: a.out

libradix.a:
	cd libs/radix
	make libradix.a
	mv libradix.a ../..
	cd ../..

libsurrender.a:
	cd libs/surrender
	./build_deps.sh
	mv libsurrender.a ../..
	cd ../..

a.out: main.c libsurrender.a libradix.a
	${CC} $^ -lSDL2 ${CFLAGS}

clean:
	rm -f a.out lib*.* ${OBJ}

.PHONY: all clean
