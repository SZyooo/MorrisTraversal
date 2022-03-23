#include<memory>
#include<iostream>
/*
Morris traversal is a better way to traverse a binary tree than traditional methods.
Its time cost has the same upper bound which is O(n) while it only costs constant space.
The key point to do a morris traversal is that set the left-subtree's right most node's
right child pointer to be current node.
for example:
     1
    / \
   /   \
  2     3
 / \   / \
4   5 6   7
   / 
  8  
for the tree above, for node 1, its left-subtree's right most node is 5;
for node 2, its left-subtree's right most node is 4. 
So, we should temporarily set the 4' right child to be node 2, the 5's right child to be
node 1, and so on.

so, as a result, the steps to traverse a tree is depicted below:

for the node we currently reach, denoted as cnode,
step 0:
    if cnode = null, the traversal is over.
    else move on to next step.
step 1:
    find its left subtree's right most node:
        if succeeds,denoted it as rnode;
        if fails 
            move on to its right node (cnode = cnode->rChild)
            jump to step 0.                
step 2:
    find out whether rnode's right child is cnode:
        YES: 
            set rnode's right child to be null;
            move on to the cnode's right child.
            jump to step 0;
        
        NO: set rnode's right child to be cnode
step 3:
    move on to the cnode's left child;
    jump to step 0.

the result of this operation is that except the right most node of the whole tree,each
other node will have right child during the traversal.
besides, we can find another characteristic of this kind of tree:
    for the nodes originally have left node, it will be scanned twice because we can go
        back to them through their left-subtrees' right most nodes.
    for the nodes have no left child, it will be only scanned once.

for the sample tree above, the morris-order of it is 
1,2,4,2,5,8,5,1,3,6,3,7
pre-order :
    it is quite easy to figure out how to get the pre-order from a morris-order:
    we pick up the nodes when they first appear: 1,2,4,5,8,3,6,7
in-order:
    it is not difficult to obtain the inorder from a morris-order:
    we pick up the nodes those can appear twice (which means they have left child)
        in their second time being scanned, while in the first time being scanned 
        for those nodes can only appear once in the morris-order (indicates that 
        they have no left child)
post-order:
    it is a little tricky to get the post-order from a morris-order, however. The
    key point is to process the node only when we meet it twice. At the second time 
    we meet a node, we process the right edge of its left subtree in reverse order.
    for instance, for the tree above
    its morris-order is: 1,2,4,2,5,8,5,1,3,6,3,7
    the process is like this:
        we scan the morris order, the first node we meet twice is 2, so at the second
        time we, we process(e.g., print) its right edge of its left subtree:
            
            4
        
        then ,the second this kind of node is 5, let's do the same thing to it:
            
            8
        
        for the node 1' second time being scanned:
            
            5,2  (the reverse order of its right edge ot its left subtree)
        
        for the node 3' second time being scanned:
            
            6

        OK, we have printed all the nodes in some subtree's left right edge. After 
        doing this, the final step is to print the right edge of the tree as a whole,
        in reverse roder as well:
        
            7,3,1
        then ,the whole print is:
        4,8,5,2,6,7,3,1
        and it is the post-order of the tree.
*/

//code
//TreeNode definition
class TreeNode {
public:
    std::shared_ptr<TreeNode> Left() { return _left; }
    std::shared_ptr<TreeNode> Right()  { return _right; }
    void setRight(std::shared_ptr<TreeNode> right)
    {
        _right = right;
    }
    void setLeft(std::shared_ptr<TreeNode> left)
    {
        _left = left;
    }
    int Value() const { return _val; }
    TreeNode(std::shared_ptr<TreeNode> left, std::shared_ptr<TreeNode> right, int val)
        :_left(left),_right(right),_val(val)
    {}
    TreeNode(int val)
        :_left(nullptr), _right(nullptr), _val(val) {}
private:
    std::shared_ptr<TreeNode> _left;
    std::shared_ptr<TreeNode> _right;
    int _val;
};


void MorrisTraversal(std::shared_ptr<TreeNode> root)
{
    std::shared_ptr<TreeNode> curNode = root;
    while (curNode)
    {
        std::cout << curNode->Value();
        if (curNode->Left())
        {
            std::shared_ptr<TreeNode> left = curNode->Left();
            while (left->Right() && left->Right() != curNode)
            {
                left = left->Right();
            }
            if (left->Right() == curNode)
            {
                left->setRight(nullptr);
                curNode = curNode->Right();
            }
            else
            {
                left->setRight(curNode);
                curNode = curNode->Left();
            }
        }
        else
            curNode = curNode->Right();
    }
}


void MorrisTraversalPreorder(std::shared_ptr<TreeNode> root)
{
    std::shared_ptr<TreeNode> curNode = root;
    while (curNode)
    {
        if (curNode->Left())
        {
            std::shared_ptr<TreeNode> left = curNode->Left();
            while (left->Right() && left->Right() != curNode)
            {
                left = left->Right();
            }
            if (left->Right() == curNode)
            {
                left->setRight(nullptr);
                curNode = curNode->Right();
            }
            else
            {
                std::cout << curNode->Value();
                left->setRight(curNode);
                curNode = curNode->Left();
            }
        }
        else
        {
            std::cout << curNode->Value();
            curNode = curNode->Right();
        }
    }
}

void MorrisTraversalInorder(std::shared_ptr<TreeNode> root)
{
    std::shared_ptr<TreeNode> curNode = root;
    while (curNode)
    {
        if (curNode->Left())
        {
            std::shared_ptr<TreeNode> left = curNode->Left();
            while (left->Right() && left->Right() != curNode)
            {
                left = left->Right();
            }
            if (left->Right() == curNode)
            {
                left->setRight(nullptr);
                std::cout << curNode->Value();
                curNode = curNode->Right();
            }
            else
            {
                left->setRight(curNode);
                curNode = curNode->Left();
            }
        }
        else
        {
            std::cout << curNode->Value();
            curNode = curNode->Right();
        }
    }
}


void inverseScan(std::shared_ptr<TreeNode> node)
{
    std::shared_ptr<TreeNode> cur = node;
    std::shared_ptr<TreeNode> next = node->Right();
    while (next)
    {
        std::shared_ptr<TreeNode> tmp = next;
        next = next->Right();
        tmp->setRight(cur);
        cur = tmp;
    }
    while (cur != node)
    {
        std::cout << cur->Value();
        std::shared_ptr<TreeNode> pre = cur->Right();
        cur->setRight(next);
        next = cur;
        cur = pre;
    }
    std::cout << cur->Value();
}

void MorrisTraversalPostorder(std::shared_ptr<TreeNode> root)
{
    std::shared_ptr<TreeNode> curNode = root;
    while (curNode)
    {
        if (curNode->Left())
        {
            std::shared_ptr<TreeNode> left = curNode->Left();
            while (left->Right() && left->Right() != curNode)
            {
                left = left->Right();
            }
            if (left->Right() == curNode)
            {
                left->setRight(nullptr);
                inverseScan(curNode->Left());
                curNode = curNode->Right();
            }
            else
            {
                left->setRight(curNode);
                curNode = curNode->Left();
            }
        }
        else
            curNode = curNode->Right();
    }
    inverseScan(root);
}



/*
     1
    / \
   /   \
  2     3
 / \   / \
4   5 6   7
   / 
  8  

*/
int main()
{
    //build the tree shown above
    std::shared_ptr<TreeNode> eight(new TreeNode(8));
    std::shared_ptr<TreeNode> five(new TreeNode(eight, nullptr, 5));
    std::shared_ptr<TreeNode> four(new TreeNode(4));
    std::shared_ptr<TreeNode> two(new TreeNode(four, five, 2));
    std::shared_ptr<TreeNode> six(new TreeNode(6));
    std::shared_ptr<TreeNode> seven(new TreeNode(7));
    std::shared_ptr<TreeNode> three(new TreeNode(six,seven,3));
    std::shared_ptr<TreeNode> one(new TreeNode(two, three, 1));
    //print the morris order
    //MorrisTraversal(one);
    //print the preorder
    //MorrisTraversalPreorder(one);
    //print middle order
    //MorrisTraversalInorder(one);
    //MorrisTraversalPostorder(one);
}


