import React, { useState, useEffect, useRef } from "react";
import { Box, Button, ButtonGroup, Typography } from "@mui/material";
import { RiAppleLine } from "react-icons/ri"; 

type SnakePart = { x: number; y: number };
const Board: React.FC = () => {
  let head:any;
  const boardSize = 20;
  const initialSnake: SnakePart[] = [{ x: 10, y: 10 }];
  const [snake, setSnake] = useState<SnakePart[]>(initialSnake);
  const [direction, setDirection] = useState<string | null>(null);
  const [level, setLevel] = useState<string | null>("EASY");
  const [gameOver, setGameOver] = useState<Boolean | null>(false);
  const [stats, setStats] = useState({ score: 0, length: initialSnake.length });
  const [lastID, setLastID] = useState(null);
  const generateRandomFruit = () => {
    const x = Math.floor(Math.random() * boardSize);
    const y = Math.floor(Math.random() * boardSize);
    return { x, y };
  };

  const [fruit, setFruit] = useState<SnakePart | null>(generateRandomFruit());

  const gameInterval = useRef<NodeJS.Timeout | null>(null);

  useEffect(() => {
    document.addEventListener("keydown", handleKeyDown);
    return () => {
      document.removeEventListener("keydown", handleKeyDown);
    };
  }, []);

  useEffect(() => {
    if (direction !== null) {
      gameInterval.current = setInterval(() => {
        handleGameLogic();
      }, 100);
    }

    return () => {
      if (gameInterval.current) clearInterval(gameInterval.current);
    };
  }, [snake, direction]);


  const handleKeyDown = (event: { key: string }) => {
    const key = event.key.toLowerCase();
    if (["w", "a", "s", "d"].includes(key) && isOppositeDirection(direction, key)) {
      setDirection(key);
    }
  };

  const isOppositeDirection = (currentDir: string | null, newDir: string) => {
    return (
      currentDir === null ||
      (currentDir === "w" && newDir !== "s") ||
      (currentDir === "a" && newDir !== "d") ||
      (currentDir === "s" && newDir !== "w") ||
      (currentDir === "d" && newDir !== "a")
    );
  };

  const handleGameLogic = () => {
    let newSnake = [...snake];
    head = { ...newSnake[0] };
    switch (direction) {
      case "w":
        head.y -= 1;
        break;
      case "a":
        head.x -= 1;
        break;
      case "s":
        head.y += 1;
        break;
      case "d":
        head.x += 1;
        break;
    }
  
    newSnake.unshift(head);
    if (fruit && head.x === fruit.x && head.y === fruit.y) {
      setFruit(generateRandomFruit());
    } else {
      newSnake.pop();
    }
    setSnake(newSnake);
  
    sendDataToServer();
  };
  

  const reset = () => {
    setSnake(initialSnake);
    setDirection(null);
    setLevel(level);
    setGameOver(false);
    setStats({ score: 0, length: initialSnake.length });
  };


  const sendDataToServer = async () => {
    try {
      let res = await fetch("http://127.0.0.1:1337", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
          head: head,
          snake: snake,
          fruit: fruit,
          score: stats.score,
          length: stats.length,
          level: level,
          gameOver: gameOver,
        }),
      });
      const data = await res.json();
      console.log("data", data);
  
      if (data.id !== lastID) {
        setLastID(data.id);
  
        if (data.snake) {
          const newSnakePos = [
            {
              x: data.snake.x,
              y: data.snake.y,
            },
          ];
          setSnake(newSnakePos);
        }
  
        if (data.fruit) {
          const newFruit = {
            x: data.fruit.x,
            y: data.fruit.y,
          };
          setFruit(newFruit);
        }
  
        setGameOver(data.gameOver || false);
        if (data.length) {
          const newSnakeLength = data.length;

          setStats({ 
            score:data.score,
            length: newSnakeLength 
          });
        
          const newSnake = [...snake];
          while (newSnake.length < newSnakeLength) {
            const tailPart = { x: -1, y: -1 };
            newSnake.push(tailPart);
          }
          
          setSnake(newSnake);
        }
      }
    } catch (error) {
      console.error("Błąd:", error);
    }
  };
  

    return (
    <>
      <Typography
        sx={{
          color: "greenyellow",
          textAlign: "center",
          fontSize: "2.2rem",
        }}
      >
        SNAKE BY TURBO1337GS
      </Typography>

      <Box
        sx={{
          backgroundColor: "black",
          height: `${boardSize * 20}px`,
          width: `${boardSize * 20}px`,
          display: "flex",
          justifyContent: "center",
          alignItems: "center",
          position: "relative",
          margin: "auto",
        }}
      >
        {snake.map((part, index) => (
          <Box
            key={index}
            sx={{
              backgroundColor: index === 0 ? "green" : "greenyellow",
              position: "absolute",
              top: `${part.y * 20}px`,
              left: `${part.x * 20}px`,
              width: "20px",
              height: "20px",
            }}
          ></Box>
        ))}

        {fruit && (
          <RiAppleLine
            style={{
              position: "absolute",
              top: `${fruit.y * 20}px`,
              left: `${fruit.x * 20}px`,
              fontSize: "20px",
              color: "red",
            }}
          />
        )}
      </Box>

      <Box
        sx={{
          backgroundColor: "black",
          height: "60px",
          width: `${boardSize * 20}px`,
          display: "flex",
          justifyContent: "space-between",
          alignItems: "center",
          margin: "auto",
          padding: "0 20px",
        }}
      >
        <Typography sx={{ color: "greenyellow" }}>
          Wynik: {stats.score}
        </Typography>
        <Typography sx={{ color: "greenyellow" }}>
          Długość: {stats.length}
        </Typography>
      </Box>
      <ButtonGroup
        color="primary"
        aria-label="outlined primary button group"
      >
        <Button
          onClick={() => setLevel("EASY")}
          variant={level === "EASY" ? "contained" : "outlined"}
        >
          Łatwy
        </Button>
        <Button
          onClick={() => setLevel("MEDIUM")}
          variant={level === "MEDIUM" ? "contained" : "outlined"}
        >
          Średni
        </Button>
        <Button
          onClick={() => setLevel("HARD")}
          variant={level === "HARD" ? "contained" : "outlined"}
        >
          Trudny
        </Button>
      </ButtonGroup>

      {/* Dodaj popup końca gry */}
      {gameOver && (
        <Box
          sx={{
            position: "fixed",
            top: 0,
            left: 0,
            width: "100%",
            height: "100%",
            backgroundColor: "rgba(0, 0, 0, 0.5)",
            display: "flex",
            justifyContent: "center",
            alignItems: "center",
          }}
        >
          <Box
            sx={{
              backgroundColor: "black",
              padding: "20px",
              borderRadius: "5px",
              textAlign: "center",
            }}
          >
            <Typography variant="h4" sx={{ color: "red" }}>
              Koniec gry!
            </Typography>
            <Typography variant="body1">
              Twój wynik: {stats.score}
            </Typography>
            <Button
              variant="contained"
              color="primary"
              onClick={() => {
                reset();
              }}
            >
              Zagraj ponownie
            </Button>
          </Box>
        </Box>
      )}
    </>
  );
};

export default Board;
