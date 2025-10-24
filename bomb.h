#pragma once
#include "player.h"
#include "utility.h"
#include <vector>

class Bomb {
    public:
        Bomb(int startX, Player* p);

        int getX();
        int getY();
        bool isExploded();

        void explode();
        void move(std::vector<std::vector<char>>& map);

    private:
        int x, y;
        Player* player;
        bool exploded;
};