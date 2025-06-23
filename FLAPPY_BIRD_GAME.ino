#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON_PIN 2
#define BUZZER_PIN 8

// Game variables
int birdY = 32;
int velocity = 0;
int gravity = 1;
int flapStrength = -4;

int pipeX = 128;
int gapY = 30;
int gapSize = 20;

int score = 0;
bool gameOver = false;
bool gameStarted = false;

unsigned long lastButtonPress = 0;
const int debounceDelay = 200;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button connected to GND
  pinMode(BUZZER_PIN, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
  randomSeed(analogRead(0)); // For pipe randomness

  showStartScreen();
}

void loop() {
  if (!gameStarted) {
    if (isButtonPressed()) {
      tone(BUZZER_PIN, 1500, 100);
      delay(100);
      gameStarted = true;
      resetGame();
    }
    return;
  }

  if (gameOver) {
    display.clearDisplay();
    display.setCursor(10, 30);
    display.print("Game Over! Score: ");
    display.print(score);
    display.display();
    tone(BUZZER_PIN, 300, 500);  // Game over sound
    delay(2000);
    gameStarted = false;
    showStartScreen();
    return;
  }

  if (isButtonPressed()) {
    velocity = flapStrength;
    tone(BUZZER_PIN, 1000, 100); // Flap sound
  }

  // Bird physics
  velocity += gravity;
  birdY += velocity;

  // Pipe movement
  pipeX--;
  if (pipeX < -10) {
    pipeX = 128;
    gapY = random(10, 40);
    score++;
    tone(BUZZER_PIN, 2000, 100); // Score sound
  }

  // Collision detection
  if (birdY < 0 || birdY > SCREEN_HEIGHT ||
     (pipeX < 10 && (birdY < gapY || birdY > gapY + gapSize))) {
    gameOver = true;
  }

  // Draw game frame
  display.clearDisplay();

  // Bird
  display.fillRect(5, birdY, 5, 5, SSD1306_WHITE);

  // Pipes
  display.fillRect(pipeX, 0, 10, gapY, SSD1306_WHITE);
  display.fillRect(pipeX, gapY + gapSize, 10, SCREEN_HEIGHT - gapY - gapSize, SSD1306_WHITE);

  // Score display
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(score);

  display.display();
  delay(30);
}

void resetGame() {
  birdY = 32;
  velocity = 0;
  pipeX = 128;
  gapY = 30;
  score = 0;
  gameOver = false;
}

void showStartScreen() {
  display.clearDisplay();
  display.setCursor(20, 20);
  display.setTextSize(1);
  display.print("FLAPPY BIRD");
  display.setCursor(10, 40);
  display.print("Press button to start");
  display.display();
}

// Debounced button press check
bool isButtonPressed() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (millis() - lastButtonPress > debounceDelay) {
      lastButtonPress = millis();
      return true;
    }
  }
  return false;
}
