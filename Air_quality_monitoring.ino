#include <Wire.h>
 #include <U8g2lib.h>
 #include <math.h>
 // Create an instance of the U8G2 library for I2C OLED 128x64
 U8G2_SSD1306_128X64_NONAME_F_HW_I2Cu8g2(U8G2_R0, /* reset=*/
 U8X8_PIN_NONE);
 // Define the analog pin for the MQ-132 sensor
 #define MQ132_PIN 34 //Analog pin for MQ-132 sensor
 // Calibration constants for the MQ-132 sensor
 const float RLOAD = 10.0; // Load resistance in kilo-ohms
 const float RZERO = 76.63; // Base resistance in clean air (adjust based on calibration)
 const float PARA_O3 = 1.0; // Constant for Ozone (O3) calculation (needs adjustment)
 const float PARB_O3 =-0.5; // Constant for Ozone (O3) calculation (needs adjustment)
 const float PARA_NOx = 1.5; // Constant for NOx calculation (needs adjustment)
 const float PARB_NOx =-0.7;// Constant for NOx calculation (needs adjustment)
 const float PARA_Cl2 = 1.2; // Constant for Chlorine (Cl2) calculation (needs
 adjustment)
 const float PARB_Cl2 =-0.6;// Constant for Chlorine (Cl2) calculation (needs
 adjustment)
 void setup() {
 // Initialize serial communication
 Serial.begin(115200);
 // Initialize the OLED display
 u8g2.begin();
 // Display a startup message on OLED
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_ncenB08_tr); // Set font
u8g2.drawStr(0, 10, "Air Quality Monitor");
 u8g2.drawStr(0, 30, "Initializing...");
 u8g2.sendBuffer(); // Send the buffer to the display
 delay(2000); // Wait for 2 seconds
 }
 float calculate_ppm(float ratio, float para, float parb)
 {return para * pow(ratio, parb);
 }
 void loop() {
 // Step 1: Read the analog value from the MQ-132 sensor
 int analogValue = analogRead(MQ132_PIN); // Read the analog value (0 to 4095)
 // Step 2: Convert the analog value to voltage
 float voltage = analogValue * (3.3 / 4095.0); // Convert to voltage (0V to 3.3V)
 // Step 3: Calculate sensor resistance (RS) in kilo-ohms
 float RS = (3.3- voltage) / voltage * RLOAD; // Sensor resistance calculation
 // Step 4: Calculate the ratio of RS to RZERO
 float ratio = RS / RZERO;
 // Step 5: Calculate the concentrations for multiple gases (O₃, NOx, Cl₂) in ppm
 float ozone_ppm = calculate_ppm(ratio, PARA_O3, PARB_O3);
 float nox_ppm= calculate_ppm(ratio, PARA_NOx,PARB_NOx);
 float cl2_ppm = calculate_ppm(ratio, PARA_Cl2, PARB_Cl2);
 // Step 6: Display data on the OLED screen
 u8g2.clearBuffer(); // Clear the screen for new data
 u8g2.setFont(u8g2_font_ncenB08_tr); // Set font size to normal
 // Display header
 u8g2.setCursor(0, 10);
 u8g2.print("Air Quality Monitor");
 // Display sensor data for multiple gases
 u8g2.setCursor(0, 25);
 u8g2.print("Ozone (O3): ");
 u8g2.print(ozone_ppm, 2);
 u8g2.print(" ppm");
u8g2.setCursor(0, 40);
 u8g2.print("NOx: ");
 u8g2.print(nox_ppm, 2);
 u8g2.print(" ppm");
 u8g2.setCursor(0, 55);
 u8g2.print("Cl2: ");
 u8g2.print(cl2_ppm, 2);
 u8g2.print(" ppm");
 // Send updated data to the OLED screen
 u8g2.sendBuffer();
 // Step 7: Display the results on the Serial Monitor as well
 Serial.print("Analog Value: ");
 Serial.print(analogValue); // Display the raw analog value
 Serial.print("\tVoltage: ");
 Serial.print(voltage, 3); // Display the calculated voltage
 Serial.print(" V\t");
 Serial.print("Resistance: ");
 Serial.print(RS, 3); // Display sensor resistance
 Serial.print(" kOhms\t");
 Serial.print("Ozone (O3): ");
 Serial.print(ozone_ppm, 2); // Display the ozone concentration in ppm
 Serial.print(" ppm\tNOx: ");
 Serial.print(nox_ppm, 2); // Display NOx concentration in ppm
 Serial.print(" ppm\tCl2: ");
 Serial.print(cl2_ppm, 2); // Display chlorine concentration in ppm
 Serial.println(" ppm");
 delay(2000); // Wait for 2 seconds before the next reading
 }
II)void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
