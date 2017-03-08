set target=ex1

arm-none-eabi-as start.s -o start.o

arm-none-eabi-gcc -Wall -O2 -nostdlib -nostartfiles -ffreestanding -c %target%.c -o %target%.o

arm-none-eabi-ld start.o %target%.o -T memmap -o %target%.elf
arm-none-eabi-objdump -D %target%.elf > %target%.list

arm-none-eabi-objcopy %target%.elf -O binary kernel7.img
arm-none-eabi-objcopy %target%.elf -O ihex %target%.hex