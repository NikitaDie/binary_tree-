#include <iostream>

enum {
    s_root = 0,
    s_right = 1,
    s_left = 2
};

template <class T>
class Node
{
private:
    int value;
    Node* right;
    Node* left;
    Node* prev;
    int side;

public:
    Node(T value) :
        value{ value },
        right{ nullptr },
        left{ nullptr },
        prev{ nullptr },
        side{ s_root }
    {}

    /*Node(const Node& node) : //?
        value{ node.value },
        right{ nullptr },
        left{ nullptr },
        prev{ nullptr }
    {}*/

    void setValue(const int& new_value)
    {
        this->value = new_value;
    }

    void setRight(Node<T>* new_right)
    {
        if (new_right == nullptr)
        {
            this->right = nullptr;
            return;
        }

        this->right = new_right;
        this->right->prev = this;
        new_right->side = s_right;
    }

    void setLeft(Node<T>* new_left)
    {
        if (new_left == nullptr)
        {
            this->left = nullptr;
            return;
        }

        this->left = new_left;
        this->left->prev = this;
        new_left->side = s_left;
    }

    void setPrev(Node<T>* new_prev)
    {
        this->prev = new_prev;
    }

    const int& getValue() const
    {
        return this->value;
    }

    Node* getRight()
    {
        return this->right;
    };

    Node* getRight() const
    {
        return this->right;
    };

    Node* getLeft()
    {
        return this->left;
    }

    Node* getLeft() const
    {
        return this->left;
    }

    Node* getPrev()
    {
        return this->prev;
    };

    int getSide() const
    {
        return this->side;
    }

    template <class C>
    friend std::ostream& operator<<(std::ostream& os, const Node<C>& node);

    ~Node()
    {
        if (this->right != nullptr)
            delete this->right;

        if (this->left != nullptr)
            delete this->left;

        value = 0;
    }

};

template <class C>
std::ostream& operator<<(std::ostream& os, const Node<C>& node)
{
    return os << node.getValue();
}

template <class T>
class Tree
{
private:
    Node<T>* root;

    Node<T>* chooseNextPosition(Node<T>* current, int value) const
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

    bool isLeaf(const Node<T>* current) const
    {
        if (current->getLeft() == nullptr && current->getRight() == nullptr)
            return true;

        return false;
    }

public:
    Tree() :
        root{ nullptr }
    {}

    Node<T>* getRoot()
    {
        return this->root;
    }

    void insert(int value)
    {

        if (this->root == nullptr)
        {
            this->root = new Node<T>(value);
            return;
        }

        Node<T>* current{ nullptr };
        Node<T>* next_current{ this->root };

        while (next_current != nullptr)
        {
            current = next_current;
            next_current = chooseNextPosition(current, value);
        }

        if (value >= current->getValue())
        {
            current->setRight(new Node<T>(value));
        }
        else
        {
            current->setLeft(new Node<T>(value));
        }
    }

    void remove(T val)
    {
        Node<T>* current{ this->find(val, this->root) };

        if (current == nullptr)
        {
            std::cout << "element doesn`t exist" << std::endl;
            return;
        }

        if (isLeaf(current))
        {
            delete current;
            return;
        }

        Node<T>* tmp{ this->getNext(current) };

        if (current->getRight() != nullptr && current->getLeft() != nullptr)
        {

            if (tmp->getSide() == s_right)
                tmp->getPrev()->setRight(nullptr);
            else
                tmp->getPrev()->setLeft(nullptr);

            tmp->setRight(current->getRight());
            tmp->setLeft(current->getLeft());

        }

        if (current->getSide() == s_right)
        {
            current->getPrev()->setRight(tmp);
        } 
        else if (current->getSide() == s_left)
        {
            current->getPrev()->setLeft(tmp);
        }
       
        tmp->setPrev(current->getPrev());

        current->setRight(nullptr);
        current->setLeft(nullptr);

        delete current;
        return;
    }


    Node<T>* getPrev(Node<T>* current)
    {
        if (current == nullptr)
            return nullptr;   //TODO throw exception

        if (current->getLeft() != nullptr)
        {
            current = current->getLeft();

            while(current->getRight() != nullptr)
            {
                current = current->getRight();
            }

            return current;
        }

        if (current->getside() == s_right)
        {
            return current->getPrev();
        }

        while(current != this->root)
        {
            int tmp = current->getValue();

            current = current->getPrev();

            if(current->getValue() < tmp)
                return current;
        }

        std::cout << "This Node is the first." << std::endl;
        return nullptr;
    }

    Node<T>* getNext(Node<T>* current) 
    {
        if (current == nullptr)
            return nullptr;   //TODO throw exception

        if (current->getRight() != nullptr)
        {
            current = current->getRight();

            while(current->getLeft() != nullptr)
            {
                current = current->getLeft();
            }

            return current;
        }

        if (current->getSide() == s_left)
        {
            return current->getPrev();
        }

        while(current != this->root)
        {
            int tmp = current->getValue();

            current = current->getPrev();

            if(current->getValue() > tmp)
                return current;
        }

        std::cout << "This Node is the last." << std::endl;
        return nullptr;
    }

    Node<T>* find(int value, Node<T>* root) 
    {
        Node<T>* current{ root };

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

    void printTree(Node<T>* root)
    {

        if (root != nullptr)
        {
            printTree(root->getLeft());
            std::cout << root->getValue() << " ";
            printTree(root->getRight());
        }

    }

    ~Tree()
    {
        if (root != nullptr)
            delete(this->root);
    }

};

int main()
{

    Tree<int> tree;

    /*tree.insert(45);
    tree.insert(55);
    tree.insert(34);
    tree.insert(28);
    tree.insert(30);
    tree.insert(29);
    tree.insert(32);

    tree.printTree(tree.getRoot());

    std::cout << std::endl;

    //Node<T>* tmp = tree.find(1, tree.getRoot());

    //std::cout << tree.getPrev(tree.find(55, tree.getRoot()))->getValue() << std::endl;
    std::cout << tree.getNext(tree.find(32, tree.getRoot()))->getValue() << std::endl;*/

    tree.insert(89);
    tree.insert(92);
    tree.insert(90);
    tree.insert(28);
    tree.insert(58);
    tree.insert(32);
    tree.insert(37);
    tree.insert(79);
    tree.insert(72);
    tree.insert(23);
    tree.insert(2);
    tree.insert(10);

    tree.printTree(tree.getRoot());
    std::cout << std::endl;

    tree.remove(58);
    tree.printTree(tree.getRoot());
}
