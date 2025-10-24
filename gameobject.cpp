#include "gameobject.h"
#include "utility.h"
#include "player.h"
#include <thread>
#include <chrono>
#include <vector>

GameObject::GameObject(bool isHealth, float duration) {
    this->isHealth = isHealth;
    this->duration = duration;
    isCollected = false;
}

void GameObject::objCollect(std::vector<std::vector<char>>& map) {
    if (isCollected)
        return;

    isCollected = true;
    removeGameObj(*this, map);
}

int GameObject::getX() { return x; }
int GameObject::getY() { return y; }
bool GameObject::getIsHealth() { return isHealth; }

bool GameObject::objIsCollected() {
    return isCollected;
}

void GameObject::spawn(int x, int y, std::vector<std::vector<char>>& map) {
    this->x = x;
    this->y = y;

    char symbol = isHealth ? '+' : 'O';
    map[y][x] = symbol;

    std::thread([this, &map]() {
        std::this_thread::sleep_for(std::chrono::duration<float>(duration));
        if (!isCollected) {
            removeGameObj(*this, map);
        }
    }).detach();
}