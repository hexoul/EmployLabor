ARMGNU ?= arm-none-eabi
COPS = -Wall -O0 -nostdlib -nostartfiles -ffreestanding

TARGET = ex7

all : 
	$(ARMGNU)-gcc $(COPS) periph.c $(TARGET).c -o $(TARGET).elf
	$(ARMGNU)-objcopy $(TARGET).elf -O binary kernel.img

clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.img

