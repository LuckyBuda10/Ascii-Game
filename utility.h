#pragma once
#include "player.h"
#include "bomb.h"
#include "gameobject.h"
#include <random>
#include <atomic>
#include <mutex>
#include <windows.h>

#define MAP_WIDTH 16
#define MAP_HEIGHT 10

class Player;
class Bomb;
class GameObject;

extern std::atomic<bool> gameOver;
extern std::mutex mtx;
extern std::vector<Bomb> bombs;
extern std::vector<GameObject> gameObjects;

void drawMap(Player p, std::vector<std::vector<char>> map);
void bombSpawner(Player* p, std::vector<Bomb>& bombs, std::mt19937& random);
void gameObjSpawner(Player* p, std::vector<GameObject>& gameObjects, std::mt19937& random, std::vector<std::vector<char>>& map);
void moveBombs(std::vector<Bomb>& bombs, std::vector<std::vector<char>>& map);
void removeGameObj(GameObject& gameObject, std::vector<std::vector<char>>& map);
Bomb *locateBomb(std::vector<Bomb>& bombs, int lookX, int lookY);
GameObject * locateGameObject(int lookX, int lookY);