ENTRY(main)
SEARCH_DIR(dist)
OUTPUT_FORMAT(binary)
OUTPUT(kernel.bin)

SECTIONS {
        .text 0x8000: {
            core.o(.text*)
        }

        .text : {
            arch.o(.text*)
        }

        .text : { *(.text) }
        .rodata : { *(.rodata) }
        .data : { *(.data) }
}