
/*  BST312.h
  CS 312 Fall 2018

  a simple implementation of a binary search tree

  Name: Rithvik Baddam
  UT eid: rrb2442
*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode * root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);
    bool isItemInTree(TreeNode* t, const ItemType& newItem);
};

/*******************************
//Function implementations
********************************/

template<class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}

template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)
{
    copyTree(root, src.root);
}

template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty();

}


template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}


template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}



//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{
    while (t->right != NULL)
        t = t->right;

    data = t->data;
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
    if(t == NULL)
        return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL;
}



template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}


template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL){  // insert item if no node exists here
    	TreeNode *newNode = new TreeNode;
    	newNode->data = newItem;
    	newNode->left = NULL;
    	newNode->right = NULL;
    	t = newNode;
//cout << newItem;
    	return;
    }
    else if (newItem < t->data){
    	if (t->left == NULL){  // insert item if no node exists here and the parent is greater than item
    		TreeNode *newNode = new TreeNode;
    		newNode->data = newItem;
    		newNode->left = NULL;
    		newNode->right = NULL;
    		t->left = newNode;
//cout << newItem;
    		return;
    	}
        insertItem(t->left, newItem);
    }
    else if (newItem > t->data){
    	if (t->right == NULL){  // insert item if no node exists here and the parent is less than item
    		TreeNode *newNode = new TreeNode;
    		newNode->data = newItem;
    		newNode->left = NULL;
    		newNode->right = NULL;
    		t->right = newNode;
//cout << newItem;
    		return;
    	}
        insertItem(t->right, newItem);
    }
}

template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    insertItem(root, newItem);
}



template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    int numNodes = 0;
    if(t != NULL)
        numNodes++; // increment if node exists
    else
        return 0;
    numNodes += countNodes(t->left); // count all left subtrees
    numNodes += countNodes(t->right); // count all right subtrees

    return numNodes;
}


template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    int numNodes = countNodes(root);
    return numNodes;
}

template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    // node, left, right
    if(t != NULL){
        result.push_back(t->data);
    }
    else
        return;
    preOrderTraversal(t->left, result);
    preOrderTraversal(t->right, result);
}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    vector<ItemType> preOrderList;
    preOrderTraversal(root, preOrderList);
    return preOrderList;

}

template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    // left, node, right
    if(t->left != NULL)
        inOrderTraversal(t->left, result);

    result.push_back(t->data);

    if(t->right != NULL)
        inOrderTraversal(t->right, result);

}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    vector<ItemType> inOrderList;
    inOrderTraversal(root, inOrderList);
    return inOrderList;
}

template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if(t == NULL)
        return;
    // Left, right, node
    postOrderTraversal(t->left, result);
    postOrderTraversal(t->right, result);
    result.push_back(t->data);
}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    vector<ItemType> postOrderList;
    postOrderTraversal(root, postOrderList);
    return postOrderList;
}

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{
    return isItemInTree(root, item);
}

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(TreeNode* t, const ItemType& newItem){
    if(t == NULL)  // node does not exist if it is null
        return false;

    else if(newItem < t->data)
        return isItemInTree(t->left, newItem);  // check left subtree if item less than node item

    else if(newItem > t->data)
        return isItemInTree(t->right, newItem); // check right subtree if item greater than node item

    else
        return true;  // if a node exists such that it isn't smaller or greater than item, tree contains item
}

#endif

