// Pin assignments
int redLED = 13;
int yellowLED = 12;
int greenLED = 11;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {
  // Green light ON
  digitalWrite(greenLED, HIGH);
  delay(5000);  // Green for 5 seconds
  digitalWrite(greenLED, LOW);

  // Yellow light ON
  digitalWrite(yellowLED, HIGH);
  delay(2000);  // Yellow for 2 seconds
  digitalWrite(yellowLED, LOW);

  // Red light ON
  digitalWrite(redLED, HIGH);
  delay(5000);  // Red for 5 seconds
  digitalWrite(redLED, LOW);
}
