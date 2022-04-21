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

        void inorderHelper(Node*) const;
        void sideways(Node*, int) const;
        void deleteTree(Node*& other);
        void assignHelper(Node*& current, Node* other);
        bool equalHelper(Node* first, Node* second)  const;
        bool insertion(Node*& current, NodeData* other);
        void retrieveHelper(Node* current, const NodeData& currData, NodeData*& other) const;
        int getHeightHelper(Node* other, const NodeData& current) const;
        int heighCounter(Node* current) const;
        int bstreeToArrayHelper(Node* current, NodeData* arr[]) const;
        void arrayToBSTreeHelper(NodeData* arr[], int left, int right);
        
    public:
        BinTree();	// constructor
        BinTree(const BinTree &); // copy constructor
        ~BinTree();	// destructor, calls makeEmpty	

        bool isEmpty() const; // true if tree is empty, otherwise false
        void makeEmpty(); // make the tree empty so isEmpty returns true

        BinTree& operator=(const BinTree &);
        bool operator==(const BinTree &) const;
        bool operator!=(const BinTree &) const;

        bool insert(NodeData*);
        bool retrieve(const NodeData& currData, NodeData*& check) const;
        void displaySideways() const;
        int getHeight(const NodeData&) const;
        void bstreeToArray(NodeData* arr[]);
        void arrayToBSTree(NodeData* arr[]);
    
    friend ostream& operator<<(ostream& out, const BinTree& other);
};
