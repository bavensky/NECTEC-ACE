#define rxPin 16
#define txPin 17

unsigned long previousMillis = 0;
const long interval = 1000;

int timeCount = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, rxPin, txPin, false);

  Serial.println();
  Serial.println("Starting...");
  Serial.println("Set position to 0");
  Serial1.print("10\n");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    timeCount++;
  }

  if (timeCount >= 1 && timeCount <= 5) {
    Serial.println("Going to 200");
    Serial1.print("200\n");
  } else if (timeCount >= 6 && timeCount <= 10) {
    Serial.println("Going to 400");
    Serial1.print("400\n");
  } else if (timeCount >= 11 && timeCount <= 15) {
    Serial.println("Going to 600");
    Serial1.print("600\n");
  } else if (timeCount >= 16 && timeCount <= 20) {
    Serial.println("Ging to 800");
    Serial1.print("800\n");
  } else if (timeCount >= 21 && timeCount <= 25) {
    Serial.println("Going to 1000");
    Serial1.print("1000\n");
  }
}
