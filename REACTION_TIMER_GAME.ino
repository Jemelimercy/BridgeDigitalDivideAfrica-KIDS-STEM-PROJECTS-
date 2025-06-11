const int ledPin = 13;     // Onboard LED (or external on D13)
const int buttonPin = A4;  // Onboard button on A4

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Button connected to GND
  Serial.begin(9600);
  Serial.println("Reaction Timer Game Ready");
  delay(1000);
}

void loop() {
  Serial.println("Get ready...");
  delay(random(2000, 5000));  // Wait 2–5 seconds

  Serial.println("GO! LED should turn ON now");
  digitalWrite(ledPin, HIGH);  // Turn LED ON
  unsigned long startTime = millis();

  // Wait until the button is PRESSED (goes LOW)
  while (digitalRead(buttonPin) == LOW) {
    // Button is already being held down before LED turns on
    // Wait until it's released first
    delay(50);
  }

  // Now wait for user to press the button
  while (digitalRead(buttonPin) == HIGH) {
    // do nothing, wait for press
  }

  unsigned long reactionTime = millis() - startTime;
  digitalWrite(ledPin, LOW);  // Turn LED OFF

  Serial.print("Your reaction time: ");
  Serial.print(reactionTime);
  Serial.println(" ms");

  delay(3000);
}
