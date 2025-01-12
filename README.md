# Dino LCD Game

This project is a simple LCD-based Dino Jump game implemented using an Arduino. The game involves a dino character that jumps to avoid obstacles (trees). The goal is to achieve the highest score possible by avoiding collisions.

## Features

- **LCD Display**: Uses an I2C 16x2 LCD screen to display the game.
- **Custom Characters**: Includes custom bitmap characters for the dino and trees.
- **Button Input**: A button is used to make the dino jump.
- **Scoring System**: Tracks the player's score and displays the high score.
- **Buzzer Feedback**: Emits a sound when the jump button is pressed.
- **Game Over Screen**: Displays a message and the high score when the player loses.

## Hardware Requirements

- Arduino board (e.g., Uno, Nano)
- I2C 16x2 LCD
- Push button
- Buzzer
- Resistors (for the button circuit, if needed)
- Connecting wires

## Wiring Diagram

1. **LCD Connections**:
   - SDA: Connect to Arduino A4 (for Uno/Nano) or corresponding SDA pin
   - SCL: Connect to Arduino A5 (for Uno/Nano) or corresponding SCL pin
   - VCC: Connect to 5V
   - GND: Connect to GND

2. **Button**:
   - One side of the button to Arduino pin `8`
   - Other side to GND with a pull-up resistor setup

3. **Buzzer**:
   - Positive pin of the buzzer to Arduino pin `9`
   - Negative pin to GND

## How to Use

1. Connect the components as per the wiring diagram.
2. Upload the code to the Arduino board.
3. Press the button to start the game.
4. Avoid the moving trees by jumping (pressing the button).
5. The game ends if the dino collides with a tree.
6. The high score is displayed after a game-over.

## Code Explanation

1. **Global Variables**:
   - `dinoOnGround`: Tracks whether the dino is on the ground.
   - `buttonPin` and `buzzerPin`: Define the pins for the button and buzzer.
   - `highScore` and `score`: Track the highest score and the current score.
   - `playState`: Indicates if the game is running.

2. **Custom Characters**:
   - The `dino` and `tree` arrays define custom bitmap characters for the LCD.

3. **Main Functions**:
   - `setup()`: Initializes the LCD, custom characters, and pins.
   - `loop()`: Manages the game start screen and starts the game when the button is pressed.
   - `startGame()`: Contains the game logic, including tree movement and jump handling.
   - `gameOver()`: Handles game-over conditions, updates the high score, and resets the game.

## How It Works

- The game begins with an instruction to press the button.
- Once started, the dino is displayed on the LCD and trees move from right to left.
- Pressing the button makes the dino jump for a brief duration.
- The game ends if a tree and the dino collide while the dino is on the ground.

## Future Improvements

- Add more obstacles or varying speeds.
- Implement multiple difficulty levels.
- Introduce additional controls or features, such as ducking or power-ups.
- Use a larger LCD for a more immersive experience.

## License

This project is open-source and can be modified or distributed freely. Attribution to the original author is appreciated.

---


