export GCC = gcc
export GPP = g++
export LD = ld

export BASE_C_FLAGS = -w -m32 -fno-pie -ffreestanding -fno-stack-protector -nostdlib -nostdinc
export INCLUDE_C_FLAGS = -I$(realpath ./include) -I$(realpath ./arch/${ARCH_DIR}/include)
export C_FLAGS = ${BASE_C_FLAGS} ${INCLUDE_C_FLAGS}

build:
	# Build arch specific kernel code
	make -C ./arch/${ARCH_DIR} build

	# Build asm
	make -C asm build

	# Build kernel
	make -C kernel build

	ld -m elf_i386 -L ${DIST} -T linker.ld ${ARCH_O_FILES} ${CORE_O_FILES}

	mv kernel.bin  ${DIST}/kernel.bin
	cat ${DIST}/bootloader.bin ${DIST}/kernel.bin > ${DIST}/disk.img

clean:
	-rm -rf *.o
	-rm -rf *.bin
	make -C ./arch/${ARCH_DIR} clean
	make -C asm clean
	make -C kernel clean


#build:
