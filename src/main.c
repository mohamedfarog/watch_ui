
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <hal/nrf_gpio.h>
#include "watchface_ui.h"
#include <string.h>



#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);


#ifdef CONFIG_GPIO
static struct gpio_dt_spec button_gpio = GPIO_DT_SPEC_GET_OR(
		DT_ALIAS(sw0), gpios, {0});
static struct gpio_callback button_callback;

static void button_isr_callback(const struct device *port,
				struct gpio_callback *cb,
				uint32_t pins)
{
	ARG_UNUSED(port);
	ARG_UNUSED(cb);
	ARG_UNUSED(pins);


	
}
#endif


/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000
bool blstatus = false;


// #define LED0_NODE DT_NODELABEL(led0)
#define LED1_NODE DT_NODELABEL(led1)

#define BUTTON0_NODE DT_NODELABEL(button0)
#define BUTTON1_NODE DT_NODELABEL(button1)
#define BUTTON2_NODE DT_NODELABEL(button2)
#define BUTTON3_NODE DT_NODELABEL(button3)



//   static const struct gpio_dt_spec led0_spec = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
  static const struct gpio_dt_spec button0_spec = GPIO_DT_SPEC_GET(BUTTON0_NODE, gpios);
  static const struct gpio_dt_spec button1_spec = GPIO_DT_SPEC_GET(BUTTON1_NODE, gpios);
  static const struct gpio_dt_spec button2_spec = GPIO_DT_SPEC_GET(BUTTON2_NODE, gpios);
  static const struct gpio_dt_spec button3_spec = GPIO_DT_SPEC_GET(BUTTON3_NODE, gpios);

  static const struct gpio_dt_spec led1_spec = GPIO_DT_SPEC_GET(LED1_NODE, gpios);


  static struct gpio_callback button0_cb;
  static struct gpio_callback button1_cb;
  static struct gpio_callback button2_cb;
  static struct gpio_callback button3_cb;



void button0_pressed_callback(const struct device *gpiob, struct gpio_callback *cb, gpio_port_pins_t pins)
{

	if (!gpio_pin_set_dt(&led1_spec, 0))
	{
		gpio_pin_set_dt(&led1_spec, 0);
		blstatus = true;
		bluetooth_status(blstatus);
	

	}

}

void button1_pressed_callback(const struct device *gpiob, struct gpio_callback *cb, gpio_port_pins_t pins)
{
	if (!gpio_pin_set_dt(&led1_spec, 0))
	{
		gpio_pin_set_dt(&led1_spec, 0);
		//here  call the screen for this button
	}

	
}
void button2_pressed_callback(const struct device *gpiob, struct gpio_callback *cb, gpio_port_pins_t pins)
{
	if (!gpio_pin_set_dt(&led1_spec, 0))
	{
		gpio_pin_set_dt(&led1_spec, 0);
		//here  call the screen for this button
	}

}

void button3_pressed_callback(const struct device *gpiob, struct gpio_callback *cb, gpio_port_pins_t pins)
{
	if (!gpio_pin_set_dt(&led1_spec, 0))
	{
		gpio_pin_set_dt(&led1_spec, 0);
		//here  call the screen for this button
	}

}



int main(void)
{

	
	int err;
	const struct device *display_dev;

	

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Device not ready, aborting test");
		return;
	}

#ifdef CONFIG_GPIO
	if (device_is_ready(button_gpio.port)) {
		err = gpio_pin_configure_dt(&button_gpio, GPIO_INPUT);
		if (err) {
			LOG_ERR("failed to configure button gpio: %d", err);
			return;
		}

		gpio_init_callback(&button_callback, button_isr_callback,
				   BIT(button_gpio.pin));

		err = gpio_add_callback(button_gpio.port, &button_callback);
		if (err) {
			LOG_ERR("failed to add button callback: %d", err);
			return;
		}

		err = gpio_pin_interrupt_configure_dt(&button_gpio,
						      GPIO_INT_EDGE_TO_ACTIVE);
		if (err) {
			LOG_ERR("failed to enable button callback: %d", err);
			return;
		}
	}
#endif


display_blanking_off(display_dev);

	// gpio_pin_configure_dt(&led0_spec, GPIO_OUTPUT);
	gpio_pin_configure_dt(&led1_spec, GPIO_OUTPUT);
	gpio_pin_configure_dt(&button0_spec, GPIO_INPUT);
	gpio_pin_configure_dt(&button1_spec, GPIO_INPUT);
	gpio_pin_configure_dt(&button2_spec, GPIO_INPUT);
	gpio_pin_configure_dt(&button3_spec, GPIO_INPUT);


	gpio_pin_interrupt_configure_dt(&button0_spec, GPIO_INT_EDGE_TO_ACTIVE);
	gpio_pin_interrupt_configure_dt(&button1_spec, GPIO_INT_EDGE_TO_ACTIVE);
	gpio_pin_interrupt_configure_dt(&button2_spec, GPIO_INT_EDGE_TO_ACTIVE);
	gpio_pin_interrupt_configure_dt(&button3_spec, GPIO_INT_EDGE_TO_ACTIVE);


	gpio_init_callback(&button0_cb, button0_pressed_callback, BIT(button0_spec.pin));

	gpio_init_callback(&button1_cb, button1_pressed_callback, BIT(button1_spec.pin));
	gpio_init_callback(&button2_cb, button2_pressed_callback, BIT(button2_spec.pin));
	gpio_init_callback(&button3_cb, button3_pressed_callback, BIT(button3_spec.pin));


	gpio_add_callback(button0_spec.port, &button0_cb);
	gpio_add_callback(button1_spec.port, &button1_cb);
	gpio_add_callback(button2_spec.port, &button2_cb);
	gpio_add_callback(button3_spec.port, &button3_cb);

	while (1) {
    watchface_init(blstatus);
	if(!gpio_pin_set_dt(&led1_spec, 1)){
		k_msleep(30000);
		gpio_pin_set_dt(&led1_spec, 1);
	}
	}


}




