/*Touch Sensor Pin Layout
   T0 = GPIO4
   T1 = GPIO0
   T2 = GPIO2
   T3 = GPIO15
   T4 = GPIO13
   T5 = GPIO12
   T6 = GPIO14
   T7 = GPIO27
   T8 = GPIO33
   T9 = GPIO32 */

#include <HardwareSerial.h>

#define rxPin (16)
#define txPin (17)

HardwareSerial Serial1(1);

unsigned long previousMillis = 0;
const long interval = 100;
boolean statusCar = false;
unsigned int timeCount = 0;

int buff(int pin)                                       //Function to handle the touch raw sensor data
{

  int out = (50 - touchRead(pin));                         //  Scale by n, value very sensitive currently
  // change to adjust sensitivity as required
  if (out > 0 )
  {
    return (out + 2);
  }
  else
  {
    return 0;                                        //Else, return 0
  }

}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, rxPin, txPin, false);
  delay(10);


  Serial.println();
  Serial.println("Starting...");
  Serial.println("Set position to 0");
  Serial1.print("0\n");
  delay(5000);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    timeCount++;
    Serial.print(millis() / 1000);
    Serial.print("  ");
    Serial.println(timeCount);
  }

  // Touch pin 33
  if (buff(T8) > 30) {
    statusCar = true;
    timeCount = 0;
  }

  delay(200);
  

  if (statusCar == true) {

    Serial1.print(String(map(timeCount, 0, 25, 0, 900)) + "\n");
  }

  if (timeCount >= 25) {
    statusCar = false;
  }

  //  if (Serial.available())              //if user typed something through the USB...
  //  {
  //    Serial1.write(Serial.read());      //Push it through port 1 to Central ESP32
  //  }
}
