
/* The base address of the GPIO peripheral (ARM Physical Address) */
#define GPIO_BASE		0x3f200000	/* GPIO base address for rpi3 */
#define GPSET0_OFFSET		0x07		/* GPIO Pin Output Set 0 Offset */
#define GPCLR0_OFFSET		0x0a		/* GPIO Pin Output Clear 0 Offset */
#define GPLEV0_OFFSET		0x0d		/* GPIO Pin Input Level 0 */

#define RESET_GPIO(idx)	gpio[(idx/10)] &= ~(7 << (idx%10)*3)
#define ACT_GPIO(idx)	gpio[(idx/10)] |= (1 << (idx%10)*3)
#define SET_GPIO(idx)	gpio[GPSET0_OFFSET] |= (1 << idx)
#define CLR_GPIO(idx)	gpio[GPCLR0_OFFSET] &= (1 << idx)
#define READ_GPIO(idx)	(gpio[GPLEV0_OFFSET] >> idx)

/* GPIO Register set */
volatile unsigned int* gpio;

#define TARGET_PIN_IN		12
#define TARGET_PIN_OUT		13

#define TRUE	1
#define	FALSE	0

int _start ( void )
{
	/* Assign the address of the GPIO peripheral (Using ARM Physical Address) */
	gpio = (unsigned int*)GPIO_BASE;

	/* Reset GPIO */
	RESET_GPIO(TARGET_PIN_IN);
	RESET_GPIO(TARGET_PIN_OUT);
	/* Activate GPIO as OUTPUT */
	ACT_GPIO(TARGET_PIN_OUT);

	while(TRUE)
	{
		if(READ_GPIO(TARGET_PIN_IN) & TRUE)
		{
			/* Set HIGH to GPIO */
			SET_GPIO(TARGET_PIN_OUT);
		}
		else
		{
			/* Set LOW to GPIO */
			CLR_GPIO(TARGET_PIN_OUT);
		}
	}

	return (0);
}
