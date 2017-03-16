set cc=arm-none-eabi
set target=ex6

%cc%-as start.s mailbox.s led.s -o start.o

%cc%-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding -c %target%.c -o %target%.o

%cc%-ld start.o %target%.o -T memmap -o %target%.elf

%cc%-objcopy %target%.elf -O binary kernel.img
