C_FILES = $(wildcard *.c)
CPP_FILES = $(wildcard *.cpp)

build:
	${GCC} ${C_FLAGS} -c ${C_FILES}
	mv *.o ${ARCH_DIST}

clean:
	-rm *.o