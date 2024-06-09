#include "Tree.hpp"
#include <string>

#define SPACE ' '

using namespace std;

Tree<int> *createByList(const string &s)
{
    if (s.empty())
        return nullptr;

    stack<Tree<int> *> nodeStack;
    Tree<int> *root = nullptr;
    Tree<int> *currentNode = nullptr;
    int num = 0;
    bool numPending = false;

    for (char ch : s)
    {
        if (isdigit(ch))
        {
            num = num * 10 + (ch - '0');
            numPending = true;
        }
        else if (ch == '(')
        {
            if (numPending)
            {
                Tree<int> *newNode = new Tree<int>(num);
                if (!nodeStack.empty())
                {
                    nodeStack.top()->append(newNode);
                }
                nodeStack.push(newNode);
                if (!root)
                {
                    root = newNode;
                }
                num = 0;
                numPending = false;
            }
        }
        else if (ch == ')')
        {
            if (numPending)
            {
                Tree<int> *newNode = new Tree<int>(num);
                if (!nodeStack.empty())
                {
                    nodeStack.top()->append(newNode);
                }
                num = 0;
                numPending = false;
            }
            if (!nodeStack.empty())
            {
                nodeStack.pop();
            }
        }
        else if (ch == ',')
        {
            if (numPending)
            {
                Tree<int> *newNode = new Tree<int>(num);
                if (!nodeStack.empty())
                {
                    nodeStack.top()->append(newNode);
                }
                num = 0;
                numPending = false;
            }
        }
    }
    return root;
}

void printTreeByLevels(Tree<int> *root)
{
    if (!root)
        return;
    root->calculateCoor();
    queue<Tree<int> *> q;
    q.push(root);

    cout << string(root->coor*2, ' ');
    cout << "{" << root->val << "}" << endl;

    while (!q.empty())
    {
        int levelSize = q.size();
        vector<vector<Tree<int> *>> levels;
        vector<Tree<int> *> currentLevel;
        for (int i = 0; i < levelSize; ++i)
        {
            Tree<int> *node = q.front();
            q.pop();

            for (Tree<int> *child : node->children)
            {
                currentLevel.push_back(child);
                q.push(child);
            }

            if (!currentLevel.empty())
            {
                levels.push_back(currentLevel);

                currentLevel.clear();
            }
        }
        bool firstGroup = true;
        int tempCoor = 0;
        for (const auto &level : levels)
        {
            if (firstGroup)
                cout << string(level[0]->coor*2, SPACE);
            else
            {               
                cout << string(max((level[0]->coor - tempCoor -2)*2,0), SPACE);
            }
            cout << "{";
            for (size_t i = 0; i < level.size(); ++i)
            {
                if (i != 0)
                    cout << string((level[i]->coor - level[i - 1]->coor - 1)*2, SPACE);

                cout << level[i]->val<<" ";

            }
            tempCoor = level[level.size() - 1]->coor;
            cout << "}";
            firstGroup = false;
        }
        if (!levels.empty())
        {
            cout << endl;
        }
    }
}

int main()
{
    const string s = "9(2(1,1(1)),4(1,3(2(2(1,1)),1)),3(1,1,1(1)))";
    auto t = createByList(s);
    printTreeByLevels(t);
    return 0;
}
