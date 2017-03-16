#include "periph.h"

/* GPIO Register set */
volatile unsigned int* gpio;

#define TARGET_PIN	13

/*
 * 1000 = 1ms
 * 1000000 = 1s
 */
#define HALF_SEC	500000
#define TWO_SEC		2000000

#define	TRUE	1
#define	FALSE	0

int _start ( void )
{
	/* Assign the address of the GPIO peripheral (Using ARM Physical Address) */
	gpio = (unsigned int*)GPIO_BASE;

	/* Reset GPIO */
	RESET_GPIO(TARGET_PIN);
	/* Activate GPIO as OUTPUT */
	ACT_GPIO(TARGET_PIN);

	/* Initiate Timer */
	timer_init();

	while(TRUE)
	{
		/* Set HIGH to GPIO */
		GPIO_SET(TARGET_PIN);
		/* Wait half second */
		timer_wait_ms(TWO_SEC);

		/* Set LOW to GPIO */
		GPIO_CLR(TARGET_PIN);
		/* Wait half second */
		timer_wait_ms(TWO_SEC);
	}

	return (0);
}
