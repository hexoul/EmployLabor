#ifndef H_PERIPH
#define H_PERIPH

#define PBASE 0x3F000000

#define ARM_TIMER_CTL   (PBASE+0x0000B408)
#define ARM_TIMER_CNT   (PBASE+0x0000B420)
#define ARM_TIMER_BASE	(PBASE+0x00003000)

/* The base address of the GPIO peripheral (ARM Physical Address) */
#define GPIO_BASE		0x3f200000	/* GPIO base address for rpi3 */
#define GPSET0_OFFSET	0x07		/* GPIO Pin Output Set 0 Offset */
#define GPCLR0_OFFSET	0x0a		/* GPIO Pin Output Clear 0 Offset */

#define RESET_GPIO(idx)	gpio[(idx/10)] &= ~(7 << (idx%10)*3)
#define ACT_GPIO(idx)	gpio[(idx/10)] |= (1 << (idx%10)*3)
#define GPIO_SET(idx)	gpio[GPSET0_OFFSET] |= (1 << idx)
#define GPIO_CLR(idx)	gpio[GPCLR0_OFFSET] &= (1 << idx)

/* For timer */
typedef struct {
    volatile unsigned int control_status;
    volatile unsigned int counter_lo;
    volatile unsigned int counter_hi;
    volatile unsigned int compare0;
    volatile unsigned int compare1;
    volatile unsigned int compare2;
    volatile unsigned int compare3;
} rpi_sys_timer_t;

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );

extern void timer_init ( void );
extern unsigned int timer_tick ( void );
extern void timer_wait_ms ( unsigned int us );

extern void SetActLEDState ( unsigned int );

#endif