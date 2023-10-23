#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <vector>
#include <binders.h>
#include <string>
#include <sstream>
#include <nlohmann/json.hpp>
#include <algorithm>
/**
 * Create a JSON representation of the game state.
 *
 * @param snakeX The x-coordinate of the snake's head.
 * @param snakeY The y-coordinate of the snake's head.
 * @param fruitX The x-coordinate of the fruit.
 * @param fruitY The y-coordinate of the fruit.
 * @param score The player's score.
 * @param length The length of the snake.
 * @param headX The x-coordinate of the snake's head.
 * @param headY The y-coordinate of the snake's head.
 * @param level The current game level.
 * @param isGameOver Whether the game is over.
 *
 * @return A JSON string representing the game state.
 */
long int ID = 0;
std::string createJson(
    int snake_x,
    int snake_y,
    int fruit_x,
    int fruit_y,
    int score,
    int len,
    int head_x,
    int head_y,
    std::string level,
    bool gameOver)
{
    ID++;
    nlohmann::json j;

    j["id"] = ID;
    j["snake"] = {{"x", snake_x}, {"y", snake_y}};
    j["fruit"] = {{"x", fruit_x}, {"y", fruit_y}};
    j["head"] = {{"x", head_x}, {"y", head_y}};
    j["gameOver"] = gameOver;
    j["score"] = score;
    j["level"] = level;
    j["score"] = score;
    j["length"] = len;

    std::string jsonString = j.dump();
    // std::cout << "Send JSON: " << jsonString << "\n";

    return jsonString;
}

using boost::asio::ip::tcp;
namespace http = boost::beast::http;
namespace beast = boost::beast;
using namespace boost::property_tree;

struct Point
{
    size_t x;
    size_t y;
};

struct GameData
{
    std::vector<Point> snake; // List of points representing the snake's body.
    std::vector<Point> head;  // List of points representing the snake's head.
    Point fruit;              // The position of the fruit.
    size_t score;             // The player's score.
    size_t length;            // The length of the snake.
    std::string level;        // The current game level.
    bool gameOver;            // Flag indicating if the game is over.

    /**
     * Load game data from a JSON string.
     *
     * @param json_str The JSON string containing game data.
     */
    void load(const std::string &json_str)
    {
        ptree pt;
        std::istringstream is(json_str);
        // std::cout << "Load JSON: " << json_str << "\n";
        try
        {
            read_json(is, pt);

            snake.clear();
            for (const auto &item : pt.get_child("snake"))
            {
                Point p;
                p.x = item.second.get("x", 10);
                p.y = item.second.get("y", 10);
                snake.push_back(p);
            }

            head.clear();
            Point p;
            p.x = pt.get("head.x", 10);
            p.y = pt.get("head.y", 10);
            head.push_back(p);

            fruit.x = pt.get("fruit.x", 0);
            fruit.y = pt.get("fruit.y", 0);
            score = pt.get("score", 0);
            length = pt.get("length", 1);
            level = pt.get("level", "EASY");
            gameOver = pt.get("gameOver", false);
        }
        catch (const boost::property_tree::json_parser_error &e)
        {
            std::cerr << "Failed to parse JSON: " << e.what() << '\n';
            std::cerr << "JSON content was:\n"
                      << json_str << '\n';
        }
    }
};
class GameLogic
{
private:
    const int MaxY = 22;
    const int MaxX = 20;

    struct SnakePart
    {
        int x;
        int y;
    };
    /**
     * Check for collision with the snake's own body.
     *
     * @param snake A vector of SnakePart representing the snake's body.
     * @return True if a collision is detected, otherwise false.
     */
    bool checkCollision(std::vector<SnakePart> snake)
    {
        SnakePart head = snake[0];

        for (int i = 1; i < snake.size(); i++)
        {
            if (head.x == snake[i].x && head.y == snake[i].y)
            {
                return true;
            }
        }

        return false;
    }

    std::string EasyMode(GameData &gs, std::string &data)
    {
        gs.load(data);
        std::string res = "";
        int snakex, snakey;
        std::string Level = "EASY";
        for (auto const &point : gs.snake)
        {
            snakex = point.x;
            snakey = point.y;
        }
        // Check pos of snake

        for (auto &point : gs.head)
        {

            if (point.x == gs.fruit.x && point.y == gs.fruit.y)
            {
                std::cout << "Zjedzone jabłuszko" << std::endl;
                int PosrFruit = rand() % 20;

                gs.score += 1;
                gs.length += 1;

                res = createJson(
                    -999, -999,
                    PosrFruit, PosrFruit,
                    gs.score, gs.length,
                    -999, -999,
                    Level,
                    false);
            }
            if (point.x == -1)
            {
                res =
                    createJson(MaxX, snakey, gs.fruit.x,
                               gs.fruit.y, gs.score - 1, gs.length - 1, MaxX, point.y, Level, false);
            }
            if (point.x == (MaxX))
            {
                res =
                    createJson(0, snakey, gs.fruit.x,
                               gs.fruit.y, gs.score - 1, gs.length - 1, 0, point.y, Level, false);
            }
            if (point.y == -1)
            {
                res = createJson(snakex, MaxY, gs.fruit.x, gs.fruit.y,
                                 gs.score - 1, gs.length - 1, point.x, MaxY, Level, false);
            }
            if (point.y == MaxY)
            {
                res = createJson(snakex, 0, gs.fruit.x, gs.fruit.y,
                                 gs.score - 1, gs.length - 1, point.x, 0, Level, false);
            }
        }
        return res;
    }
    std::string MediumMode(GameData &gs, std::string &data)
    {
        std::string Level = "MEDIUM";

        gs.load(data);
        std::string res = "";
        int snakex, snakey;
        for (auto const &point : gs.snake)
        {
            snakex = point.x;
            snakey = point.y;
        }

        for (auto &point : gs.head)
        {

            if (point.x == gs.fruit.x && point.y == gs.fruit.y)
            {
                std::cout << "Zjedzone jabłuszko" << std::endl;
                int PosrFruit = rand() % 20;

                gs.score += 1;
                gs.length += 1;

                res = createJson(
                    -999, -999,
                    PosrFruit, PosrFruit,
                    gs.score, gs.length,
                    -999, -999,
                    Level,
                    false);
            }

            if (point.x == -1 ||
                point.x == (MaxX) ||
                point.y == -1 ||
                point.y == MaxY)
            {
                res =
                    createJson(snakex, snakey, gs.fruit.x, gs.fruit.y, gs.score, gs.length, point.x, point.y, Level, true);
            }

            std::vector<SnakePart> snake;
            for (auto const &point : gs.snake)
            {
                SnakePart part = {static_cast<int>(point.x), static_cast<int>(point.y)};
                snake.push_back(part);
            }

            bool collision = checkCollision(snake);
            if (collision)
            {
                std::cout << "DEAD \n";
                res =
                    createJson(snakex, snakey, gs.fruit.x, gs.fruit.y, gs.score, gs.length, point.x, point.y, Level, true);
            }
        }
        return res;
    }

    std::string HardMode(GameData &gs, std::string &data)
    {
        std::string Level = "HARD";

        gs.load(data);
        std::string res = "";
        int snakex, snakey;
        for (auto const &point : gs.snake)
        {
            snakex = point.x;
            snakey = point.y;
        }

        for (auto &point : gs.head)
        {
            if (point.x == gs.fruit.x && point.y == gs.fruit.y)
            {
                std::cout << "Zjedzone jabłuszko" << std::endl;
                int PosrFruit = rand() % 20;

                gs.score += 1;
                gs.length += 4;

                res = createJson(
                    -999, -999,
                    PosrFruit, PosrFruit,
                    gs.score, gs.length,
                    -999, -999,
                    Level,
                    false);
            }

            if (point.x == -1 ||
                point.x == (MaxX) ||
                point.y == -1 ||
                point.y == MaxY)
            {
                res =
                    createJson(snakex, snakey, gs.fruit.x, gs.fruit.y, gs.score, gs.length, point.x, point.y, Level, true);
            }

            std::vector<SnakePart> snake;
            for (auto const &point : gs.snake)
            {
                SnakePart part = {static_cast<int>(point.x), static_cast<int>(point.y)};
                snake.push_back(part);
            }

            bool collision = checkCollision(snake);
            if (collision)
            {
                std::cout << "DEAD \n";
                res =
                    createJson(snakex, snakey, gs.fruit.x, gs.fruit.y, gs.score, gs.length, point.x, point.y, Level, true);
            }
        }
        return res;
    }

public:
    std::string mainGame(GameData &gs, std::string &data)
    {
        gs.load(data);
        std::string res = "";
        if (gs.level == "EASY")
        {
            res = EasyMode(gs, data);
        }
        if (gs.level == "MEDIUM")
        {
            res = MediumMode(gs, data);
        }

        if (gs.level == "HARD")
        {
            res = HardMode(gs, data);
        }

        return res;
    }
};
extern GameLogic *gm;