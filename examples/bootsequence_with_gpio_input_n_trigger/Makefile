ARMGNU ?= arm-none-eabi
COPS = -Wall -O0 -nostdlib -nostartfiles -ffreestanding

TARGET = ex4

all : 
	$(ARMGNU)-gcc $(COPS) $(TARGET).c -o $(TARGET).elf
	$(ARMGNU)-objcopy $(TARGET).elf -O binary kernel.img

clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.img

