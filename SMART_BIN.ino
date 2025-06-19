#include <Servo.h>

const int trigPin = 2;
const int echoPin = 3;
const int servoPin = 9;

Servo binServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  binServo.attach(servoPin);
  binServo.write(0); // Lid closed
  Serial.begin(9600);
}

void loop() {
  long duration;
  int distance;

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance < 20) { // Hand is near
    binServo.write(90); // Open lid
    delay(3000);        // Keep open for 3 seconds
    binServo.write(0);  // Close lid
  }

  delay(200); // Small delay to prevent rapid triggering
}
