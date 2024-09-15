target remote localhost:1234
set architecture i8086
display /i ($cs*16)+$pc
br *0x7c00
br *0x7e00
br *0x8000
cont
