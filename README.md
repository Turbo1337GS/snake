# snake
 # Snake Game

This is a simple Snake game implemented using C++ for the backend and React for the frontend using the Electron application framework.

## How to Play

1. The game board is a grid of size 20x20.
2. The snake starts with a single part at position (10, 10).
3. Use the keyboard arrow keys or WASD keys to control the movement of the snake.
4. The goal is to eat the fruit (represented by a red apple) that randomly appears on the board.
5. Each time the snake eats a fruit, its length increases and its score is incremented.
6. Avoid running into the walls or into the snake's own body, as this will end the game.
7. You can choose the game difficulty level by clicking the corresponding button at the bottom of the screen.

## Technologies Used

- React: A JavaScript library for building user interfaces.
- Material-UI (Mui): A popular React UI framework.
- Electron: A framework for building cross-platform desktop applications using web technologies.

## Setup
Before running the game, make sure you have the following dependencies installed:

- Node.js
- npm (Node Package Manager)

To set up and run the game, follow these steps:

1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Install the required dependencies by running the following command:
```bash
npm install
```
4. Once the dependencies are installed, start the game by running:
```bash
npm start
```
This will launch the game in an Electron window.

## Controls

- Use the arrow keys or WASD keys to control the snake's movement.
- Press the "Play Again" button to start a new game after the game is over.

## Acknowledgements

This Snake game was developed by Turbo1337GS.

Please note that the game sends game data to a server at "http://127.0.0.1:1337" using the POST method, which can be modified to fit your specific needs.

Feel free to explore the code and make any modifications you desire. Have fun playing Snake!
