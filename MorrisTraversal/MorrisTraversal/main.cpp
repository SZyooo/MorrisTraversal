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
    it is a little tricky to get the post-order from a morris-order, however.
*/

//code
//TreeNode definition
template<typename T>
struct TreeNode {
    TreeNode *left, *right;
    T val;
    TreeNode(TreeNode* l, TreeNode* r, T v)
        :left(l), right(r), val(v) {}
    TreeNode(T v)
        :left(nullptr), right(nullptr), val(v) {}
};


template<typename T>
void morris_traversal(TreeNode<T>* root)
{
    TreeNode<T> *c_node = root;
    while (c_node != nullptr)
    {
        if (c_node->left)
        {
            //right most
            TreeNode<T>* rm = left;
            while (rm->right && rm->right!=c_node)
                rm = rm->right;
            if (rm->right == c_node)
            {
                c_node = c_node->right;
                continue;
            }
            else {
                c_node = c_node->left;
            }
        }
        else
        {
            c = c_node->right;
        }
    }
}

