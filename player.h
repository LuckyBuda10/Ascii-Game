#pragma once
#include <vector>

class Player {
    public:
        Player(int startX, int startY, int startLives, int startScore);

        int getX();
        int getY();
        int getLives();
        int getScore();

        void move(char input, std::vector<std::vector<char>>& map);
        void hitBomb();
        void incrementScore();
        void incrementHealth();
        void checkCollision(std::vector<std::vector<char>>& map);

        void die();
    private:
        int x, y, lives, score;
};