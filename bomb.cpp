#include "bomb.h"
#include "player.h"

Bomb::Bomb(int startX, Player* p) {
    x = startX;
    y = -1;
    player = p;
    exploded = false;
}

int Bomb::getX() { return x; }
int Bomb::getY() { return y; }
bool Bomb::isExploded() { return exploded; }
void Bomb::explode() { exploded = true; }

void Bomb::move(std::vector<std::vector<char>>& map) {
    if (y != -1) {
        if (y == 0) {
            map[y][x] = '-';
        } else {
            map[y][x] = '.';
        }
    }

    drawMap(*player, map);
    y++;
    
    if (map[y][x] == 'P') {
        if (!exploded) {
            exploded = true;
            player->hitBomb();
        }
    } else {
        map[y][x] = 'B';
    }

    drawMap(*player, map);

    if (y >= MAP_HEIGHT - 1) {
        exploded = true;
    }
}
