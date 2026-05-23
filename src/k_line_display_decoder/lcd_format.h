#include <LiquidCrystal_I2C.h>

void write (LiquidCrystal_I2C screen_object, int row, String left_text, String right_text, int colum_length = 16) {
	screen_object.setCursor(0, row);
	screen_object.print(left_text + ":");

	screen_object.setCursor(colum_length - right_text.length(), row);
	screen_object.print(right_text);
}

String format_value (int value, String unit_abbreviation) {
	return ((String) value + unit_abbreviation);
}
