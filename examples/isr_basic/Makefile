ARMGNU ?= arm-none-eabi
COPS = -Wall -O0 -nostdlib -nostartfiles -ffreestanding

TARGET = ex4

all : 
	$(ARMGNU)-as start.s mailbox.s led.s -o start.o
	$(ARMGNU)-gcc $(COPS) -c $(TARGET).c -o kernel.o
	$(ARMGNU)-ld start.o kernel.o -T memmap -o kernel.elf
	$(ARMGNU)-objcopy kernel.elf -O binary kernel.img

clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.img

