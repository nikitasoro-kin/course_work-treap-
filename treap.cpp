#include "treap.h"

std::pair<TreapNode*, TreapNode*> Treap::split(TreapNode* node, int key) {
    if (!node) return {nullptr, nullptr};

    if (node->key <= key) {
        auto [left, right] = split(node->right, key);
        node->right = left;
        return {node, right};
    } else {
        auto [left, right] = split(node->left, key);
        node->left = right;
        return {left, node};
    }
}

TreapNode* Treap::merge(TreapNode* left, TreapNode* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

void Treap::insert(int key) {
    auto [left, right] = split(root, key);
    TreapNode* newNode = new TreapNode(key);
    root = merge(merge(left, newNode), right);
}

void Treap::remove(int key) {
    auto [L, R] = split(root, key);
    auto [L1, M] = split(L, key - 1);
    if (M) {
        delete M;
        M = nullptr;
    }
    root = merge(L1, R);
}

TreapNode* Treap::search(int key) const {
    TreapNode* current = root;
    while (current) {
        if (key == current->key) return current;
        current = key < current->key ? current->left : current->right;
    }
    return nullptr;
}

void Treap::clear(TreapNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}
