#include <OBD2_KLine.h>
#include <LiquidCrystal_I2C.h>

const int LED_ARRAY [10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
const int led_amount = 11;
unsigned long current_time = 0;
unsigned long previous_time = 0;
int flash_state;

void setup() {
	// setting led pins
	for (int i = 0; i < 10; i++) {
		pinMode(LED_ARRAY[i], OUTPUT);
	}

	//I2C LCD setup
	LiquidCrystal_I2C lcd_left (0x27,16,2);
	LiquidCrystal_I2C lcd_right (0x26,16,2);

	lcd_left.init();
	lcd_right.init();

	lcd_left.backlight();
	lcd_right.backlight();
}

void loop() {
	// put your main code here, to run repeatedly:

}

void led_flash (int LED_ARRAY [], int interval, unsigned long current_time = current_time, unsigned long *previous_time = &previous_time) {

	if (current_time >= *previous_time + interval) {
		*previous_time = current_time;

		if (flash_state = HIGH) {

			flash_state = LOW;
		} else {

			flash_state = HIGH;
		}

		for (int i = 0; i < 10; i++) {
			digitalWrite(LED_ARRAY[i], flash_state);
		}
	}
}

void led_rpm_meter (int LED_ARRAY [], int rpm, unsigned long current_time, unsigned long *previous_time) {

	int idle_rpm = 900;
	int flash_rpm = 4000;
	int flash_interval = 500; // in milliseconds
	
	if (rpm < flash_rpm) {
		for (int i = 0; i < led_amount; i++) {
			if (i <= (0 - led_amount) / (idle_rpm - flash_rpm) * (rpm - idle_rpm) { // equation is based on a linear graph in point slope form: y = m(x - x1) + y1

				digitalWrite (LED_ARRAY[i], HIGH);
			} else {
				digitalWrite ( LED_ARRAY, LOW );
			}
		}
	} else {
		led_flash (LED_ARRAY, flash_interval, current_time, previous_time);
	}
}
