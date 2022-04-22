/*---------------------------------------------------BinTree.H--------------------------------------------------------
Name: Sanket Karna
Class: CSS 343
Created: 04/14/2022
Last Modified: 04/22/2022
----------------------------------------------------------------------------------------------------------------------
This file contains the implementation of the methods and fucntions that are defined in the header class of a BinTree.
It includes the BinTree.h file, and the public method are right above the private helper method for each fucntion for easy
visibility.
The fucntions of BinTree are: To make a tree out of the values read from a file
Being able to delete the tree, make a deep copy of the tree, see if two trees are equal or unequal, find a value in the tree
display the tree normally, and sideways, converts the tree to an Array and make a tree out of the contents in an array
-----------------------------------------------------------------------------------------------------------------------
This class utizes the nodedata class, which conatins the pointers to the data that are stored in each node of the BST
-----------------------------------------------------------------------------------------------------------------------
*/
#include "BinTree.h"
using namespace std;

//------------------------- cout<< overload ---------------------------------
// Displays the tree to the console
//-------------------------------------------------------------------------

ostream& operator<<(ostream& out, const BinTree& other)
{
    other.inorderHelper(other.root);
    out << endl;
    return out;
}
//------------------------- inorderHelper ---------------------------------
// helper method for the cout fucntion that prints the tree with inorder traversal
//-------------------------------------------------------------------------- 

void BinTree::inorderHelper(Node* current) const
{
    if(current == nullptr) // if the tree is empty
    {
        return; // returns back
    }
    else if (root != nullptr) // if the root is not null
    {
        inorderHelper(current->left); // go left first 
        cout << *current->data << " "; // then root
        inorderHelper(current->right); // then right 
    }
}

BinTree::BinTree() 
{
    this->root = nullptr; // initializes empty node
}

//------------------------- copy constructor ---------------------------------
// Creates a deep copy of the object being copied
//--------------------------------------------------------------------------

BinTree::BinTree(const BinTree& other) 
{
    this->root = nullptr; // sets this root to nullptr
    *this = other; // uses the assignment operator to make a deep copy
}

//------------------------- Destructor ---------------------------------
// Calls the makeEmpty funciton to delete a tree and set it to null
//--------------------------------------------------------------------------

BinTree::~BinTree()
{
    this->makeEmpty(); // calls the makeEmpty function
}

//------------------------- isEmpty ---------------------------------
// Checks if the tree is empty or not. returns true or false
//--------------------------------------------------------------------------

bool BinTree::isEmpty() const 
{
    return (this->root == nullptr); // checks if root is null or not
}

//------------------------- makeEmpty ---------------------------------
// Calls the deleteTree method to delete the entire tree
//--------------------------------------------------------------------------

void BinTree::makeEmpty()
{
    deleteTree(root); // calls the deleteTree method
}

//------------------------- deleteTree ---------------------------------
// deletes the current tree paresed in using post-order traversal
//--------------------------------------------------------------------------

void BinTree::deleteTree(Node*& other)
{
    if(other != nullptr) // if the tree isnt already empty
    {
        deleteTree(other->left); // left
        deleteTree(other->right); // right  

        if(other->data != nullptr) // root data
        {
            delete other->data; // delete then set to null
            other->data = nullptr;
        }

        delete other; // actual root
        other = nullptr;
    }
}

//------------------------- Assignment operator ---------------------------------
// sets the right side of the = to the left side 
//--------------------------------------------------------------------------

BinTree& BinTree::operator=(const BinTree& other) 
{
    if(this == &other) // if the BinTree being assigned is the same as this
    {
        return *this;
    }

    this->makeEmpty(); // delete the current tree
    assignHelper(this->root, other.root);

    return *this;
}

//------------------------- assignHelper ---------------------------------
// recursive method to set the rhs to the lhs using pre-order
//--------------------------------------------------------------------------

void BinTree::assignHelper(Node*& lhs, Node* rhs)
{
    if(rhs == nullptr) // if the rhs is null, so is lhs
    {
        lhs = nullptr;
    }
    else 
    {
        lhs =  new Node(); // creates a lhs node
        NodeData *temp = new NodeData(*rhs->data); // creates a new data pointer with the data with the rhs node
        lhs->data = temp; // sets the lhs data 

        assignHelper(lhs->left, rhs->left); // left subtree
        assignHelper(lhs->right, rhs->right); // right subtree
    }
}

//------------------------- operator= ---------------------------------
// Checks if two BinTrees are the same by calling equalHelper method
//--------------------------------------------------------------------------

bool BinTree::operator==(const BinTree& other) const 
{
    if(this->root == nullptr && other.root == nullptr) // checks if both are null
    {
        return true; // true if both are null
    }
    else {
        return equalHelper(this->root, other.root); // if not it calls the helper method 
    }
}

//------------------------- equalHelper ---------------------------------
// Helper method that comapres two BinTree to see if they are the same recursively
//--------------------------------------------------------------------------

bool BinTree::equalHelper(Node* lhs, Node* rhs) const
{
    if (lhs == nullptr && rhs == nullptr) // checks if both are null
    {
        return true; // true if both are null
    }
    else if(lhs == nullptr || rhs == nullptr) // checks if atleast either of them are null
    {
        return false; // false if one of them is null 
    }
    else if((*lhs->data == *rhs->data) && (lhs->left == nullptr && rhs->left == nullptr) && (lhs->right == nullptr && rhs->right == nullptr)) 
    // checks if current data mathces, and the nodes after that (left and right) are null
    {
        return true; // if they are then true
    }

    // otherwise we need to move to the next data, while mainting the truth of the current data
    return ((*lhs->data == *rhs->data) && equalHelper(lhs->left, rhs->left) && equalHelper(lhs->right, rhs->right));
}

//------------------------- operator!= ---------------------------------
// Checks if two BinTrees are different by calling the = method
//--------------------------------------------------------------------------

bool BinTree::operator!= (const BinTree& other) const
{
    return !(*this == other); // returns the value
}

//------------------------- insert ---------------------------------
// inserts a new item into the BinTree object by calling a helper fucntion
//--------------------------------------------------------------------------

bool BinTree::insert(NodeData* data)
{
    return insertion(this->root, data); // calls the insert helper method that is recursive
}

//------------------------- insertion ---------------------------------
// Recursive helper method that insets a new NodeData into the tree 
//--------------------------------------------------------------------------

bool BinTree::insertion(Node*& lhs, NodeData* data)
{
    if(lhs == nullptr) // if there is current node is empty
    {
        lhs = new Node; // dynamically alloacte memory
        lhs->data = data; // add the data 
        lhs->left = nullptr;
        lhs->right = nullptr; // set the left and right to nullptr

        return true;
    }

    if(*data != *lhs->data)
    {
        if(*data < *lhs->data)
        {
            return insertion(lhs->left, data);
        }
        if(*data > *lhs->data)
        {
            return insertion(lhs->right, data);
        }
    }
    return false;    
}
//------------------------- retrieve ---------------------------------
// Checks if the NodeData is in the tree by using a helper function
//--------------------------------------------------------------------------

bool BinTree::retrieve(const NodeData& currData, NodeData*& check) const
{
    Node* temp = root;

    if (temp != nullptr) // if the tree is not empty
    {
        retrieveHelper(temp, currData, check); // calls the helper fucntion
    }
    else
    {
        return false; // if its empty then the data doesnt exist
    }

    if(check != nullptr) // once back from the fucntion, if check is not null, it means the data was found
    {
        assert(*check == currData);
        return true; // reutrn true
    }

    return false; // else false
}

//------------------------- retrieveHelper ---------------------------------
// Helper fucntion that scans the tree to see if a NodeData is in the tree
//--------------------------------------------------------------------------

void BinTree::retrieveHelper(Node* current, const NodeData& currData, NodeData*& check) const
{
    if(current == nullptr) // check for null again
    {
        check = nullptr;

    }
    else if(*current->data == currData) // checks the data of the root 
    {
        check = current->data; // if the data matches, check = root
    }
    else if(*current->data < currData) // if it is bigger 
    {
        retrieveHelper(current->right, currData, check); // check right subtree
    }
    else if(*current->data > currData) // if it is smaller
    {
        retrieveHelper(current->left, currData, check); // check left subtree
    }
}

//------------------------- getHeight ---------------------------------
// Fucntion that returns the height of the inputted node in the tree by using the helper function
//--------------------------------------------------------------------------

int BinTree::getHeight(const NodeData& currNode) const
{
    return getHeightHelper(this->root, currNode); // calls the helper method
}

//------------------------- getHeightHelper ---------------------------------
// This method (is recursive) checks the node to see if the value is in the tree, and when
// found it calls the counter method that counts the height 
//--------------------------------------------------------------------------

int BinTree::getHeightHelper(Node* curr, const NodeData& currNode) const
{
    if(curr == nullptr) // check to see if the tree is empty
    {
        return 0; // if it is height is 0
    }
    else if(*curr->data == currNode) // if the NodeData is found
    {
        return heighCounter(curr); // call the heightCounter method to count the height
    }
    else 
    {
        int leftSubTree = getHeightHelper(curr->left, currNode); // otherwise go left subtree to check
        int rightSubTree = getHeightHelper(curr->right, currNode); // and also right subtree to check

        return max(leftSubTree, rightSubTree); // if they are on both sides, return the higher value
    }

}

//------------------------- heightCounter ---------------------------------
// This recursive method to count the height of the node in the tree, either left or right
// and returns the higher value
//--------------------------------------------------------------------------

int BinTree::heighCounter(Node* current) const
{
    if(current == nullptr) // if the tree is empty
    {
        return 0; // height is 0
    }
    else if(current->left == nullptr && current->right == nullptr) // if the root is the correct and only node
    {
        return 1; // height is 1
    }
    else 
    {
        return 1 + max(heighCounter(current->left), heighCounter(current->right)); // 1 + the amount of time it has to go down left or right, depending on which is bigger
    }
    return 0;
}

//------------------------- bstreeToArray ---------------------------------
// This method calls on a helper function to transfer the contents of a BST to array
//--------------------------------------------------------------------------

void BinTree::bstreeToArray(NodeData* arr[])
{
    bstreeToArrayHelper(this->root, arr); // calls the helper function
    this->makeEmpty(); // clears the BST
}

//------------------------- bstreeToArrayHelper ---------------------------------
// Helper method that transfers the contents of a BST to an array
//--------------------------------------------------------------------------

int BinTree::bstreeToArrayHelper(Node* current, NodeData* arr[]) const
{
    if(current == nullptr) // if the root is empty
    {
        return 0;
    }
    int leftSubTree = bstreeToArrayHelper(current->left, arr); // traverse left to fill the array

    NodeData* temp; // temp NodeData
    temp = current->data; // to store the left most value of the tree
    current->data = nullptr; // set the value to null
    *(arr + leftSubTree) = temp; // set the value of the array to the postion of the node that it is at currently
    temp = nullptr; // set temp to nullptr

    int rightSubTree = bstreeToArrayHelper(current->right, arr + leftSubTree + 1); // traverse right

    return leftSubTree + rightSubTree + 1; // return the postion of the node
}

//------------------------- arrayToBSTree ---------------------------------
// This method calls on a helper function to transfer the contents of a array to BST
//--------------------------------------------------------------------------

void BinTree::arrayToBSTree(NodeData* arr[])
{
    this->makeEmpty(); // clear the current tree

    int len = 0; // length of the array 

    while(arr[len] !=  nullptr) // while the array is not empty
    {
        len++; // get the length
    }

    arrayToBSTreeHelper(arr, 0, len - 1); // call the helper fucntion to fill the BST with arr of size 0 to len-1

}

//------------------------- arrayToBSTreeHelper ---------------------------------
// Helper method that transfers the contents of a array to an BST
//--------------------------------------------------------------------------

void BinTree::arrayToBSTreeHelper(NodeData* arr[], int left, int right)
{
    if(left > right) // if the left index is greater then the right index, then tree is null
    {
        return;
    }
    int middle = (left + right) / 2; // mid the middle index

    NodeData* temp; // temp NodeData
    temp = arr[middle]; // for the middle value of the  array
    arr[middle] = nullptr; // once that is use, set the mid to null

    insert(temp); // insert the middle value into the tree
    arrayToBSTreeHelper(arr, left, middle - 1); // insert the values to the left of the middle
    arrayToBSTreeHelper(arr, middle + 1, right); // insert the value to the right of the middle
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
//---------------------------------------------------------------------------
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}
