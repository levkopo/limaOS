#include <panic.h>
#include "include/IDT.h"

char __currentChar = -1;

void idt_init() {
    unsigned int i;
    remappic();
    struct idtpointer idt;			// Contains the struct being loaded by lidt

    idt_entry(0, &int_0, 0x08, 0x8E);	// Flag indicates an interrupt gate
    idt_entry(1, &int_1, 0x08, 0x8E);
    idt_entry(2, &int_2, 0x08, 0x8E);
    idt_entry(3, &int_3, 0x08, 0x8E);
    idt_entry(4, &int_4, 0x08, 0x8E);
    idt_entry(5, &int_5, 0x08, 0x8E);
    idt_entry(6, &int_6, 0x08, 0x8E);
    idt_entry(7, &int_7, 0x08, 0x8E);
    idt_entry(8, &int_8, 0x08, 0x8E);
    idt_entry(9, &int_9, 0x08, 0x8E);
    idt_entry(10, &int_10, 0x08, 0x8E);
    idt_entry(11, &int_11, 0x08, 0x8E);
    idt_entry(12, &int_12, 0x08, 0x8E);
    idt_entry(13, &int_13, 0x08, 0x8E);
    idt_entry(14, &int_14, 0x08, 0x8E);
    idt_entry(15, &int_15, 0x08, 0x8E);
    idt_entry(16, &int_16, 0x08, 0x8E);
    idt_entry(17, &int_17, 0x08, 0x8E);
    idt_entry(18, &int_18, 0x08, 0x8E);
    idt_entry(19, &int_19, 0x08, 0x8E);
    idt_entry(20, &int_20, 0x08, 0x8E);
    idt_entry(21, &int_21, 0x08, 0x8E);
    idt_entry(22, &int_22, 0x08, 0x8E);
    idt_entry(23, &int_23, 0x08, 0x8E);
    idt_entry(24, &int_24, 0x08, 0x8E);
    idt_entry(25, &int_25, 0x08, 0x8E);
    idt_entry(26, &int_26, 0x08, 0x8E);
    idt_entry(27, &int_27, 0x08, 0x8E);
    idt_entry(28, &int_28, 0x08, 0x8E);
    idt_entry(29, &int_29, 0x08, 0x8E);
    idt_entry(30, &int_30, 0x08, 0x8E);
    idt_entry(31, &int_31, 0x08, 0x8E);
    idt_entry(32, &int_32, 0x08, 0x8E);
    idt_entry(33, &int_33, 0x08, 0x8E);
    idt_entry(34, &int_34, 0x08, 0x8E);
    idt_entry(35, &int_35, 0x08, 0x8E);
    idt_entry(36, &int_36, 0x08, 0x8E);
    idt_entry(37, &int_37, 0x08, 0x8E);
    idt_entry(38, &int_38, 0x08, 0x8E);
    idt_entry(39, &int_39, 0x08, 0x8E);
    idt_entry(40, &int_40, 0x08, 0x8E);
    idt_entry(41, &int_41, 0x08, 0x8E);
    idt_entry(42, &int_42, 0x08, 0x8E);
    idt_entry(43, &int_43, 0x08, 0x8E);
    idt_entry(44, &int_44, 0x08, 0x8E);
    idt_entry(45, &int_45, 0x08, 0x8E);
    idt_entry(46, &int_46, 0x08, 0x8E);
    idt_entry(47, &int_47, 0x08, 0x8E);

    for(i = 48; i < 256; i++)	// Fill in the remaining entries with a standard isr
    {
        idt_entry(i, &int_general, 0x08, 0x8E);
    }

    idt.size = sizeof(idttable) - 1;		// Size of the IDT
    idt.offset = (unsigned int)&idttable;		// Pointer to the IDT

    asm("lidt (%0)" : : "p"(&idt));			// Load the IDT struct
}

void idt_entry(unsigned int entry, void* offset, unsigned short selector, unsigned char flag) {
    unsigned int offsetinteger = (unsigned int)offset;
    idttable[entry].offset1 = offsetinteger & 0xFFFF;
    idttable[entry].selector = selector;
    idttable[entry].unused = 0;
    idttable[entry].flag = flag;
    idttable[entry].offset2 = (offsetinteger >> 16) & 0xFFFF;
}

void isr_general(){
    write_port(0x20, 0x20);
    println_string("isr_general was called");
}
void isr_0(){
    write_port(0x20,0x20);
    println_string("isr_0 : Divide Error was called");
}
void isr_1(){
    write_port(0x20,0x20);
    println_string("isr_1 : Debug Exceptions was called");
}
void isr_2(){
    write_port(0x20,0x20);
    println_string("isr_2 : Intel Reserved was called");
}
void isr_3(){
    write_port(0x20,0x20);
    println_string("isr_3 : Breakpoint was called");
}
void isr_4(){
    write_port(0x20,0x20);
    println_string("isr_4 : Overflow was called");
}
void isr_5(){
    write_port(0x20,0x20);
    println_string("isr_5 : Bounds Check was called");
}
void isr_6(){
    write_port(0x20,0x20);
    panic("Invalid Opcode");
}
void isr_7(){
    write_port(0x20,0x20);
    println_string("isr_7 : Coprocessor Not Available was called");
}
void isr_8(){
    write_port(0x20,0x20);
    println_string("isr_8 : Double Fault was called");
}
void isr_9(){
    write_port(0x20,0x20);
    println_string("isr_9 : Coprocessor Segment Overrun was called");
}
void isr_10(){
    write_port(0x20,0x20);
    println_string("isr_10 : Invalid TSS was called");
}
void isr_11(){
    write_port(0x20,0x20);
    println_string("isr_11 : Segment Not Present was called");
}
void isr_12(){
    write_port(0x20,0x20);
    println_string("isr_12 : Stack Exception was called");
}
void isr_13(){
    write_port(0x20,0x20);
    panic("General Protection Exception (Triple Fault)");
}
void isr_14(){
    write_port(0x20,0x20);
    panic("Page Fault");
}
void isr_15(){
    write_port(0x20,0x20);
    println_string("isr_15 Intel Reserved was called");
}
void isr_16(){
    write_port(0x20,0x20);
    panic("Coprocessor Error was called");
}

void isr_17(){
    write_port(0x20,0x20);
    println_string("isr_17 was called");
}

void isr_18(){
    write_port(0x20,0x20);
    println_string("isr_18 was called");
}

void isr_19(){
    write_port(0x20,0x20);
    println_string("isr_19 was called");
}
void isr_20(){
    write_port(0x20,0x20);
    println_string("isr_20 was called");
}
void isr_21(){
    write_port(0x20,0x20);
    println_string("isr_21 was called");
}
void isr_22(){
    write_port(0x20,0x20);
    println_string("isr_22 was called");
}
void isr_23(){
    write_port(0x20,0x20);
    println_string("isr_23 was called");
}
void isr_24(){
    write_port(0x20,0x20);
    println_string("isr_24 was called");
}
void isr_25(){
    write_port(0x20,0x20);
    println_string("isr_25 was called");
}
void isr_26(){
    write_port(0x20,0x20);
    println_string("isr_26 was called");
}
void isr_27(){
    write_port(0x20,0x20);
    println_string("isr_27 was called");
}
void isr_28(){
    write_port(0x20,0x20);
    println_string("isr_28 was called");
}
void isr_29(){
    write_port(0x20,0x20);
    println_string("isr_29 was called");
}
void isr_30(){
    write_port(0x20,0x20);
    println_string("isr_30 was called");
}
void isr_31(){
    write_port(0x20,0x20);
    println_string("isr_31 was called");
}

void isr_32(){
    write_port(0x20,0x20);
//	pitCall(); TODO:
//	println_string("isr_32 (IRQ 0: Programmable Interrupt Timer) was called");
}

void isr_33() {
//    uint8_t scancode = read_port(0x60);
//
//    struct KeyboardKey key = getchar_keyboard(scancode);
//    if(scancode!=0) __currentChar = key.key;
//    else __currentChar = -1;
//
//    write_port(0x60, 0);
}

void isr_34(){
    write_port(0x20,0x20);
    println_string("isr_34 (IRQ 2: Cascade [used by PICS]) was called");
}
void isr_35(){
    write_port(0x20,0x20);
    println_string("isr_35 (IRQ 3: COM2) was called");
}
void isr_36(){
    write_port(0x20,0x20);
    println_string("isr_36 (IRQ 4: COM1) was called");
}
void isr_37(){
    write_port(0x20,0x20);
    println_string("isr_37 (IRQ 5: LPT2) was called");
}
void isr_38(){
    write_port(0x20,0x20);
    println_string("isr_38 (IRQ 6: Floppy Disk) was called");
}
void isr_39(){
    write_port(0x20,0x20);
    println_string("isr_39 (IRQ 7: LPT1 / spurious interrupt) was called");
}
void isr_40(){
    write_port(0xA0,0x20);
    write_port(0x20,0x20);
    //by reading register C, the interrupt will happen again
    write_port(0x70,0x0C);
    read_port(0x71);
//	rtcCall();
    println_string("isr_40 (RTC) was called");
}
void isr_41(){
    write_port(0xA0,0x20);
    write_port(0x20,0x20);
    println_string("isr_41 (IRQ 9: Free for peripherals) was called");
}
void isr_42(){
    write_port(0xA0,0x20);
    write_port(0x20,0x20);
    println_string("isr_42 (IRQ 10: Free for peripherals) was called");
}
void isr_43(){
    write_port(0xA0,0x20);
    write_port(0x20,0x20);
    println_string("isr_43 (IRQ 11: Free for peripherals) was called");
}
void isr_44(){
    write_port(0xA0,0x20);
    write_port(0x20,0x20);
    println_string("isr_44 (IRQ 12: PS2 Mouse) was called");
}
void isr_45(){
    write_port(0xA0,0x20);
    write_port(0x20,0x20);
    println_string("isr_45 (IRQ 13: FPU / Coprocessor / Inter-processor) was called");
}
void isr_46(){
    write_port(0xA0,0x20);
    write_port(0x20,0x20);
    println_string("isr_46 (IRQ 14: Primary ATA Hard Disk) was called");
}
void isr_47(){
    write_port(0xA0,0x20);
    write_port(0x20,0x20);
    println_string("isr_47 (IRQ 15: Secondary ATA Hard Disk) was called");
}


void remappic(){
    write_port(0x20, 0x11);		// Initilisation instruction
    write_port(0xA0, 0x11);

    write_port(0x21, 0x20);		// Map the first 8 interrupts to 0x20
    write_port(0xA1, 0x28);		// Map 8 - 15 interrupts to 0x28

    write_port(0x21, 0x04);		// Tell the pic how its connected
    write_port(0xA1, 0x02);

    write_port(0x21, 0x01);		// Tell the mode it is operating in
    write_port(0xA1, 0x01);

    //write_port(0x21, 0xfd);
    //write_port(0xA1, 0xff);
    write_port(0x21, 0x0);
    write_port(0xA1, 0x0);
}