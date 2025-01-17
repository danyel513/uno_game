# UNO Game

This project is a C++ implementation of the popular card game **UNO**. It features a simulation of gameplay between bots or human players, adhering to the official rules of UNO. The program is structured using Object-Oriented Programming (OOP) principles.

---

## Features

- **Deck Initialization**:
  - The deck contains 108 cards, including all numbers (0-9) and special cards (Skip, Reverse, Draw Two, Wild, Wild Draw Four).
  - Cards are properly distributed by color (`red`, `green`, `blue`, `yellow`) and type.

- **Player Management**:
  - Support for human players and bots.
  - Each player starts with 7 cards.

- **Game Logic**:
  - Full implementation of UNO rules, including:
    - Playing matching cards by color or value.
    - Drawing cards if no valid play exists.
    - Special card effects (e.g., Skip, Reverse, Draw Two).
    - Wild and Wild Draw Four cards with color selection.
  - Turn-based gameplay with direction control.

---

## Technologies Used

- **Programming Language**: C++
  - **OOP Concepts**: Classes, encapsulation, inheritance.
  - **STL**: `std::vector`, `std::list`, and algorithms for card management.

---

## Code Structure

### Classes
1. **Card**:
   - Represents an individual card in the game.
   - Attributes:
     - `color` (e.g., `red`, `none` for wild cards).
     - `value` (e.g., `zero`, `drawTwo`).
   - Example:
     ```cpp
     Card redFive(red, five);
     redFive.display(); // Output: "five red"
     ```

2. **Deck**:
   - Manages the collection of all cards in the game.
   - Key Functions:
     - `shuffle()`: Randomizes the deck.
     - `draw()`: Draws a card from the deck.
   - Example:
     ```cpp
     Deck deck;
     deck.shuffle();
     Card drawnCard = deck.draw();
     drawnCard.display();
     ```

3. **Player**:
   - Represents a player (human or bot).
   - Key Functions:
     - `playCard()`: Selects and plays a card.
     - `drawCard()`: Draws a card from the deck.
   - Example:
     ```cpp
     Player player("Alice", deck);
     player.playCard(green, two, deck);
     ```

4. **Game**:
   - Manages the game flow, including rounds and rules enforcement.
   - Handles:
     - Turn management.
     - Rule application for special cards.
     - Winner detection.
   - Example:
     ```cpp
     Game game;
     game.StartGame();
     ```

---

## How to Run

### Prerequisites
- **Compiler**: A C++ compiler that supports at least C++11 (e.g., GCC, Clang, MSVC).
- **CMake**: For building the project.

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/uno-game.git
   cd uno-game
   ```

2. Build the project using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. Run the executable:
   ```bash
   ./UNO
   ```

---

## Gameplay Example

Upon starting the program, you will be prompted to select the game mode:
1. Player vs. Bot.
2. Bot vs. Bot.

### Sample Output
```text
~~~~~ GAME STARTED ~~~~~

Select the game mode:
1. Player vs Bot
2. Bot vs Bot
Your option: 2

ROUND 1 IN PROGRESS...

CARD ON THE TABLE: [ eight - blue ]
Player <Bot> has the following cards:
[ nine - blue ] [ three - red ] [ reverse - green ] [ eight - red ] [ six - blue ] [ five - red ] [ draw two - blue ]
Chosen card: [ eight - red ]
```

---

## Future Enhancements
- Add support for multiplayer over a network.
- Implement a graphical interface for better user experience.
- Add sound effects and animations.

---

## License
This project is licensed under the MIT License. See the LICENSE file for details.

---

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes.

---

Enjoy playing UNO! 😊
