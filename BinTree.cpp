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
        lhs->left = lhs->right = nullptr; // set the left and right to nullptr
    }
    else if(*data < *lhs->data) // if the value inserted is smaller
    {
        insertion(lhs->left, data); // goes to the left
    }
    else if(*data > *lhs->data) // if the value inserted is bigger
    {
        insertion(lhs->right, data); // goes to the right
    }
    else 
    {
        return false; // if the value has already been inserted, returns back
    }

    return true; // new value has been inserted 
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
    else if(*current->data == currData)
    {
        check = current->data;
    }
    else if(*current->data < currData)
    {
        retrieveHelper(current->right, currData, check);
    }
    else if(*current->data > currData)
    {
        retrieveHelper(current->left, currData, check);
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


