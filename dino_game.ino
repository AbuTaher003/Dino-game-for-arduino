#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the I2C address for the LCD

boolean dinoOnGround = true;  
int buttonPin = 8;
int buzzerPin = 9;

int buttonState = 0; 
int highScore = 0; 
boolean playState = false; // Game starts when this is true
int dist = 0;   
int distTwo = 0;
int score = 0;
unsigned long jumpStartTime = 0; // Timer for jump duration
boolean isJumping = false; // Flag to check if dino is jumping

// Bitmap array for the dino character
byte dino[8] = { 
  B00000,
  B00111,
  B00101,
  B10111,
  B11100,
  B11111,
  B01101,
  B01100,
};

// Character for the tree
byte tree[8] = {
  B00011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11111,
  B01110,
  B01110
};

void setup() {
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  lcd.createChar(7, dino); // Create dino character
  lcd.createChar(6, tree); // Create tree character
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  lcd.clear();

  // At the start, check if playState is true or false
  if (!playState) {  
    lcd.setCursor(0, 0);                
    lcd.print("Press the button"); 
    lcd.setCursor(0, 1);
    lcd.print("to start: ");
    
    // When it is false, print the starting instruction
    if (digitalRead(buttonPin) == HIGH) { // Read the button
      playState = true; // When button pushed, make playState true
    }
  }

  // When playState is true, call the startGame function
  if (playState) {
    startGame();
  }

  delay(100); 
} // The loop function ends here

// When playState is true, startGame function is called
void startGame() {  
  lcd.clear();

  dist = random(4, 9);  
  distTwo = random(4, 9); // Generate two random distances for the gap between the trees

  // This for loop is to make the trees move
  for (int i = 16; i >= -(dist + distTwo); i--) { 
    lcd.setCursor(13, 0);
    lcd.print(score); // Print the score

    int state = digitalRead(buttonPin); // Read the push button
    if (state == HIGH) { 
      buttonState = 1;
      tone(buzzerPin, 700, 100);

      // If the dino is not currently jumping, start the jump
      if (!isJumping) {
        isJumping = true; // Set the jumping flag
        jumpStartTime = millis(); // Start the timer
      }
    } else {
      buttonState = 0;
    }

    // Manage Dino jumping
    if (isJumping) {
      // Check if 1 second has passed
      if (millis() - jumpStartTime < 1000) {
        dinoOnGround = false; // Dino is jumping
        lcd.setCursor(1, 0); // Print the dino on the upper row
        lcd.write(7);
        lcd.setCursor(1, 1);
        lcd.print(" ");
      } else {
        // After 1 second, stop jumping
        isJumping = false; // Reset jumping flag
        dinoOnGround = true; // Set dino back to the ground
        lcd.setCursor(1, 1); // Print the dino on the lower row
        lcd.write(7);
        lcd.setCursor(1, 0);
        lcd.print(" ");
      }
    } else {
      // Normal position when not jumping
      lcd.setCursor(1, 1);
      lcd.write(7); // Print dino on the lower row
      lcd.setCursor(1, 0);
      lcd.print(" ");
    }

    // This prints the trees so that it moves with the for loop
    lcd.setCursor(i, 1); 
    lcd.write(6);
    lcd.setCursor(i + 1, 1);
    lcd.print(" ");

    lcd.setCursor(i + dist, 1);
    lcd.write(6);
    lcd.setCursor(i + dist + 1, 1);
    lcd.print(" ");

    lcd.setCursor(i + dist + distTwo, 1);
    lcd.write(6);
    lcd.setCursor(i + dist + distTwo + 1, 1);
    lcd.print(" ");

    // When the trees reach the starting point
    if ((i + dist + distTwo) == -1) {
      i = 12; // They are taken to the end and set up randomly once more
    }

    // Check if the position of the trees and that of the dino coincides
    if (i == 1 && (dinoOnGround == true)) {
      gameOver();
      break;
    }
    else if (i + dist == 1 && (dinoOnGround == true)) {
      gameOver();
      break;
    }
    else if (i + dist + distTwo == 1 && (dinoOnGround == true)) {
      gameOver();
      break;
    }

    score++; // Increase the score variable for every run of the loop
    delay(500);
  }
}

void gameOver() {
  lcd.clear();
  lcd.print("Game Over!!!");
  if (score > highScore) {
    highScore = score;
  }
  
  lcd.setCursor(0, 1);
  lcd.print("HS: ");
  lcd.print(highScore);
  playState = false; // Set the playState as false so it goes to the start screen
  delay(5000); // Wait before restarting
  score = 0; // Reset score
}
