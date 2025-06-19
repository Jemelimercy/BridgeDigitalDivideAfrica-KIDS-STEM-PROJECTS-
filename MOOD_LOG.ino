#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Button Pins
#define BTN_NEXT   A4
#define BTN_SELECT A5

// LED Pins (onboard)
#define LED_GREEN 11  // Happy
#define LED_ORANGE 12 // Okay
#define LED_RED 13    // Sad

// Mood Variables
String moodOptions[] = {"Happy :)", "Okay :|", "Sad :("};
int moodIndex = 0;
const int moodCount = 3;

void setup() {
  // Init display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  // Setup buttons
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(BTN_SELECT, INPUT_PULLUP);

  // Setup LEDs
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_ORANGE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  showMoodOption();
}

void loop() {
  static bool lastNext = HIGH;
  static bool lastSelect = HIGH;

  bool currentNext = digitalRead(BTN_NEXT);
  bool currentSelect = digitalRead(BTN_SELECT);

  // A4 - Cycle moods
  if (lastNext == HIGH && currentNext == LOW) {
    moodIndex = (moodIndex + 1) % moodCount;
    showMoodOption();
    delay(200); // debounce
  }

  // A5 - Select mood
  if (lastSelect == HIGH && currentSelect == LOW) {
    logMood(moodIndex);
    delay(1000);
    showMoodOption();
  }

  lastNext = currentNext;
  lastSelect = currentSelect;
}

void showMoodOption() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("How do you feel?");
  display.setTextSize(2);
  display.setCursor(0, 30);
  display.println(moodOptions[moodIndex]);
  display.setTextSize(1);
  display.display();
}

void logMood(int mood) {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println("Mood Logged:");
  display.setTextSize(2);
  display.setCursor(0, 30);
  display.println(moodOptions[mood]);
  display.display();

  // Clear all LEDs
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_ORANGE, LOW);
  digitalWrite(LED_RED, LOW);

  // Turn on matching LED
  switch (mood) {
    case 0: // Happy
      digitalWrite(LED_GREEN, HIGH);
      break;
    case 1: // Okay
      digitalWrite(LED_ORANGE, HIGH);
      break;
    case 2: // Sad
      digitalWrite(LED_RED, HIGH);
      break;
  }
}
