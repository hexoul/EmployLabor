ARMGNU ?= arm-none-eabi
COPS = -Wall -O0 -nostdlib -nostartfiles -ffreestanding

TARGET = ex6

all : 
	$(ARMGNU)-gcc $(COPS) $(TARGET).c -o kernel.elf
	$(ARMGNU)-objcopy kernel.elf -O binary kernel.img

clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.img

