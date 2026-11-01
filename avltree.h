#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <vector>

// Nodo del arbol AVL
struct AVLNode {
    std::string key;   // palabra almacenada
    AVLNode* left;     // hijo izquierdo
    AVLNode* right;    // hijo derecho
    int height;        // altura del nodo

    AVLNode(const std::string& k);
    // Sin destructor propio: AVLTree::destroy() libera los nodos (evita doble free)
};

// Arbol balanceado AVL
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    // Inserta una palabra manteniendo el equilibrio
    void insert(const std::string& key);

    // Devuelve las palabras ordenadas alfabéticamente (inorder)
    std::vector<std::string> inorder() const;

    // Cantidad de nodos insertados
    size_t nodeCount() const;

    // Altura del arbol (cota AVL: <= 1.44*log2(n+2))
    int treeHeight() const;

private:
    AVLNode* root;
    size_t count;

    AVLNode* insert(AVLNode* node, const std::string& key);
    void destroy(AVLNode* node);
    void inorder(AVLNode* node, std::vector<std::string>& result) const;

    int height(AVLNode* node) const;
    int balanceFactor(AVLNode* node) const;
    void updateHeight(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
};

#endif
