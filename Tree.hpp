#include <iostream>
#include <queue>
#include <vector>
#include <stack>

template <typename T>
class Tree
{
public:
    T val;
    std::vector<Tree<T>*> children;
    int coor;

    Tree()
    {
        this->val = -1;
    }

    Tree(T val) : val(val) {}

    void append(T val)
    {
        Tree* child = new Tree(val);
        children.push_back(child);
    }
    void append(Tree* node)
    {
        children.push_back(node);
    }
    
    static int countLeaves(Tree* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        
        if (node->children.empty())
        {
            return 1;
        }

        int leafCount = 0;
        for (Tree* child : node->children)
        {
            leafCount += countLeaves(child);
        }

        return leafCount;
    }
    int countLeaves()
    {
        if (this == nullptr)
        {
            return 0;
        }
        
        if (this->children.empty())
        {
            return 1;
        }

        int leafCount = 0;
        for (Tree* child : this->children)
        {
            leafCount += countLeaves(child);
        }

        return leafCount;
    }

    void calculateCoor()
{
    int leafCoor = 0;
    std::stack<Tree*> stack;
    std::stack<Tree*> postOrderStack;

    // Step 1: Post-order traversal to fill postOrderStack
    stack.push(this);
    while (!stack.empty())
    {
        Tree* node = stack.top();
        stack.pop();
        postOrderStack.push(node);
        for (Tree* child : node->children)
        {
            stack.push(child);
        }
    }

    // Step 2: Calculate coor values in post-order
    while (!postOrderStack.empty())
    {
        Tree* node = postOrderStack.top();
        postOrderStack.pop();

        if (node->children.empty())
        {
            // It's a leaf node
            node->coor = leafCoor;
            leafCoor += 2;
        }
        else
        {
            // It's a non-leaf node
            int sumCoor = 0;
            for (Tree* child : node->children)
            {
                sumCoor += child->coor;
            }
            node->coor = sumCoor / node->children.size();
        }
    }
}

};
