arm-none-eabi-as start.s -o start.o

arm-none-eabi-gcc -Wall -O2 -nostdlib -nostartfiles -ffreestanding -c ex1.c -o ex1.o

arm-none-eabi-ld start.o ex1.o -T memmap -o ex1.elf
arm-none-eabi-objdump -D ex1.elf > ex1.list

arm-none-eabi-objcopy ex1.elf -O binary kernel8.img
arm-none-eabi-objcopy ex1.elf -O ihex ex1.hex