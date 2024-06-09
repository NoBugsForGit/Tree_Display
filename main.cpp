#include "Tree.hpp"
#include <string>

#define SPACE ' '

using namespace std;

Tree<int> *createByList(const string &s) 
// 通过字符串生成树。这个函数由AI生成，功能良好。若对此代码段有疑问，可以询问AI。
// 采用栈的思想实现。
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

// 主要的显示函数。用于按题给格式显示树。
// 本程序核心，唯一一段AI不能解决的代码。

{
    if (!root)
        return;
    root->calculateCoor(); // 调用类函数，计算所有坐标值
    queue<Tree<int> *> q; // 输出按层次输出，采用层次遍历。这是层次遍历所用队列。
    q.push(root); 

    // 输出初始根结点
    /*
        坐标与字符数的关系：我们规定，每两个字符占据一个坐标，
        这是为了规避可能出现的花括号位置重合问题，
        在接下来的所有逻辑中，生成空格数都是 坐标间隔数*2
    */
    cout << string(root->coor*2, ' ');
    cout << "{" << root->val << "}" << endl;

    while (!q.empty())
    {
        int levelSize = q.size();// levels的currentLevel数目，为上一层级的结点数
        vector<vector<Tree<int> *>> levels;// 为2维容器，储存着levelSize个currentLevel,即储存了本层级的所有信息。每次while循环都会重置，即遍历到下一层级时自动清空
        vector<Tree<int> *> currentLevel;// 储存本层级中属于同一父节点的一组结点，也就是大括号应括起的一组结点
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
        }// 按规则生成levels
        bool firstGroup = true;// 标志当前level是否是levels中的第一个结点
        int tempCoor = 0; // 临时变量，用于储存上一个level中最后一个结点的坐标值
        for (const auto &level : levels) // 遍历所有level
        {
            if (firstGroup)
                cout << string(level[0]->coor*2, SPACE); // 如果是第一组，正常控制缩进
            else
            {               
                cout << string(max((level[0]->coor - tempCoor -2)*2,0), SPACE); // 实际间隔坐标数为level[0]->coor - tempCoor - 1，减去两个大括号占据的空间，即为输出的空格数的1/2
            }
            cout << "{";
            for (size_t i = 0; i < level.size(); ++i)
            {
                if (i != 0) // i = 0时，即第一个数字时，缩进由前面的if else 语句(line 128~134)控制
                    cout << string((level[i]->coor - level[i - 1]->coor - 1)*2, SPACE);

                cout << level[i]->val<<" "; // 数字后跟一个空格，确保占据2字符

            }
            tempCoor = level[level.size() - 1]->coor; // 储存末坐标，便于后续对其
            cout << "}";
            firstGroup = false; //第一个结点一定已经访问完毕，此标志变量置假
        }
        if (!levels.empty())
        {
            cout << endl;// 如果levels不为空，即本行有输出，则输出一个回车
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
