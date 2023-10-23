# Snake Game

This is a Snake game implementation with a C++ backend and a React frontend (using Electron for the application). The game logic is implemented in C++ and the game state is represented as a JSON object. The backend uses Boost.Asio and Boost.Beast libraries for handling HTTP requests and JSON parsing.

## Installation

To run the game, you need to install the following dependencies:

- [Boost](https://www.boost.org/): Boost libraries are required for the backend implementation.
- [nlohmann/json](https://github.com/nlohmann/json): A JSON library used for creating and parsing JSON objects.

After installing the dependencies, you can compile the C++ code and start the game.

## Building the Project

To build the project, execute the following steps:

1. Clone the repository:

   ```
   git clone https://github.com/your-username/snake-game.git
   ```

2. Change to the project directory:

   ```
   cd snake-game
   ```

3. Build the project using `make`:

   ```
   make
   ```

## Running the Game

To run the game, follow the steps below:

1. Start the backend server:

   ```
   ./GigaSoft
  
   ```

2. Start the frontend:

   ```
   npm start
   ```

3. The game should open in a new Electron window.

## Gameplay

The Snake game is played using the W A S D keys to navigate the snake. The objective of the game is to eat fruits and grow the snake without hitting the walls or its own body. The game has three difficulty levels: Easy, Medium, and Hard. The levels determine factors such as snake speed and the number of fruits required to grow.

## Code Explanation

### `createJson`

This function creates a JSON representation of the game state based on the provided parameters. It constructs a JSON object using the `nlohmann/json` library.

### `GameData` Structure

This structure represents the game state, including the snake's body, head, fruit position, player's score, length of the snake, the current game level, and a flag indicating if the game is over. The `load` function parses the JSON data and updates the game state accordingly.

### `GameLogic` Class

This class implements the main logic of the game. It contains private helper functions for checking collision, updating the game state based on the difficulty level, and creating the JSON response. The `mainGame` function determines the appropriate game mode based on the level and calls the corresponding helper functions.

### `main` Function

The `main` function initializes the `GameLogic` instance and starts the main game loop. It listens for HTTP requests, parses the JSON data, and updates the game state based on the received input. It then returns the updated game state as a JSON response.

## Conclusion

This Snake game implementation provides a fun and interactive gameplay experience. With the C++ backend and React frontend, the game combines the power of Boost libraries for networking and JSON manipulation with the flexibility of a modern and interactive user interface. Enjoy playing the game and have fun!

