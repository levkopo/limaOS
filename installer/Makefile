build:
	mkdir -p iso/lmiso
	cp ../dist/kernel.bin iso/lmiso/boot.bin
	xorriso -as mkisofs \
			-b boot.bin \
			-no-emul-boot \
			-boot-load-size 4 \
			-boot-info-table \
			--protective-msdos-label \
			iso/lmiso -o ../dist/build.iso