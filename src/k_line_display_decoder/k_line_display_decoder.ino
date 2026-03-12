#include <AltSoftSerial.h>
#include <OBD2_KLine.h>
#include <LiquidCrystal_I2C.h>

// LED bar global varibles
const int LED_ARRAY_PINS [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int led_amount = 11;
unsigned long current_time = 0;
unsigned long previous_time = 0;
int flash_state;

// k line global varibles 
AltSoftSerial alt_serial;
OBD2_KLine KLine(alt_serial, 10400, 0, 1);  // Uses Hardware Serial (Serial1) at 10400 baud, with RX on pin 0 and TX on pin 1.
bool supported_pids [200];
int user_defined_pids [5] = {0x0C, 0x0B, 0x0A, 0x0F, 0x11}; // defined by user, will make better way to interact with in future
void setup() {
	// setting led pins
	for (int i = 0; i < 10; i++) {
		pinMode(LED_ARRAY_PINS[i], OUTPUT);
	}

	//I2C LCD setup
	LiquidCrystal_I2C lcd_left (0x27,16,2);
	LiquidCrystal_I2C lcd_right (0x26,16,2);

	lcd_left.init();
	lcd_right.init();

	lcd_left.backlight();
	lcd_right.backlight();

	Serial.begin(115200);  // Start the default serial (for logging/debugging)
	Serial.println("OBD2 K-Line Get Supported PIDs Example");

	KLine.setDebug(Serial);          // Optional: outputs debug messages to the selected serial port
	KLine.setProtocol("Automatic");  // Optional: communication protocol (default: Automatic; supported: ISO9141, ISO14230_Slow, ISO14230_Fast, Automatic)
	KLine.setByteWriteInterval(5);   // Optional: delay (ms) between bytes when writing
	KLine.setInterByteTimeout(60);   // Optional: sets the maximum inter-byte timeout (ms) while receiving data
	KLine.setReadTimeout(1000);      // Optional: maximum time (ms) to wait for a response after sending a request

	Serial.println("OBD2 Starting.");

	if (KLine.initOBD2()) {
		int liveDataLength = KLine.readSupportedLiveData();  // Read supported live data PIDs. Mode: 01
		if (liveDataLength > 0) {
      Serial.println(liveDataLength);
			Serial.print("LiveData: ");
			for (int i = 0; i < liveDataLength; i++) {
				byte supported = KLine.getSupportedData(0x01, i);  // Get supported live data PID
				Serial.print(supported, HEX);                      // Print the PID in hexadecimal format
				Serial.print(" ");

        supported_pids[i] = (bool)supported;
        
			}
			Serial.println();
		} else {
			Serial.print("LiveData not supported!");
		}
	}
}
void loop() {
	// put your main code here, to run repeatedly:

}

void led_flash (int LED_ARRAY_PINS [], int interval, unsigned long current_time = current_time, unsigned long *previous_time = &previous_time) {

	if (current_time >= *previous_time + interval) {
		*previous_time = current_time;

		if (flash_state = HIGH) {

			flash_state = LOW;
		} else {

			flash_state = HIGH;
		}

		for (int i = 0; i < 10; i++) {
			digitalWrite(LED_ARRAY_PINS[i], flash_state);
		}
	}
}

void led_rpm_meter (int LED_ARRAY_PINS [], int rpm, unsigned long current_time, unsigned long *previous_time) {

	int idle_rpm = 900;
	int flash_rpm = 4000;
	int flash_interval = 500; // in milliseconds

	if (rpm < flash_rpm) {
		for (int i = 0; i < led_amount; i++) {
			if (i <= (0 - led_amount) / (idle_rpm - flash_rpm) * (rpm - idle_rpm)) { // equation is based on a linear graph in point slope form: y = m(x - x1) + y1

					digitalWrite (LED_ARRAY_PINS[i], HIGH);
					} else {
					digitalWrite ( LED_ARRAY_PINS[i], LOW );
					}
					}
					} else {
					led_flash (LED_ARRAY_PINS, flash_interval, current_time, previous_time);
					}
					}
