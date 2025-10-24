#include "player.h"
#include "utility.h"
#include "gameobject.h"

Player::Player(int startX, int startY, int startLives, int startScore) {
    x = startX;
    y = startY;
    lives = startLives;
    score = startScore;
}

int Player::getX() { return x; }
int Player:: getY() { return y; }
int Player:: getLives() { return lives; }
int Player:: getScore() { return score; }

void Player::move(char input, std::vector<std::vector<char>>& map) {
    map[y][x] = '.';

    if (input == 'w') y--;
    if (input == 'a') x--;
    if (input == 's') y++;
    if (input == 'd') x++;

    //Cant go on top row (for bombs)
    if (x >= MAP_WIDTH) x = MAP_WIDTH - 1;
    if (y >= MAP_HEIGHT) y = MAP_HEIGHT - 1;
    if (x < 0) x = 0;
    if (y < 1) y = 1;

    checkCollision(map);
    map[y][x] = 'P';
}

void Player::checkCollision(std::vector<std::vector<char>>& map) {
    if (map[y][x] == 'B') {
        Bomb* bomb = locateBomb(bombs, x, y);
        if (bomb != nullptr && !bomb->isExploded()) {
            bomb->explode();
            hitBomb();
        }
    } else if (map[y][x] == 'O' || map[y][x] == '+') {
        bool isHealthObj = map[y][x] == '+';

        GameObject* go = locateGameObject(x, y);
        if (go != nullptr) {
            if (go->getIsHealth()) {
                lives++;
            } else {
                score++;
            }
            go->objCollect(map);
        }
    }
}

void Player::hitBomb() {
    lives--;
    if (lives <= 0) {
        die();
    }
}

void Player::incrementScore() {
    score++;
}

void Player::die() {
    gameOver = true;
}