#ifndef IDT_H
#define IDT_H

#include <screen.h>
#include <io.h>

extern void int_general();		// Default interrupt routine
extern void int_0();
extern void int_1();
extern void int_2();
extern void int_3();
extern void int_4();
extern void int_5();
extern void int_6();
extern void int_7();
extern void int_8();
extern void int_9();
extern void int_10();
extern void int_11();
extern void int_12();
extern void int_13();
extern void int_14();
extern void int_15();
extern void int_16();
extern void int_17();
extern void int_18();
extern void int_19();
extern void int_20();
extern void int_21();
extern void int_22();
extern void int_23();
extern void int_24();
extern void int_25();
extern void int_26();
extern void int_27();
extern void int_28();
extern void int_29();
extern void int_30();
extern void int_31();
extern void int_32();
extern void int_33(int a);			// Keyboard interrupt
extern void int_34();
extern void int_35();
extern void int_36();
extern void int_37();
extern void int_38();
extern void int_39();
extern void int_40();
extern void int_41();
extern void int_42();
extern void int_43();
extern void int_44();
extern void int_45();
extern void int_46();
extern void int_47();

struct idtstruct {
	unsigned short offset1;
	unsigned short selector;
	unsigned char unused;
	unsigned char flag;
	unsigned short offset2;
} __attribute__((packed));		// Packed to avoid padding

struct idtpointer {
	unsigned short size;
	unsigned int offset;	
} __attribute__((packed));		// Packed to avoid padding


static struct idtstruct idttable[256];	// Define the idt struct

void remappic();
void isr_general();
void isr_0();
void isr_1();
void isr_2();
void isr_3();
void isr_4();
void isr_5();
void isr_6();
void isr_7();
void isr_8();
void isr_9();
void isr_10();
void isr_11();
void isr_12();
void isr_13();
void isr_14();
void isr_15();
void isr_16();
void isr_17();
void isr_18();
void isr_19();
void isr_20();
void isr_21();
void isr_22();
void isr_23();
void isr_24();
void isr_25();
void isr_26();
void isr_27();
void isr_28();
void isr_29();
void isr_30();
void isr_31();
void isr_32();
void isr_33();
void isr_34();
void isr_35();
void isr_36();
void isr_37();
void isr_38();
void isr_39();
void isr_40();
void isr_41();
void isr_42();
void isr_43();
void isr_44();
void isr_45();
void isr_46();
void isr_47();
void idt_entry(unsigned int entry, void* offset, unsigned short selector, unsigned char flag);

void idt_init();
#endif //IDT_H
