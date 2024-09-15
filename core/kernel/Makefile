C_FILES = $(wildcard *.c)

build:
	# Compile main kernel code
	${GCC} ${C_FLAGS} -c ${C_FILES}

	# Move results to core destination folder
	mv *.o ${CORE_DIST}

clean:
	-rm *.o