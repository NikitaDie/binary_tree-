#include <iostream>

class Node
{
private:
    int value;
    Node* right;
    Node* left;
    Node* prev;

public:
    Node(int value) :
        value{ value },
        right{ nullptr },
        left{ nullptr },
        prev{ nullptr }
    {}

    Node(const Node& node) :
        value{ node.value },
        right{ nullptr },
        left{ nullptr },
        prev{ nullptr }
    {}

    void setValue(const int& new_value)
    {
        this->value = new_value;
    }

    void setRight(Node* new_right)
    {
        this->right = new_right;
        this->right->prev = this;
    }

    void setLeft(Node* new_left)
    {
        this->left = new_left;
        this->left->prev = this;
    }

    const int& getValue() const
    {
        return this->value;
    }

    Node* getRight()
    {
        return this->right;
    };

    Node* getLeft()
    {
        return this->left;
    }

    Node* getPrev()
    {
        return this->prev;
    };

    friend std::ostream& operator<<(std::ostream& os, const Node& node);

    ~Node()
    {
        if (this->right != nullptr)
            delete this->right;

        if (this->left != nullptr)
            delete this->left;

        value = 0;
    }

};

std::ostream& operator<<(std::ostream& os, const Node& node)
{
    return os << node.getValue();
}

class Tree
{
private:
    Node* root;

    Node* chooseNextPosition(Node* current, int value) const
    {

        if (current == nullptr)
            return nullptr;     //TODO throw exception

        if (value >= current->getValue())
        {
            current = current->getRight();
        }
        else {
            current = current->getLeft();
        }

        return current;
    }

public:
    Tree() = default;

    Node* getRoot()
    {
        return this->root;
    }

    void insert(int value)
    {

        if (this->root == nullptr)
        {
            this->root = new Node(value);
            return;
        }

        Node* current{ nullptr };
        Node* next_current{ this->root };

        while (next_current != nullptr)
        {
            current = next_current;
            next_current = chooseNextPosition(current, value);
        }

        if (value >= current->getValue())
        {
            current->setRight(new Node(value));
        }
        else
        {
            current->setLeft(new Node(value));
        }
    }

    const Node* getNext(Node* current) const // ?
    {
        if (current == nullptr)
            return nullptr;     //TODO throw exception

        return(current->getLeft());

    }

    Node* find(int value, Node* root) //this->root = root;
    {
        Node* current{ root };

        if (root == nullptr)
        {
            std::cout << "element doesn`t exist" << std::endl;
            return nullptr;
        }

        if (current->getValue() == value)
            return current;

        current = chooseNextPosition(current, value);
        find(value, current);
    }

    void printTree(Node* root) //root = this->root
    {

        if (root != nullptr)
        {
            printTree(root->getLeft());
            std::cout << root->getValue() << " ";
            printTree(root->getRight());
        }

    }

    void dl()
    {
        if (root != nullptr)
            delete(this->root);
    }

    ~Tree()
    {
        if (root != nullptr)
            delete(this->root);
    }

};

int main()
{

    Tree tree;

    tree.insert(45);
    tree.insert(55);
    tree.insert(34);
    tree.insert(1);
    tree.insert(28);

    tree.printTree(tree.getRoot());

    std::cout << std::endl;

    Node* tmp = tree.find(1, tree.getRoot());

    std::cout << tree.find(1, tree.getRoot())->getPrev()->getValue() << std::endl;

}
