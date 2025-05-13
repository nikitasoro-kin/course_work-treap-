#ifndef TREAPNODE_H
#define TREAPNODE_H

#include <QString>
#include <cstdlib>
#include <ctime>

class TreapNode {
public:
    int key;
    int priority;
    TreapNode* left;
    TreapNode* right;
    int posX;
    int posY;

    TreapNode(int k) :
        key(k),
        priority(std::rand() % 100),
        left(nullptr),
        right(nullptr),
        posX(0),        //Переменная для x - координаты
        posY(0) {}      //Переменная для y - координаты
};

#endif // TREAPNODE_H
