ARMGNU ?= arm-none-eabi
COPS = -Wall -O0 -nostdlib -nostartfiles -ffreestanding

TARGET = ex10

all : 
	$(ARMGNU)-as start.s mailbox.s led.s -o start.o
	$(ARMGNU)-gcc $(COPS) -c $(TARGET).c -o $(TARGET).o
	$(ARMGNU)-gcc $(COPS) -c periph.c -o periph.o
	$(ARMGNU)-gcc $(COPS) -c rpi-interrupts.c -o rpi-interrupts.o
	$(ARMGNU)-gcc $(COPS) -c rpi-armtimer.c -o rpi-armtimer.o
	$(ARMGNU)-ld start.o periph.o rpi-interrupts.o rpi-armtimer.o $(TARGET).o -o kernel.elf
	$(ARMGNU)-objcopy kernel.elf -O binary kernel.img

clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.img

