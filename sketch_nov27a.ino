#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Voltage measurement constants
const float VREF = 5.0;  // Arduino ADC reference voltage
const int ADC_RESOLUTION = 1023; // 10-bit ADC resolution
const float AMPERE_Conversion; 
const float GAIN_Voltage;

void setup() {
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.backlight(); // Turn on the LCD backlight
  lcd.print("MultiMeter Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  int sensorValueA0 = analogRead(A0); // Read the analog pin A0 
  float measuredVoltage = (sensorValueA0 * VREF) / ADC_RESOLUTION; // Voltage Out of OP-AMP 
  float inputVoltage = measuredVoltage*GAIN_Voltage; // Calculate the input voltage
  // Reading Current :
  int sensorValueA1 = analogRead(A1);
  float measuredVoltageCurrent = (sensorValueA1 * VREF) / ADC_RESOLUTION;  
  float inputCurrent = measuredVoltageCurrent*AMPERE_Conversion; // Calculate the input voltage
  float resistance;
  // Display voltage
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(inputVoltage, 2); // Display with 2 decimal places
  lcd.print("V\n");
  lcd.print("I:")
  lcd.print(inputCurrent, 2)
  lcd.print("mA  R:")
  lcd.print(resistance, 2)

  delay(1000); // Update every second
}
