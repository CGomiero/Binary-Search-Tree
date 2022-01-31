#ifndef BINTREE_H_
#define BINTREE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "nodedata.h"
using namespace std;

class BinTree {             // you add class/method comments and assumptions/implementation 
public:
    //construstor
    BinTree();

    //copy constructor: make a deep copy
    BinTree(const BinTree& other);

    //destructor: delete the entire tree
    ~BinTree();                               // calls makeEmpty() 

    //isEmpty: check if the tree is empty
    bool isEmpty() const;

    // makeEmpty: delete all memory, isEmpty() returns true
    void makeEmpty();

    // overloaded operator = : make a deep copy of the other tree
    BinTree& operator=(const BinTree& other);

    // overloaded comparator operators: check if two trees are equal
    bool operator==(const BinTree& other) const;
    bool operator!=(const BinTree& other) const;

    // insert: add a NodeData to the BST, return true if added
    bool insert(NodeData*);

    // retrieve, getSibling, getParent return data from the tree
    bool retrieve(const NodeData&, NodeData*&) const;
    bool getSibling(const NodeData& input, NodeData& sibling) const;
    bool getParent(const NodeData& input, NodeData& parent) const;
    void displaySideways() const;             // displays the tree sideways 

    // Make an array from the BST using the inorder process
    void bstreeToArray(NodeData* []);

    // Create a BST from an array
    void arrayToBSTree(NodeData* []);

    // overloaded input/output operators
    friend ostream& operator <<(ostream& output, const BinTree& tree);  //output the BST using the inorder process
private:
    struct Node {
        NodeData* data;                                   // pointer to data object  
        Node* left;                                      // left subtree pointer  
        Node* right;                                     // right subtree pointer 
    };
    Node* root;                                          // root of the tree 

    // utility functions (recursive functions for the public functions)
    void inorderHelper(Node* current) const;          // recursive helper for operator<< 
    void sidewaysHelper(Node*, int) const;
    void makeEmptyHelper(Node* node);
    void copyHelper(const Node* rhsCurrent, Node*& current);
    bool compareHelper(const Node* current1, const Node* current2) const;
    bool getSiblingsHelper(const NodeData& input, NodeData& sibling, const Node* current) const;
    bool getParentHelper(const NodeData& input, NodeData& parent, const Node* current, bool& flag) const;
    void bstreeToArrayHelper(Node* current, NodeData* [], int& index);
    Node* arrayToBstHelper(NodeData* [], int start, int end);
};
#endif
