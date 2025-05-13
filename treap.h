#ifndef TREAP_H
#define TREAP_H

#include "treapnode.h"
#include <utility>

class Treap {
public:
    Treap() : root(nullptr) {
        std::srand(std::time(nullptr)); // Инициализация генератора
    }
    ~Treap() { clear(root); }

    void insert(int key);
    void remove(int key);
    TreapNode* search(int key) const;
    void clear() { clear(root); root = nullptr; }

    TreapNode* getRoot() const { return root; }

private:
    TreapNode* root;

    std::pair<TreapNode*, TreapNode*> split(TreapNode* node, int key);
    TreapNode* merge(TreapNode* left, TreapNode* right);
    void clear(TreapNode* node);
};

#endif // TREAP_H
