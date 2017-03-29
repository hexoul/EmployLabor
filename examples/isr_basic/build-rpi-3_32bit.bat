set cc=arm-none-eabi
set target=ex10

%cc%-as start.s mailbox.s led.s -o start.o

%cc%-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding -c %target%.c -o %target%.o
%cc%-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding -c periph.c -o periph.o
%cc%-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding -c rpi-interrupts.c -o rpi-interrupts.o
%cc%-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding -c rpi-armtimer.c -o rpi-armtimer.o

%cc%-ld start.o periph.o rpi-interrupts.o rpi-armtimer.o %target%.o -o %target%.elf

%cc%-objcopy %target%.elf -O binary kernel.img