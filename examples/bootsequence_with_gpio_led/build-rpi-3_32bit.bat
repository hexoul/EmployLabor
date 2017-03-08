set target=ex2

arm-none-eabi-as start.s mailbox.s led.s -o start.o

arm-none-eabi-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding -c %target%.c -o %target%.o

arm-none-eabi-ld start.o %target%.o -T memmap -o %target%.elf
arm-none-eabi-objdump -D %target%.elf > %target%.list

arm-none-eabi-objcopy %target%.elf -O binary kernel7.img
arm-none-eabi-objcopy %target%.elf -O ihex %target%.hex