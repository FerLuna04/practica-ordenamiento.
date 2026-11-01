#include "avltree.h"
#include <algorithm>

// Constructor de nodo
AVLNode::AVLNode(const std::string& k)
    : key(k), left(nullptr), right(nullptr), height(1) {}

// Destructor recursivo: libera hijos y el nodo actual
AVLNode::~AVLNode() {
    delete left;
    delete right;
}

AVLTree::AVLTree() : root(nullptr), count(0) {}

// Libera todo el arbol
AVLTree::~AVLTree() {
    destroy(root);
}

void AVLTree::destroy(AVLNode* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

// Retorna la altura de un nodo (0 si es nulo)
int AVLTree::height(AVLNode* node) const {
    return node ? node->height : 0;
}

// Actualiza la altura de un nodo según sus hijos
void AVLTree::updateHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

// Factor de equilibrio: altura izquierda - altura derecha
int AVLTree::balanceFactor(AVLNode* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

// Rotacion simple a la derecha
AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

// Rotacion simple a la izquierda
AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

// Inserta recursivamente y rebalancea si es necesario
AVLNode* AVLTree::insert(AVLNode* node, const std::string& key) {
    if (!node) {
        count++;
        return new AVLNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else {
        node->right = insert(node->right, key);
    }

    updateHeight(node);

    int balance = balanceFactor(node);

    // Casos de desbalance y rotaciones correspondientes
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Inserta una palabra en el arbol
void AVLTree::insert(const std::string& key) {
    root = insert(root, key);
}

// Recorrido inorder: izquierda, raiz, derecha
void AVLTree::inorder(AVLNode* node, std::vector<std::string>& result) const {
    if (!node) return;
    inorder(node->left, result);
    result.push_back(node->key);
    inorder(node->right, result);
}

// Devuelve todas las palabras ordenadas alfabeticamente
std::vector<std::string> AVLTree::inorder() const {
    std::vector<std::string> result;
    result.reserve(count);
    inorder(root, result);
    return result;
}

// Cantidad de nodos en el arbol
size_t AVLTree::nodeCount() const {
    return count;
}
