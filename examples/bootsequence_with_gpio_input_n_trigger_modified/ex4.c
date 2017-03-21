
/* The base address of the GPIO peripheral (ARM Physical Address) */
#define GPIO_BASE	0x3f200000	/* GPIO base address for rpi3 */
/*  Alternate Function Select Register 
 * 	6 registers total (for 54 GPIO pins)
 *	000	input
 *	001 output
 *	100 alt. function 0
 *	101 alt. function 1
 *	110 alt. function 2
 *	111 alt. function 3
 *	011 alt. function 4
 *	010 alt. function 5
 */
#define GPSET0_OFFSET	0x07		/* GPIO Pin Output Set 0 Offset */
/* Output Set Register
 * 0	No effect
 * 1	set GPIO Pin to 1
 */
#define GPCLR0_OFFSET	0x0a		/* GPIO Pin Output Clear 0 Offset */
/* Output Clear Register
 * 0	No effect
 * 1	set GPIO Pin to 0
 */
#define GPLEV0_OFFSET	0x0d	/* GPIO Pin Level 0 */
/* Output Set Register
 * 0	Pin Low
 * 1	Pin High
 */
#define GPEDS0_OFFSET	0x10 	/* GPIO Pin Event Detect Status 0 */
/* GPIO Pin Event Detect Status
 * Is set when:
 * 1) Detected edge matches the type programmed (rising/falling/both)
 * 2) Detected level matches the type programmed (high/low/both)
 * 0	Event NOT detected
 * 1	Event detected
 * Bit cleared by writing 1 to relevant bit (?)
 * Can be programmed to interrupt the processor when any are set.
 * GPIO has three dedicated interrupt lines,
 * each GPIO bank can generate independent interrupt
 * Third line generates a single interrupt whenever any bit is set.
 */
#define GPREN0_OFFSET	0x13	/* GPIO Pin Rising Edge Detect Enable 0 */
/* GPIO Pin Rising Edge Detect Enable Register
 * Upon detecting rising edge, corresponding bit in GPEDS0 will be set
 * Uses synchronous edge detection:
 * input signal is sampled using the system clock,
 * looks for a "011" pattern on the sampled signal (to suppress glitches)
 * 0	Disabled
 * 1	Enabled
 */
#define GPFEN0_OFFSET	0x16	/* GPIO Pin Falling Edge Detect Enable 0 */
/* GPIO Pin Falling Edge Detect Enable Register
 * Upon detecting falling edge, corresponding bit in GPEDS0 will be set
 * Uses synchronous edge detection:
 * input signal is sampled using the system clock, 
 * looks for a "100" pattern on the sampled signal (to suppress glitches)
 * 0	Disabled
 * 1	Enabled
 */
#define GPHEN0_OFFSET	0x19	/* GPIO Pin High Detect Enable 0 */
/* High Detect Status Register
 * When pin still high upon GPEDSn clear attempt, status will remain set.
 * 0	Disabled
 * 1	Enabled
 */
#define GPLEN0_OFFSET	0x1c	/* GPIO Pin Low Detect Enable 0 */
/* Low Detect Status Register
 * When pin still low upon GPEDSn clear attempt, status will remain set.
 * 0	Disabled
 * 1	Enabled
 */
#define GPAREN0_OFFSET	0x1f	/* GPIO Pin Async. Rising Edge Detect 0 */
/* Async. Rising Edge Detect Status Register
 * Incoming signal not sampled by system clock.
 * Can be used to detect signals with very short duration
 * Upon detecting rising edge, corresponding bit in GPEDS0 will be set
 * 0	Disabled
 * 1	Enabled
 */
#define GPAFEN0_OFFSET	0x22	/* GPIO Pin Async. Falling Edge Detect 0 */
/* Async. Falling Edge Detect Status Register
 * Incoming signal not sampled by system clock.
 * Can be used to detect signals with very short duration
 * Upon detecting falling edge, corresponding bit in GPEDS0 will be set
 * 0	Disabled
 * 1	Enabled
 */
#define GPPUD_OFFSET	0x25	/* GPIO Pin Pull Up/Down Enable */
/* GPIO Pin Pull Up/Down Enable Register
 * Controlls actuation of internal pull-up/down control line to ALL the GPIO pins.
 * Must be used in conjunction with the two GPPUDCLKn registers.
 * Cannot read once set, users should remember the state, as it will remain even when the power is off.
 * 00	disable
 * 01	enable pull-down
 * 10	enable pull-up (recommended)
 * 11 	reserved
 */
#define GPPUDCLK0_OFFSET	0x26	/* GPIO Pin Pull Up/Down Clock 0 */
/* GPIO Pin Pull Up/Down Clock Register
 * Controlls actuation of internal pull-up/down 
 * Following sequence of event required
 * 1) Write to GPPUD to set the required control signal(pull-up/down)
 * 2) Wait 150 cycles to provide required set-up time
 * 3) Write GPPUDCLKn to clock the control signal into the GPIO pads you wish to modify.
 * 4) Wait 150 cycles to provide required hold time
 * 5) Write GPPUD to remove control signal.
 * 6) Write GPPUDCLK to remove the clock.
 */

#define RESET_GPIO(idx)	gpio[(idx/10)] &= ~(7 << (idx%10)*3)
#define ACT_GPIO(idx)	gpio[(idx/10)] |= (1 << (idx%10)*3)
#define GPIO_SET(idx)	gpio[GPSET0_OFFSET] |= (1 << idx)
#define GPIO_CLR(idx)	gpio[GPCLR0_OFFSET] &= (1 << idx)

#define GPIO_EVENT_READ(idx)	(gpio[GPEDS0_OFFSET] >> idx) & 1
#define GPIO_EVENT_CLEAR(idx)	gpio[GPEDS0_OFFSET] |= (1 << idx)

#define GPIO_RISING_EDGE_EVENT_READ(idx) gpio[GPREN0_OFFSET] & (1 << idx)
#define GPIO_FALLING_EDGE_EVENT_READ(idx) gpio[GPFEN0_OFFSET] & (1 << idx)

#define GPIO_SET_RISING_EDGE_ENABLE(idx) gpio[GPREN0_OFFSET] |= (1 << idx)
#define GPIO_SET_RISING_EDGE_DISABLE(idx) gpio[GPREN0_OFFSET] &= ~(1 << idx)
#define GPIO_SET_FALLING_EDGE_ENABLE(idx) gpio[GPFEN0_OFFSET] |= (1 << idx)
#define GPIO_SET_FALLING_EDGE_DISABLE(idx) gpio[GPFEN0_OFFSET] &= ~(1 << idx)
#define GPIO_SET_HIGH_DETECT(idx) gpio[GPHEN0_OFFSET] |= (1 << idx)
#define GPIO_SET_LOW_DETECT(idx) gpio[GPLEN0_OFFSET] |= (1 << idx)

/* GPIO Register set */
volatile unsigned int* gpio;

#define PIN_IN		5
#define PIN_OUT		13

#define TRUE	1
#define	FALSE	0

int read_gpio_event(int PIN_IN)
{
	int ret = 0;
	if (GPIO_EVENT_READ(PIN_IN))
	{
		if (GPIO_RISINGEDGE_EVENT_READ(PIN_IN))
		{
			GPIO_EVENT_CLEAR(PIN_IN);
			GPIO_SET_RISING_EDGE_DISABLE(PIN_IN);
			GPIO_SET_FALLING_EDGE_ENABLE(PIN_IN);
		}
		else if (GPIO_FALLINGEDGE_EVENT_READ(PIN_IN))
		{
			GPIO_EVENT_CLEAR(PIN_IN);
			GPIO_SET_FALLING_EDGE_DISABLE(PIN_IN);
			GPIO_SET_RISING_EDGE_ENABLE(PIN_IN);
			ret = 1;
		}
	}
	return ret;
}


int _start ( void )
{
	/* Assign the address of the GPIO peripheral (Using ARM Physical Address) */
	gpio = (unsigned int*)GPIO_BASE;

	/* Reset GPIO */
	RESET_GPIO(PIN_IN);
	RESET_GPIO(PIN_OUT);
	ACT_GPIO(PIN_OUT);

	GPIO_SET_RISING_EDGE_ENABLE(PIN_IN);
	GPIO_SET_FALLING_EDGE_DISABLE(PIN_IN);

	int count = 0;
	
	while(TRUE)
	{
		if (read_gpio_event(PIN_IN))
		{
			count ++;
			if (count % 2)
				GPIO_SET(PIN_OUT);
			else
				GPIO_CLR(PIN_OUT);
		}
	}

	return (0);
}
