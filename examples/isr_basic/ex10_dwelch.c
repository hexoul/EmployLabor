#include "periph.h"

/* GPIO Register set */
volatile unsigned int* gpio;

#define TARGET_PIN		13

#define	TRUE	1
#define	FALSE	0

volatile unsigned int icount;

void c_irq_handler ( void )
{
    icount++;
    if(icount&1)
    {
		setActLEDState(TRUE);
    }
    else
    {
        setActLEDState(FALSE);
    }
    PUT32(ARM_TIMER_CLI,0);
}


int main ( void )
{
	PUT32(ARM_TIMER_CTL,0x003E0000);
    PUT32(ARM_TIMER_LOD,4000000-1);
    PUT32(ARM_TIMER_RLD,4000000-1);
    PUT32(ARM_TIMER_DIV,0x000000F9);
    PUT32(ARM_TIMER_CLI,0);
    PUT32(IRQ_ENABLE_BASIC,1);
    icount=0;
	enable_irq();
    PUT32(ARM_TIMER_CTL,0x003E00A2);
    PUT32(ARM_TIMER_CLI,0);
    while(TRUE) continue;

	return 0;
}