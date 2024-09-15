[global apm_real_mode]

DATA_SEG_ADDRESS equ 0x7001
[bits 16]

apm_power_off:
    mov ah,53h              ;this is an APM command
    mov al,07h              ;Set the power state...
    mov bx,0001h            ;...on all devices to...
    mov cx,03h              ;see above
    int 15h                 ;call the BIOS function through interrupt 15h

idt_real:
	dw 0x3ff		; 256 entries, 4b each = 1K
	dd 0			; Real Mode IVT @ 0x0000
	jmp apm_power_off

savcr0:
	dd 0			; Storage location for pmode CR0.

apm_real_mode:
        ; We are already in 16-bit mode here!

	cli			; Disable interrupts.

	; Need 16-bit Protected Mode GDT entries!
	mov eax, [DATA_SEG_ADDRESS]	; 16-bit Protected Mode data selector.
	mov ds, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	mov ss, eax


	; Disable paging (we need everything to be 1:1 mapped).
	mov eax, cr0
	mov [savcr0], eax	; save pmode CR0
	and eax, 0x7FFFFFFe	; Disable paging bit & disable 16-bit pmode.
	mov cr0, eax

	jmp 0:GoRMode		; Perform Far jump to set CS.

GoRMode:
	mov sp, 0x8000		; pick a stack pointer.
	mov ax, 0		; Reset segment registers to 0.
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	lidt [idt_real]
	sti			; Restore interrupts -- be careful, unhandled int's will kill it.