/*---------------------------------------------------BinTree.H--------------------------------------------------------
Name: Sanket Karna
Class: CSS 343
Created: 04/14/2022
Last Modified: 04/22/2022
----------------------------------------------------------------------------------------------------------------------
This file contains the header class of a BinTree. The class contains the method and fucntion definitions of a BinTree
Alongside that, there is also a stuct Node, that is there for the pointers to the left and the right child of a BinTree
The fucntions of BinTree are: To make a tree out of the values read from a file
Being able to delete the tree, make a deep copy of the tree, see if two trees are equal or unequal, find a value in the tree
display the tree normally, and sideways, converts the tree to an Array and make a tree out of the contents in an array
-----------------------------------------------------------------------------------------------------------------------
This class utizes the nodedata class, which conatins the pointers to the data that are stored in each node of the BST
-----------------------------------------------------------------------------------------------------------------------
*/

#pragma once 
#include <iostream>
#include "nodedata.h"
#include <cassert>
using namespace std;

class BinTree 
{
    private:
        struct Node 
        {
            NodeData* data;	// pointer to data object
            Node* left;	// left subtree pointer
            Node* right; // right subtree pointer
	    };
	    Node* root;	// root of the tree

        void inorderHelper(Node*) const; // cout<< overload helper
        void sideways(Node*, int) const; // display sideways helper
        void deleteTree(Node*& other); // destructor/make empty helper
        void assignHelper(Node*& current, Node* other); // assignment operator helper
        bool equalHelper(Node* first, Node* second)  const; // equality/inequality helper
        bool insertion(Node*& current, NodeData* other); // insert helper
        void retrieveHelper(Node* current, const NodeData& currData, NodeData*& other) const; // retrive helper
        int getHeightHelper(Node* other, const NodeData& current) const; // get height helper
        int heighCounter(Node* current) const; // get height helper's helper
        int bstreeToArrayHelper(Node* current, NodeData* arr[]) const; // tree to array helper
        void arrayToBSTreeHelper(NodeData* arr[], int left, int right); // array to tree helper
        
    public:
        BinTree();	// constructor
        BinTree(const BinTree &); // copy constructor
        ~BinTree();	// destructor, calls makeEmpty	

        bool isEmpty() const; // true if tree is empty, otherwise false
        void makeEmpty(); // make the tree empty so isEmpty returns true

        BinTree& operator=(const BinTree &); // assignment operator
        bool operator==(const BinTree &) const; // equality operator
        bool operator!=(const BinTree &) const; // inequality operator

        bool insert(NodeData*); // insert method
        bool retrieve(const NodeData& currData, NodeData*& check) const; // to retieve an item method
        void displaySideways() const; // dispplay sideways method 
        int getHeight(const NodeData&) const; // get height of the tree method
        void bstreeToArray(NodeData* arr[]); // convert tree to array method
        void arrayToBSTree(NodeData* arr[]); // converts array to tree method
    
    friend ostream& operator<<(ostream& out, const BinTree& other); // operator overload for cout<<
};
