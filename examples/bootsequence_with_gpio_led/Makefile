ARMGNU ?= arm-none-eabi
COPS = -Wall -O0 -nostdlib -nostartfiles -ffreestanding

TARGET = ex5

all : 
	$(ARMGNU)-as start.s mailbox.s led.s -o start.o
	$(ARMGNU)-gcc $(COPS) -c $(TARGET).c -o kernel.o
	$(ARMGNU)-ld start.o kernel.o -T memmap -o $(TARGET).elf
	$(ARMGNU)-objcopy $(TARGET).elf -O binary kernel.img

clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.img

