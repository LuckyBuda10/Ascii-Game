#include <iostream>
#include <conio.h>
#include <thread>
#include <vector>
#include <random>
#include <windows.h>

#include "utility.h"
#include "player.h"
#include "bomb.h"
#include "gameobject.h"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    Player player(MAP_WIDTH / 2, MAP_HEIGHT / 2, 5, 0);
    std::vector<std::vector<char>> map(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, '.'));    

    map[player.getY()][player.getX()] = 'P';
    drawMap(player, map);

    std::thread bombSpawnThread(bombSpawner, &player, std::ref(bombs), std::ref(gen));
    bombSpawnThread.detach();

    std::thread gameObjSpawnThread(gameObjSpawner, &player, std::ref(gameObjects), std::ref(gen), std::ref(map));
    gameObjSpawnThread.detach();

    std::thread bombMoveThread(moveBombs, std::ref(bombs), std::ref(map));
    bombMoveThread.detach();

    char input;
    while (true) {
        if (_kbhit()) {
            input = getch();
            if (input == 'q') {
                break;
            } else {
                player.move(input, map);
                drawMap(player, map);
            }
        }

        if (gameOver) {
            break;
        }
    }

    drawMap(player, map);
    system("cls");
    std::cout << "Game Over!" << std::endl;
    std::cout << "Score: " << player.getScore() << std::endl;
    std::cout << "Lives: " << player.getLives() << std::endl;

    exit(0);
}