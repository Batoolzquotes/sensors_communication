//Include the necessary library headers in your Arduino code:
#include <Wire.h>                        // Library for I2C communication
#include <Adafruit_MLX90614.h>           // Library for MLX90614 sensor
#include <Adafruit_Sensor.h>             // Library for MPX5010DP sensor
#include <Adafruit_MAX3010x.h>           // Library for MAX30102 sensor
#include <Adafruit_GFX.h>                // Base library for TFT display
#include <Adafruit_LiquidCrystal.h>      // Library for I2C TFT display

//Initialize the sensor and TFT display objects in your code:
//Include the necessary library headers in your Arduino code:
#include <Wire.h>                        // Library for I2C communication
#include <Adafruit_MLX90614.h>           // Library for MLX90614 sensor
#include <Adafruit_Sensor.h>             // Library for MPX5010DP sensor
#include <Adafruit_MAX3010x.h>           // Library for MAX30102 sensor
#include <Adafruit_GFX.h>                // Base library for TFT display
#include <Adafruit_LiquidCrystal.h>      // Library for I2C TFT display

//Initialize the sensor and TFT display objects in your code:
Adafruit_MLX90614 mlx = Adafruit_MLX90614();                        // Create an instance of MLX90614
Adafruit_MPX5010DP mpx = Adafruit_MPX5010DP(0);                     // Create an instance of MPX5010DP
Adafruit_MAX30102 max30102;                                         // Create an instance of MAX30102
Adafruit_LiquidCrystal lcd(0x27, 20, 4);                             // Create an instance of I2C TFT display
Adafruit_Sensor *pxSensor = max30102.getTemperatureSensor();         // Create a pointer for MAX30102 temperature sensor
Adafruit_Sensor *oxSensor = max30102.getIRSensor();                  // Create a pointer for MAX30102 IR sensor

//Adjust the I2C address (0x27) if necessary to match your TFT display's address.

//Initialize the I2C communication and sensors, as well as the TFT display, in the setup() function:
void setup() {
  mlx.begin();                                      // Initialize the MLX90614 sensor
  mpx.begin();                                      // Initialize the MPX5010DP sensor
  max30102.begin(Wire, I2C_SPEED_FAST);              // Initialize the MAX30102 sensor
  max30102.setup();                                 // Setup the MAX30102 sensor
  lcd.begin(20, 4);                                 // Initialize the TFT display
  lcd.backlight();                                  // Turn on the backlight (if applicable)
}

//Read the sensor data and display it on the TFT display in the loop() function:
void loop() {
  float tempC = mlx.readObjectTempC();              // Read temperature in Celsius from the MLX90614 sensor
  float pressure = mpx.readPressure();               // Read pressure from the MPX5010DP sensor
  sensors_event_t pxEvent, oxEvent;                  // Create event structures for MAX30102 sensors
  pxSensor->getEvent(&pxEvent);                       // Read temperature event from MAX30102
  oxSensor->getEvent(&oxEvent);                       // Read IR event from MAX30102

  lcd.clear();                                       // Clear the display
  lcd.setCursor(0, 0);                               // Set cursor to the first row, first column
  lcd.print("Temp: ");                               // Print label for temperature
  lcd.print(tempC, 1);                               // Print the temperature value with one decimal place
  lcd.print("C");

  lcd.setCursor(0, 1);                               // Set cursor to the second row, first column
  lcd.print("Pressure: ");                           // Print label for pressure
  lcd.print(pressure, 2);                            // Print the pressure value with two decimal places
  lcd.print("Pa");

  lcd.setCursor(0, 2);                               // Set cursor to the third row, first column
  lcd.print("PX Temp: ");                            // Print label for MAX30102 temperature
  lcd.print(pxEvent.temperature, 1);                 // Print the MAX30102 temperature value with one decimal place
  lcd.print("C");

  lcd.setCursor(0, 3);                               // Set cursor to the fourth row, first column
  lcd.print("OX: ");                                  // Print label for MAX30102 IR value
  lcd.print(oxEvent.relative, 2);                     // Print the MAX30102 IR value with two decimal places

  delay(1000);                                       // Delay for one second before updating the display
}