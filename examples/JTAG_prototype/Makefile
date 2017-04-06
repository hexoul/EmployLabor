cc=aarch64-linux-gnu

target=jtag0

all:
	${cc}-as start.s -o start.o
	${cc}-gcc -Wall -O0 -ggdb3 -nostdlib -nostartfiles -ffreestanding -c ${target}.c -o ${target}.o
	${cc}-ld start.o ${target}.o -T memmap -o ${target}.elf
	${cc}-objcopy ${target}.elf -O binary kernel.img
