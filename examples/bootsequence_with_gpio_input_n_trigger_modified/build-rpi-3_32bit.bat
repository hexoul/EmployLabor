set cc=arm-none-eabi
set target=ex4

%cc%-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding %target%.c -o %target%.elf

%cc%-objcopy %target%.elf -O binary kernel.img
