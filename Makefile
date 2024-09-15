export ARCH = i686
export ARCH_DIR = x86

export DIST = $(shell mkdir -p dist/{arch,core} && realpath dist)
export ARCH_DIST = $(realpath ${DIST}/arch)
export CORE_DIST = $(realpath ${DIST}/core)

export ARCH_O_FILES = $(wildcard ${ARCH_DIST}/*.o)
export CORE_O_FILES = $(wildcard ${CORE_DIST}/*.o)

build:
	mkdir -p ./dist
	make -C core build
	make -C installer build

run-img:
	make -C . build
	qemu-system-i386 -drive file=./dist/disk.img,format=raw,index=0,media=disk

debug-img:
	make -C . build
	xterm -e gdb -iex "add-auto-load-safe-path .gdbinit" &
	qemu-system-i386 -drive file=./dist/disk.img,format=raw,index=0,media=disk -s -S

run-iso:
	make -C . build
	qemu-system-i386 -boot d -cdrom ./dist/build.iso

debug-iso:
	make -C . build
	xterm -e gdb -iex "add-auto-load-safe-path .gdbinit" &
	qemu-system-i386 -boot d -cdrom ./dist/build.iso -s -S

clean:
	-rm -rf ${DIST}