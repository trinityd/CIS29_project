#ifndef TILE_H
#define TILE_H

#include "../include/Enemy.h"
#include "../include/Item.h"
#include <vector>
#include <map>

class Tile
{
    public:
        Tile();

        int getCaps() { return caps; }
        void setCaps(int val) { caps = val; }

        bool containsElevator() { return elevator; }
        void makeElevator() { elevator = true; }

        bool containsPlayer() { return player; }
        void playerIn() { player = true; }
        void playerOut() { player = false; }

        bool containsEnemy() { return enemies.size() != 0; }
        void enemyIn(Enemy e) { enemies.push_back(e); }
        void enemyOut(const Enemy& e);
        Enemy& getEnemy(int i) { return enemies[i]; }
        int getNumEnemies() { return enemies.size(); }

        bool containsItem() { return (items.size() != 0); }
        void addItem(Item i) { items.push_back(i); }
        void removeItem(const Item& i);
        void removeItem(int i);
        Item& getItem(int i) { return items[i]; }
        int getNumItems() { return items.size(); }

        void setWall(std::string dir, bool val = true) { walls[dir] = val; }
        bool checkWall(std::string dir) { return walls[dir]; }

        std::vector<Enemy> enemies;
        std::vector<Item> items;
        int caps;
        bool elevator;
        bool player;
        std::map<std::string, bool> walls;
};

#endif // TILE_H
