#include "periph.h"
#include "rpi-interrupts.h"
#include "rpi-armtimer.h"

/* GPIO Register set */
volatile unsigned int* gpio;

#define TARGET_PIN		13

/*
 * 1000 = 1ms
 * 1000000 = 1s
 */
#define HALF_SEC	500000
#define TWO_SEC		2000000

#define	TRUE	1
#define	FALSE	0

extern void _enable_interrupts (void);

int main ( void )
{
	/* Enable the timer interrupt IRQ */
	RPI_GetIrqController()->Enable_Basic_IRQs = RPI_BASIC_ARM_TIMER_IRQ;
	
    /* Setup the system timer interrupt */
    /* Timer frequency = Clk/256 * 0x400 */
    RPI_GetArmTimer()->Load = 0x400;

	/* Setup the ARM Timer */
	RPI_GetArmTimer()->Control =
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_256;

	/* Enable interrupts! */
	_enable_interrupts();
	while(TRUE);
	
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
		/* Turn on LED */
		setActLEDState(TRUE);
		/* Set HIGH to GPIO */
		GPIO_SET(TARGET_PIN);
		/* Wait half second */
        timer_wait_ms(HALF_SEC);

		/* Turn off LED */
        setActLEDState(FALSE);
		/* Set LOW to GPIO */
		GPIO_CLR(TARGET_PIN);
		/* Wait half second */
        timer_wait_ms(HALF_SEC);
    }

    return (0);
}