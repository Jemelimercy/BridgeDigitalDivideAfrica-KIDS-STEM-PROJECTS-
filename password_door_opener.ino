#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Set your password
String password = "C987";
String input = "";

// --- Servo Setup ---
Servo doorServo;
#define SERVO_PIN 10
#define OPEN_POS 90     // adjust if needed
#define CLOSED_POS 0

// --- Keypad Setup ---
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};  // Your actual row pins
byte colPins[COLS] = {5, 4, 3, 2};  // Your actual column pins

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void showMessage(String line1, String line2 = "") {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(line1);
  if (line2 != "") {
    display.setCursor(0, 30);
    display.println(line2);
  }
  display.display();
}

void setup() {
  Serial.begin(9600);

  // Start OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED not found"));
    while (true);
  }

  // Start Servo
  doorServo.attach(SERVO_PIN);
  doorServo.write(CLOSED_POS);  // Door starts locked

  showMessage("Enter Password:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Key: ");
    Serial.println(key);

    if (key == '#') {
      if (input == password) {
        showMessage("Access Granted", "Welcome Jemeli!");
        Serial.println("Access Granted");

        doorServo.write(OPEN_POS);   // Unlock door
        delay(3000);                 // Keep open 3 sec
        doorServo.write(CLOSED_POS); // Lock again

        delay(1000);
      } else {
        showMessage("Access Denied", "Try Again");
        Serial.println("Access Denied");
        delay(2000);
      }

      input = "";
      showMessage("Enter Password:");

    } else if (key == '*') {
      input = "";
      showMessage("Enter Password:");

    } else {
      if (input.length() < 4) {
        input += key;
        showMessage("Enter Password:", input);
      }
    }
  }
}
