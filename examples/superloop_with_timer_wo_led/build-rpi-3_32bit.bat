set target=ex4
set cc=arm-none-eabi

%cc%-as start.s -o start.o

%cc%-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding -c %target%.c -o %target%.o
%cc%-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding -c periph.c -o periph.o

%cc%-ld start.o periph.o %target%.o -T memmap -o %target%.elf
%cc%-objdump -D %target%.elf > %target%.list

%cc%-objcopy %target%.elf -O binary kernel7.img
%cc%-objcopy %target%.elf -O ihex %target%.hex