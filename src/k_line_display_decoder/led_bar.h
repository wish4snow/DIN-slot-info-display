void led_flash (int LED_ARRAY_PINS [], int interval) {
	static unsigned long current_time = 0;
	static unsigned long previous_time = 0;
	static int flash_state = LOW;

	current_time = millis();
	if (current_time >= previous_time + interval) {
		previous_time = current_time;
		flash_state = (flash_state == HIGH) ? LOW : HIGH;
		/*
		if (flash_state == HIGH) {

			flash_state = LOW;
		} else {

			flash_state = HIGH;
		}
		*/
		for (int i = 0; i < 11; i++) {
			digitalWrite(LED_ARRAY_PINS[i], flash_state);
		}
	}
}

void led_rpm_meter (int LED_ARRAY_PINS [], int rpm) {

	int idle_rpm = 900;
	int flash_rpm = 4000;
	int flash_interval = 500; // in milliseconds

	if (rpm < flash_rpm) {
		for (int i = 0; i < 11; i++) {

			digitalWrite(LED_ARRAY_PINS[i], (i <= (int) ((float) (0 - 11) / (idle_rpm - flash_rpm) * (rpm - idle_rpm))) ? HIGH : LOW);
			/*
			if (i <= (int) ((float) (0 - 11) / (idle_rpm - flash_rpm) * (rpm - idle_rpm))) { // equation is based on a linear graph in point slope form: y = m(x - x1) + y1

				digitalWrite (LED_ARRAY_PINS[i], HIGH);
			} else {
				digitalWrite ( LED_ARRAY_PINS[i], LOW );
			}
			*/
		}
	} else {
		led_flash (LED_ARRAY_PINS, flash_interval);
	}
}
