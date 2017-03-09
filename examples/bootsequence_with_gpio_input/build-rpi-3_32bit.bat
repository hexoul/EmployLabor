set target=ex2
set cc=c:\GNU\v47\bin\arm-none-eabi

%cc%-as start.s mailbox.s led.s -o start.o

%cc%-gcc -Wall -O0 -nostdlib -nostartfiles -ffreestanding -c %target%.c -o %target%.o

%cc%-ld start.o %target%.o -T memmap -o %target%.elf
%cc%-objdump -D %target%.elf > %target%.list

%cc%-objcopy %target%.elf -O binary kernel7.img
%cc%-objcopy %target%.elf -O ihex %target%.hex