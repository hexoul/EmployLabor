#ifndef H_PERIPH
#define H_PERIPH

#define PBASE 0x3F000000

#define ARM_TIMER_BASE	(PBASE+0x00003000)
#define ARM_TIMER_CNT   (PBASE+0x0000B420)
#define ARM_TIMER_LOD	(PBASE+0x0000B400)
#define ARM_TIMER_VAL	(PBASE+0x0000B404)
#define ARM_TIMER_CTL   (PBASE+0x0000B408)
#define ARM_TIMER_CLI	(PBASE+0x0000B40C)
#define ARM_TIMER_RIS	(PBASE+0x0000B410)
#define ARM_TIMER_MIS	(PBASE+0x0000B414)
#define ARM_TIMER_RLD	(PBASE+0x0000B418)
#define ARM_TIMER_DIV	(PBASE+0x0000B41C)

/* The base address of the GPIO peripheral (ARM Physical Address) */
#define GPIO_BASE		(PBASE+0x00200000)	/* GPIO base address for rpi3 */
#define GPSET0_OFFSET	0x07				/* GPIO Pin Output Set 0 Offset */
#define GPCLR0_OFFSET	0x0a				/* GPIO Pin Output Clear 0 Offset */

#define RESET_GPIO(idx)	gpio[(idx/10)] &= ~(7 << (idx%10)*3)
#define ACT_GPIO(idx)	gpio[(idx/10)] |= (1 << (idx%10)*3)
#define GPIO_SET(idx)	gpio[GPSET0_OFFSET] |= (1 << idx)
#define GPIO_CLR(idx)	gpio[GPCLR0_OFFSET] &= (1 << idx)

#define IRQ_BASIC 0x3F00B200
#define IRQ_PEND1 0x3F00B204
#define IRQ_PEND2 0x3F00B208
#define IRQ_FIQ_CONTROL 0x3F00B210
#define IRQ_ENABLE_BASIC 0x3F00B218
#define IRQ_DISABLE_BASIC 0x3F00B224

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

extern void setActLEDState ( unsigned int );

extern void enable_irq ( void );

#endif