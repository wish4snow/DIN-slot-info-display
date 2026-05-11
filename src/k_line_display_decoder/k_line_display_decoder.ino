#include <AltSoftSerial.h>
#include <OBD2_KLine.h>
#include <LiquidCrystal_I2C.h>
#include "led_bar.h"

// LED bar global varibles
const int LED_ARRAY_PINS [] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
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
	led_rpm_meter (LED_ARRAY_PINS, 2000, flash_state, current_time, &previous_time);
	// put your main code here, to run repeatedly:

}

