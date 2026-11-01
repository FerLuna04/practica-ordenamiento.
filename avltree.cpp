#include "avltree.h"
#include <algorithm>

AVLNode::AVLNode(const std::string& k)
    : key(k), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr), count(0) {}

AVLTree::~AVLTree() { destroy(root); }

// Postorden: libera hijos y luego el nodo. Profundidad O(log n).
void AVLTree::destroy(AVLNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

int AVLTree::height(AVLNode* node) const { return node ? node->height : 0; }

void AVLTree::updateHeight(AVLNode* node) {
    if (node) node->height = 1 + std::max(height(node->left), height(node->right));
}

int AVLTree::balanceFactor(AVLNode* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* AVLTree::insert(AVLNode* node, const std::string& key) {
    if (!node) {
        count++;
        return new AVLNode(key);
    }

    if (key < node->key) node->left = insert(node->left, key);
    else                 node->right = insert(node->right, key);  // duplicados a la derecha

    updateHeight(node);
    int balance = balanceFactor(node);

    // El caso se decide por el factor de balance del HIJO (no comparando claves):
    // comparar claves falla con duplicados y deja el arbol desbalanceado.
    if (balance > 1) {                                    // pesado a la izquierda
        if (balanceFactor(node->left) < 0)                // caso Izq-Der
            node->left = rotateLeft(node->left);
        return rotateRight(node);                         // Izq-Izq
    }
    if (balance < -1) {                                   // pesado a la derecha
        if (balanceFactor(node->right) > 0)               // caso Der-Izq
            node->right = rotateRight(node->right);
        return rotateLeft(node);                          // Der-Der
    }
    return node;
}

void AVLTree::insert(const std::string& key) { root = insert(root, key); }

void AVLTree::inorder(AVLNode* node, std::vector<std::string>& result) const {
    if (!node) return;
    inorder(node->left, result);
    result.push_back(node->key);
    inorder(node->right, result);
}

std::vector<std::string> AVLTree::inorder() const {
    std::vector<std::string> result;
    result.reserve(count);
    inorder(root, result);
    return result;
}

size_t AVLTree::nodeCount() const { return count; }

int AVLTree::treeHeight() const { return height(root); }
