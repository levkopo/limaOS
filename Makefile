build:
	mkdir -p ./dist
	make -C ./kernel build
	make -C ./bootloader build
	dd if=./iso/kernel.bin of=kernel.bin conv=sync &> /dev/null && sync
	cat ./iso/bootloader.bin ./kernel.bin > os.bin
	dd if=os.bin of=disk.img conv=notrunc
	mkfs.vfat -F 32 disk.img
	rm -d -r ./iso
	mv disk.img ./dist/disk.img
	mv os.bin ./dist/os.bin

run:
	make -C . build
	qemu-system-i386 disk.img