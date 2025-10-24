#include "utility.h"
#include "bomb.h"
#include "player.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>

std::atomic<bool> gameOver(false);
std::mutex mtx;
std::vector<Bomb> bombs;
std::vector<GameObject> gameObjects;

void drawMap(Player p, std::vector<std::vector<char>> map) {
    std::cout << "\x1b[2J\x1b[H";
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (y == 0) {
                if (map[y][x] == 'B') {
                    std::cout << map[y][x];
                } else{
                    std::cout << "-";
                }
            } else {
                std::cout << map[y][x];
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Score: " << p.getScore() << std::endl;
    std::cout << "Lives: " << p.getLives() << std::endl;
}

void bombSpawner(Player* p, std::vector<Bomb>& bombs, std::mt19937& random) {
    float timeBetweenBombs = 2.0f;
    std::uniform_int_distribution<int> genX(0, MAP_WIDTH - 1);

    while (true) {
        std::this_thread::sleep_for(std::chrono::duration<float>(timeBetweenBombs));

        {
            std::lock_guard<std::mutex> lock(mtx);
            bombs.emplace_back(genX(random), p);
        }
    }
}

void gameObjSpawner(Player* p, std::vector<GameObject>& gameObjects, std::mt19937& random, std::vector<std::vector<char>>& map) {
    float timeBetweenObjs;

    std::uniform_real_distribution<float> objSpawn(1.5, 6.5);

    std::uniform_int_distribution<int> genX(0, MAP_WIDTH - 1);
    std::uniform_int_distribution<int> genY(0, MAP_HEIGHT - 1);
    std::uniform_int_distribution<int> isHealth(1, 6);

    while (true) {
        timeBetweenObjs = objSpawn(random);

        std::this_thread::sleep_for(std::chrono::duration<float>(timeBetweenObjs));

        int healthNum = isHealth(random);
        bool healthFlag = healthNum == 6;

        {
            std::lock_guard<std::mutex> lock(mtx);
            gameObjects.emplace_back(healthFlag, 8.0);
            auto& go = gameObjects.back();

            while (true) {
                int x = genX(random);
                int y = genY(random);

                if (map[y][x] == '.') {
                    go.spawn(x, y, map);
                    break;
                }
            }
        }
    }
}

void moveBombs(std::vector<Bomb>& bombs, std::vector<std::vector<char>>& map) {
    float bombSpeed = 0.5f;

    while (true) {
        std::this_thread::sleep_for(std::chrono::duration<float>(bombSpeed));

        {
            std::lock_guard<std::mutex> lock(mtx);

            for (auto itr = bombs.begin(); itr != bombs.end(); ) {
                itr->move(map);
                if (itr->isExploded()) {
                    map[itr->getY()][itr->getX()] = '.';
                    itr = bombs.erase(itr);
                } else {
                    ++itr;
                }
            }
        }
    }
}

Bomb* locateBomb(std::vector<Bomb>& bombs, int lookX, int lookY) {
    for (auto& bomb : bombs) {
        if (bomb.getY() == lookY && bomb.getX() == lookX) {
            return &bomb;
        }
    }

    return nullptr;
}

GameObject* locateGameObject(int lookX, int lookY) {
    for (auto& go : gameObjects) {
        if (go.getY() == lookY && go.getX() == lookX) {
            return &go;
        }
    }

    return nullptr;
}

void removeGameObj(GameObject& gameObject, std::vector<std::vector<char>>& map) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto itr = gameObjects.begin(); itr != gameObjects.end(); ) {
        if (&(*itr) == &gameObject) {
            map[itr->getY()][itr->getX()] = '.';
            itr = gameObjects.erase(itr);   
        } else {
            ++itr;
        }
    }
}