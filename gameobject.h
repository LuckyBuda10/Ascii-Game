#pragma once
#include "utility.h"
#include <vector>

class GameObject {
    public:
        GameObject(bool isHealth, float duration);

        void spawn(int x, int y, std::vector<std::vector<char>>& map);
        bool objIsCollected();

        int getX();
        int getY();
        bool getIsHealth();

        void objCollect(std::vector<std::vector<char>>& map);
    private:
        bool isHealth, isCollected;
        float duration;
        int x, y;
};