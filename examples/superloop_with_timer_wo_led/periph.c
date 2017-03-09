#include "periph.h"

static rpi_sys_timer_t* rpiSystemTimer = (rpi_sys_timer_t*)ARM_TIMER_BASE;

void timer_init ( void )
{
    //0xF9+1 = 250
    //250MHz/250 = 1MHz
    PUT32(ARM_TIMER_CTL,0x00F90000);
    PUT32(ARM_TIMER_CTL,0x00F90200);
}

unsigned int timer_tick ( void )
{
    return(GET32(ARM_TIMER_CNT));
}

void timer_wait_ms ( unsigned int us )
{
    volatile unsigned int ts = rpiSystemTimer->counter_lo;

    while( ( rpiSystemTimer->counter_lo - ts ) < us )
    {
        /* BLANK */
    }
}