#pragma once 
#include <iostream>
#include "nodedata.h"
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
        void sideways(Node*, int)
        void deleteTree(Node*& other);
        void assignHelper(Node* current, Node*& other);
        bool equalityHelper(Node* first, Node* second);
        bool insertion(Node*& current, NodeData* other);
        bool retrieveHelper(Node*& newNode, const NodeData& current, NodeData*& other);
        int getHeightHelper(const NodeData& current, Node* other) const;
        int bstreeToArrayHelper(Node*, NodeData* []);
        
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
        bool retrieve(const NodeData&, NodeData*&) const;
        void displaySideways() const;
        int getHeight(const NodeData&) const;
        void bstreeToArray(NodeData* []);
        void arrayToBSTree(NodeData* []);
    
    friend ostream& operator<<(ostream& out, const BinTree& other);
}