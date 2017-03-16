set cc=arm-none-eabi
set target=ex7

%cc%-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding periph.c %target%.c -o %target%.elf

%cc%-objcopy %target%.elf -O binary kernel.img
