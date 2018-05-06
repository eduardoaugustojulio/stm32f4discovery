#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

uint16_t exti_line_state;

/* Set STM32 to 168 MHz. */
static void clock_setup(void)
{
	rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
}

static void gpio_setup(void)
{
	/* Enable GPIOD clock. */
	rcc_periph_clock_enable(RCC_GPIOG);

	/* Set GPIO13 (in GPIO port D) to 'output push-pull'. */
	gpio_mode_setup(GPIOG, GPIO_MODE_OUTPUT,
			GPIO_PUPD_NONE, GPIO13 | GPIO14);
}

static void button_setup(void)
{
	/* Enable GPIOA clock. */
	rcc_periph_clock_enable(RCC_GPIOA);

	/* Set GPIO0 (in GPIO port A) to 'input open-drain'. */
	gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);
}

int main(void)
{
	int i;

	clock_setup();
	button_setup();
	gpio_setup();

	/* Blink the LED (PD13) on the board. */
	while (1) {
		gpio_toggle(GPIOG, GPIO13);

		/* Upon button press, blink more slowly. */
		exti_line_state = GPIOA_IDR;
		if ((exti_line_state & (1 << 0)) != 0) {
			for (i = 0; i < 3000000; i++) {	/* Wait a bit. */
				__asm__("nop");
			}
		}

		for (i = 0; i < 3000000; i++) {		/* Wait a bit. */
			__asm__("nop");
		}
	}

	return 0;
}
