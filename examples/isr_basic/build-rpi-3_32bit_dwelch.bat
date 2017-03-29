set cc=arm-none-eabi
set target=ex10_dwelch

%cc%-as start_dwelch.s mailbox.s led.s -o start.o

%cc%-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding -c %target%.c -o %target%.o
%cc%-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding -c periph.c -o periph.o

%cc%-ld start.o periph.o %target%.o -o %target%.elf

%cc%-objcopy %target%.elf -O binary kernel.img