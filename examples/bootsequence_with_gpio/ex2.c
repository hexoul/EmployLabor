
/* The base address of the GPIO peripheral (ARM Physical Address) */
#define GPIO_BASE		0x3f200000	/* GPIO base address for rpi3 */
#define GPSET0_OFFSET		0x07		/* GPIO Pin Output Set 0 Offset */
#define GPCLR0_OFFSET		0x0a		/* GPIO Pin Output Clear 0 Offset */

#define RESET_GPIO(idx)	gpio[(idx/10)] &= ~(7 << (idx%10)*3)
#define ACT_GPIO(idx)	gpio[(idx/10)] |= (1 << (idx%10)*3)
#define SET_GPIO(idx)	gpio[GPSET0_OFFSET] |= (1 << idx)
#define CLR_GPIO(idx)	gpio[GPCLR0_OFFSET] &= (1 << idx)

/* GPIO Register set */
volatile unsigned int* gpio;

#define TARGET_PIN		13

#define TRUE	1
#define	FALSE	0

int _start ( void )
{
	/* Assign the address of the GPIO peripheral (Using ARM Physical Address) */
	gpio = (unsigned int*)GPIO_BASE;

	/* Reset GPIO */
	RESET_GPIO(TARGET_PIN);
	/* Activate GPIO as OUTPUT */
	ACT_GPIO(TARGET_PIN);

	/* Set HIGH to GPIO */
	SET_GPIO(TARGET_PIN);

	while(TRUE)
	{
	}

	return (0);
}
