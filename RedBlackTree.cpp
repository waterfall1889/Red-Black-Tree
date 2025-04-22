#include "RedBlackTree.h"
#include <iostream>
#include <queue>
#include <stack>
#include <vector>


// 构造函数：初始化一个空的红黑树
RedBlackTree::RedBlackTree() {
    this->root = nullptr;
}

// 构造函数：根据数据初始化红黑树
RedBlackTree::RedBlackTree(std::vector<std::pair<uint64_t, std::string>>& data) {
    this->root = nullptr;
    for (auto& item : data) {
        insertNode(item.first, item.second);
    }
}

// 析构函数：清空树释放内存
RedBlackTree::~RedBlackTree() {
    clear();
}

// 递归清空树
void RedBlackTree::clear(Node*& t) {
    if (!t) return;
    clear(t->leftChild);
    clear(t->rightChild);
    delete t;
    t = nullptr;  // 将指针设置为空，避免悬挂指针
}

// 公共方法清空树
void RedBlackTree::clear() {
    clear(root);
}

// 检查树是否为空
bool RedBlackTree::isEmpty() const {
    return (this->root == nullptr);
}

// 查找指定键值的节点
RedBlackTree::Node* RedBlackTree::findNode(uint64_t k) {
    if (this->isEmpty()) {
        return nullptr;
    }

    Node* tmp = this->root;
    while (tmp != nullptr) {
        if (tmp->key == k) {
            return tmp;
        }
        if (tmp->key > k) {
            tmp = tmp->leftChild;
        } else {
            tmp = tmp->rightChild;
        }
    }
    return nullptr;
}

// 插入节点
void RedBlackTree::insertNode(uint64_t k, std::string& s) {
    if (isEmpty()) {
        Node* node = new Node(k, s, Node::BLACK);
        this->root = node;
        return;
    }

    Node* curNode = this->root;
    while (curNode != nullptr) {
        if (curNode->key == k) {
            curNode->value = s;
            return;
        } else if (curNode->key > k) {
            if (curNode->leftChild) {
                curNode = curNode->leftChild;
            } else {
                curNode->leftChild = new Node(k, s, Node::RED);
                curNode->leftChild->parent = curNode;
                fixInsert(curNode->leftChild);
                return;
            }
        } else {
            if (curNode->rightChild) {
                curNode = curNode->rightChild;
            } else {
                curNode->rightChild = new Node(k, s, Node::RED);
                curNode->rightChild->parent = curNode;
                fixInsert(curNode->rightChild);
                return;
            }
        }
    }
}

bool RedBlackTree::deleteNode(uint64_t k) {
    Node* target = findNode(k); // 查找要删除的节点
    if (!target) {
        return false; // 如果找不到节点，则返回 false
    }

    Node* nodeToDelete = target;
    Node* child = nullptr;
    Node* parent = nullptr;
    Node::Color originalColor = nodeToDelete->nodeColor;

    // Case 1: Node to delete has two children
    if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild != nullptr) {
        nodeToDelete = successor(nodeToDelete);  // 获取后继节点
        originalColor = nodeToDelete->nodeColor;
        child = nodeToDelete->rightChild;
        parent = nodeToDelete->parent;

        if (nodeToDelete->parent == target) {
            parent = nodeToDelete;  // 如果后继节点是目标节点的右子节点
        } else {
            if (child != nullptr) {
                child->parent = nodeToDelete->parent;
            }
            nodeToDelete->parent->leftChild = child;
            nodeToDelete->rightChild = target->rightChild;
            target->rightChild->parent = nodeToDelete;
        }

        target->key = nodeToDelete->key;
        target->value = nodeToDelete->value;
    }
        // Case 2: Node to delete has one or zero children
    else {
        if (nodeToDelete->leftChild != nullptr) {
            child = nodeToDelete->leftChild;
        } else {
            child = nodeToDelete->rightChild;
        }

        parent = nodeToDelete->parent;

        if (child != nullptr) {
            child->parent = parent;
        }

        if (parent == nullptr) {
            root = child; // 如果是根节点，更新根节点
        } else if (nodeToDelete == parent->leftChild) {
            parent->leftChild = child;
        } else {
            parent->rightChild = child;
        }
    }

    if (originalColor == Node::BLACK) {
        fixDelete(child, parent); // 删除后的修复
    }

    delete nodeToDelete;  // 删除节点
    return true;
}

void RedBlackTree::fixDelete(Node* node, Node* parent) {
    Node* sibling = nullptr;

    // 仅在节点颜色为黑且节点不是根节点时，才执行修复操作
    while (node != root && node != nullptr && node->nodeColor == Node::BLACK) {
        if (node == parent->leftChild) {
            sibling = parent->rightChild;

            // Case 1: Sibling is RED
            if (sibling != nullptr && sibling->nodeColor == Node::RED) {
                sibling->nodeColor = Node::BLACK;
                parent->nodeColor = Node::RED;
                leftRotate(parent);
                sibling = parent->rightChild;  // 旋转后，更新 sibling
            }

            // Case 2: Sibling's children are both BLACK
            if (sibling != nullptr &&
                sibling->leftChild != nullptr && sibling->leftChild->nodeColor == Node::BLACK &&
                sibling->rightChild != nullptr && sibling->rightChild->nodeColor == Node::BLACK) {
                sibling->nodeColor = Node::RED;
                node = parent;
                parent = node->parent;
            } else {
                // Case 3: Sibling's right child is BLACK
                if (sibling != nullptr && sibling->rightChild != nullptr && sibling->rightChild->nodeColor == Node::BLACK) {
                    sibling->leftChild->nodeColor = Node::BLACK;
                    sibling->nodeColor = Node::RED;
                    rightRotate(sibling);
                    sibling = parent->rightChild;  // 旋转后，更新 sibling
                }

                // Case 4: Sibling's right child is RED
                if (sibling != nullptr) {
                    sibling->nodeColor = parent->nodeColor;
                    parent->nodeColor = Node::BLACK;
                    sibling->rightChild->nodeColor = Node::BLACK;
                    leftRotate(parent);
                    node = root;
                }
            }
        } else {
            sibling = parent->leftChild;

            // Case 1: Sibling is RED
            if (sibling != nullptr && sibling->nodeColor == Node::RED) {
                sibling->nodeColor = Node::BLACK;
                parent->nodeColor = Node::RED;
                rightRotate(parent);
                sibling = parent->leftChild;  // 旋转后，更新 sibling
            }

            // Case 2: Sibling's children are both BLACK
            if (sibling != nullptr &&
                sibling->leftChild != nullptr && sibling->leftChild->nodeColor == Node::BLACK &&
                sibling->rightChild != nullptr && sibling->rightChild->nodeColor == Node::BLACK) {
                sibling->nodeColor = Node::RED;
                node = parent;
                parent = node->parent;
            } else {
                // Case 3: Sibling's left child is BLACK
                if (sibling != nullptr && sibling->leftChild != nullptr && sibling->leftChild->nodeColor == Node::BLACK) {
                    sibling->rightChild->nodeColor = Node::BLACK;
                    sibling->nodeColor = Node::RED;
                    leftRotate(sibling);
                    sibling = parent->leftChild;  // 旋转后，更新 sibling
                }

                // Case 4: Sibling's left child is RED
                if (sibling != nullptr) {
                    sibling->nodeColor = parent->nodeColor;
                    parent->nodeColor = Node::BLACK;
                    sibling->leftChild->nodeColor = Node::BLACK;
                    rightRotate(parent);
                    node = root;
                }
            }
        }
    }

    if (node != nullptr) {
        node->nodeColor = Node::BLACK;  // 最终节点颜色应为黑色
    }
}


// 左旋操作
void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->rightChild;
    x->rightChild = y->leftChild;

    if (y->leftChild != nullptr) {
        y->leftChild->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->leftChild) {
        x->parent->leftChild = y;
    } else {
        x->parent->rightChild = y;
    }

    y->leftChild = x;
    x->parent = y;
}

// 右旋操作
void RedBlackTree::rightRotate(Node* pNode) {
    Node* leftChild = pNode->leftChild;
    pNode->leftChild = leftChild->rightChild;

    if (leftChild->rightChild != nullptr) {
        leftChild->rightChild->parent = pNode;
    }

    leftChild->parent = pNode->parent;

    if (pNode->parent == nullptr) {
        root = leftChild;
    } else if (pNode == pNode->parent->rightChild) {
        pNode->parent->rightChild = leftChild;
    } else {
        pNode->parent->leftChild = leftChild;
    }

    leftChild->rightChild = pNode;
    pNode->parent = leftChild;
}

// 获取中序遍历数据
void RedBlackTree::getData(std::vector<std::pair<uint64_t, std::string>>& data) const {
    inOrderTraverseHelper(root, data);
}

void RedBlackTree::inOrderTraverseHelper(Node* node, std::vector<std::pair<uint64_t, std::string>>& data) const {
    if (node == nullptr) {
        return;
    }
    inOrderTraverseHelper(node->leftChild, data);
    data.push_back({node->key, node->value});
    inOrderTraverseHelper(node->rightChild, data);
}

// 前序遍历
void RedBlackTree::preOrderTraverse() const {
    if (isEmpty()) return;
    std::stack<Node*> tmpStack;
    tmpStack.push(this->root);
    std::cout << "Pre-order traverse:\n";
    while (!tmpStack.empty()) {
        Node* curNode = tmpStack.top();
        tmpStack.pop();
        if (curNode->rightChild) {
            tmpStack.push(curNode->rightChild);
        }
        if (curNode->leftChild) {
            tmpStack.push(curNode->leftChild);
        }
        std::cout << curNode->key << ": " << curNode->value << std::endl;
    }
}

// 中序遍历
void RedBlackTree::inOrderTraverse() const {
    if (isEmpty()) return;
    std::cout << "In-order traverse:\n";
    std::vector<std::pair<uint64_t, std::string>> data;
    getData(data);
    for (const auto& item : data) {
        std::cout << item.first << ": " << item.second << std::endl;
    }
}

// 后序遍历
void RedBlackTree::postOrderTraverse() const {
    if (isEmpty()) return;
    std::stack<Node*> tmpStack;
    std::stack<Node*> outputStack;
    tmpStack.push(this->root);
    std::cout << "Post-order traverse:\n";
    while (!tmpStack.empty()) {
        Node* curNode = tmpStack.top();
        tmpStack.pop();
        outputStack.push(curNode);
        if (curNode->leftChild) {
            tmpStack.push(curNode->leftChild);
        }
        if (curNode->rightChild) {
            tmpStack.push(curNode->rightChild);
        }
    }
    while (!outputStack.empty()) {
        Node* curNode = outputStack.top();
        outputStack.pop();
        std::cout << curNode->key << ": " << curNode->value << std::endl;
    }
}

// 层次遍历
void RedBlackTree::levelOrderTraverse() const {
    if (isEmpty()) return;
    std::queue<Node*> tmpQueue;
    tmpQueue.push(this->root);
    std::cout << "Level-order traverse:\n";
    while (!tmpQueue.empty()) {
        Node* curNode = tmpQueue.front();
        tmpQueue.pop();
        std::cout << curNode->key << ": " << curNode->value << std::endl;
        if (curNode->leftChild) {
            tmpQueue.push(curNode->leftChild);
        }
        if (curNode->rightChild) {
            tmpQueue.push(curNode->rightChild);
        }
    }
}

// 查找当前节点的中序后继节点
RedBlackTree::Node* RedBlackTree::successor(Node* node) {
    // 如果节点有右子树，后继节点是右子树中的最左节点
    if (node->rightChild != nullptr) {
        Node* tmp = node->rightChild;
        while (tmp->leftChild != nullptr) {
            tmp = tmp->leftChild;
        }
        return tmp;
    }

    // 如果没有右子树，后继节点是它的父节点中，第一个比当前节点大的节点
    Node* parent = node->parent;
    while (parent != nullptr && node == parent->rightChild) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

void RedBlackTree::fixInsert(Node* node) {
    Node* uncle = nullptr;
    // 直到根节点，或父节点是黑色节点，结束
    while (node != root && node->parent->nodeColor == Node::RED) {
        // 如果父节点是祖父节点的左子节点
        if (node->parent == node->parent->parent->leftChild) {
            uncle = node->parent->parent->rightChild;

            // Case 1: 叔叔节点是红色的
            if (uncle != nullptr && uncle->nodeColor == Node::RED) {
                node->parent->nodeColor = Node::BLACK;
                uncle->nodeColor = Node::BLACK;
                node->parent->parent->nodeColor = Node::RED;
                node = node->parent->parent;  // 向上调整，检查祖父节点
            } else {
                // Case 2: 叔叔节点是黑色的，且当前节点是右子节点
                if (node == node->parent->rightChild) {
                    node = node->parent;
                    leftRotate(node);  // 左旋转，使得当前节点成为左子节点
                }

                // Case 3: 叔叔节点是黑色的，且当前节点是左子节点
                node->parent->nodeColor = Node::BLACK;
                node->parent->parent->nodeColor = Node::RED;
                rightRotate(node->parent->parent);  // 右旋转调整
            }
        } else {  // 如果父节点是祖父节点的右子节点（对称情况）
            uncle = node->parent->parent->leftChild;

            // Case 1: 叔叔节点是红色的
            if (uncle != nullptr && uncle->nodeColor == Node::RED) {
                node->parent->nodeColor = Node::BLACK;
                uncle->nodeColor = Node::BLACK;
                node->parent->parent->nodeColor = Node::RED;
                node = node->parent->parent;  // 向上调整，检查祖父节点
            } else {
                // Case 2: 叔叔节点是黑色的，且当前节点是左子节点
                if (node == node->parent->leftChild) {
                    node = node->parent;
                    rightRotate(node);  // 右旋转，使得当前节点成为右子节点
                }

                // Case 3: 叔叔节点是黑色的，且当前节点是右子节点
                node->parent->nodeColor = Node::BLACK;
                node->parent->parent->nodeColor = Node::RED;
                leftRotate(node->parent->parent);  // 左旋转调整
            }
        }
    }

    // 确保根节点为黑色
    root->nodeColor = Node::BLACK;
}

std::string RedBlackTree::searchKey(uint64_t k) {
    Node *n = findNode(k);
    if(n == nullptr){
        return {};
    }
    return n->value;
}
