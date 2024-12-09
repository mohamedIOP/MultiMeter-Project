#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Voltage measurement constants
const float VREF = 5.0;  // Arduino ADC reference voltage
const int ADC_RESOLUTION = 1023; // 10-bit ADC resolution
const float AMPERE_Conversion = 1.0; // Example value, update accordingly
const float GAIN_Voltage = 2;      // Example value, update accordingly
const float VOLTAGE_DIVIDER_MULTIPLE[8] = {6, 1, 1, 1, 1, 1, 1, 1}; // Example values

// Function to detect "on" signal
int onSignal(float signal) {
  return (signal > 2.5) ? 1 : 0; // Return 1 if signal > 2.5V, else 0
}

void setup() {
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.backlight();  // Turn on the LCD backlight
  lcd.print("MultiMeter Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read analog pins
  int sensorValueA0 = analogRead(A0); // Read the analog pin A0
  float A1Selection = analogRead(A1) * VREF / ADC_RESOLUTION;
  float A2Selection = analogRead(A2) * VREF / ADC_RESOLUTION;
  float A3Selection = analogRead(A3) * VREF / ADC_RESOLUTION;

  // Convert selected lines into binary representation
  int selectedLine[3] = {onSignal(A3Selection), onSignal(A2Selection), onSignal(A1Selection)};
  int size = sizeof(selectedLine) / sizeof(selectedLine[0]);

  // Convert binary array to integer value
  int value = 0;
  for (int i = 0; i < size; i++) {
    value = (value << 1) | selectedLine[i]; // Shift left and add the bit
  }

  // Display selected line and value
  lcd.setCursor(0, 0);
  lcd.print("SL: ");
  lcd.print(selectedLine[0]);
  lcd.print(selectedLine[1]);
  lcd.print(selectedLine[2]);
  lcd.print(" Val:");
  lcd.print(value);
  // Calculate voltage
  float measuredVoltage = (sensorValueA0 * VREF) / ADC_RESOLUTION; // Voltage out of OP-AMP
  float inputVoltage = measuredVoltage;

  switch (value) {
    case 0:
      inputVoltage = measuredVoltage / GAIN_Voltage * VOLTAGE_DIVIDER_MULTIPLE[0];
      break;
    case 1:
      inputVoltage = measuredVoltage / GAIN_Voltage * VOLTAGE_DIVIDER_MULTIPLE[1];
      break;
    case 2:
      inputVoltage = measuredVoltage / GAIN_Voltage * VOLTAGE_DIVIDER_MULTIPLE[2];
      break;
    case 3:
      inputVoltage = measuredVoltage / GAIN_Voltage * VOLTAGE_DIVIDER_MULTIPLE[3];
      break;
    case 4:
      inputVoltage = measuredVoltage / GAIN_Voltage * VOLTAGE_DIVIDER_MULTIPLE[4];
      break;
    case 5:
      inputVoltage = measuredVoltage / GAIN_Voltage * VOLTAGE_DIVIDER_MULTIPLE[5];
      break;
    case 6:
      inputVoltage = measuredVoltage / GAIN_Voltage * VOLTAGE_DIVIDER_MULTIPLE[6];
      break;
    case 7:
      inputVoltage = measuredVoltage / GAIN_Voltage * VOLTAGE_DIVIDER_MULTIPLE[7];
      break;
    default:
      inputVoltage = measuredVoltage;
      break;
  }

  // Display calculated voltage
  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.print(inputVoltage, 2); // Display with 2 decimal places
  lcd.print("V");

  delay(1000); // Update every second
}
