
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <cstdint>

class RedBlackTree {
public:
    struct Node {
        uint64_t key;
        std::string value;
        Node* leftChild;
        Node* rightChild;
        Node* parent;
        enum Color { RED, BLACK } nodeColor;

        Node(uint64_t k, std::string& s, Color color)
                : key(k), value(s), leftChild(nullptr), rightChild(nullptr), parent(nullptr), nodeColor(color) {}
    };

    RedBlackTree();
    RedBlackTree(std::vector<std::pair<uint64_t, std::string>>& data);
    ~RedBlackTree();

    void clear();
    bool isEmpty() const;
    void insertNode(uint64_t k, std::string& s);
    bool deleteNode(uint64_t k);
    std::string searchKey(uint64_t k);

    void getData(std::vector<std::pair<uint64_t, std::string>>& data) const;

    void preOrderTraverse() const;
    void inOrderTraverse() const;
    void postOrderTraverse() const;
    void levelOrderTraverse() const;

private:
    Node* root;

    void clear(Node*& t);
    Node* findNode(uint64_t k);
    void fixInsert(Node* node);
    void fixDelete(Node* node, Node* parent);

    void leftRotate(Node* x);
    void rightRotate(Node* pNode);
    Node* successor(Node* node);

    void inOrderTraverseHelper(Node* node, std::vector<std::pair<uint64_t, std::string>>& data) const;
};