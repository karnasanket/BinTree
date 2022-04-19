#include "BinTree.h"
using namespace std;

//------------------------- 0 constructor ---------------------------------
// Construction of an empty BinTree
//--------------------------------------------------------------------------
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

        if(current->data != nullptr) // root data
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

BinTree* BinTree::operator=(const BinTree& other) 
{
    if(this == other.root) // if the BinTree being assigned is the same as this
    {
        return *this;
    }

    this->makeEmpty(); // delete the current tree
    assignHelper(this->root, other.root);

    return *this;
}

void BinTree::assignHelper(Node*& lhs, Node* rhs)
{
    if(rhs == nullptr)
    {
        lhs = nullptr;
    }
    else 
    {
        lhs =  new Node();
        NodeData *temp = new NodeData(*rhs->data);
        lhs->data = temp;

        assignHelper(lhs->left, rhs,->left);
        assignHelper(lhs->right, rhs->right);
    }
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