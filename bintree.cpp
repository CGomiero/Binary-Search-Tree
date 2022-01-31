#include "bintree.h"

//----------------------------------------------------
// Constructor: set root to null
BinTree::BinTree() : root(nullptr)
{
}

//----------------------------------------------------
// Copy Constructor: Make a deep copy of another BinTree
BinTree::BinTree(const BinTree& other)
{
	copyHelper(other.root, root);
}

//----------------------------------------------------
// Destructor: Delete the tree for no memory leaks
BinTree::~BinTree()
{
	makeEmpty();
}

//----------------------------------------------------
// isEmpty: check if the tree is root
// return if root is nullptr
bool BinTree::isEmpty() const
{
	return root == nullptr;
}

//----------------------------------------------------
// makeEmpty: Delete every node in the tree and
// set root to null
void BinTree::makeEmpty()
{
	makeEmptyHelper(root);
	root = nullptr;
}

void BinTree::makeEmptyHelper(Node* node)
{
	if (node == nullptr) {
		return;
	}
	else {
		makeEmptyHelper(node->left);
		makeEmptyHelper(node->right);

		delete node->data;
		node->data = nullptr;
		delete node;
		node = nullptr;
	}
}

//----------------------------------------------------
// overload operator =: make a deep copy of a BinTree object
BinTree& BinTree::operator=(const BinTree& other)
{
	if (this == &other) {
		return *this;
	}
	makeEmpty(); // delete any node left in the tree

	copyHelper(other.root, root);	//copy tree
	return *this;
}

void BinTree::copyHelper(const Node* rhsCurrent, Node*& current) {
	if (rhsCurrent == nullptr) {
		current = nullptr;
	}
	else {//copy every current node to the rhs node
		current = new Node();
		current->data = new NodeData(*rhsCurrent->data);

		copyHelper(rhsCurrent->left, current->left);
		copyHelper(rhsCurrent->right, current->right);
	}
}

//----------------------------------------------------
// overload operator ==: check if two BinTree is equal 
// by checking every node return true if equal
bool BinTree::operator==(const BinTree& other) const
{
	//check if any or both trees are empty
	if (this->isEmpty() && !other.isEmpty()) {
		return false;
	}
	else if (!this->isEmpty() && other.isEmpty()) {
		return false;
	}
	else if (isEmpty() && other.isEmpty()) {
		return true;
	}

	Node* current = root;
	Node* otherCurrent = other.root;
	return compareHelper(current, otherCurrent);
}

//----------------------------------------------------
// compareHelper: recursively compare every node and if there are equal then return true
bool BinTree::compareHelper(const Node* current1, const Node* current2) const
{
	//check current1 and current are equal or not
	if (current1 == nullptr && current2 != nullptr) {
		return false;
	}
	if (current1 != nullptr && current2 == nullptr) {
		return false;
	}
	if (current1 == nullptr && current2 == nullptr) {
		return true;
	}
	
	// compare both tree
	return (*current1->data == *current2->data && compareHelper(current1->left,
		current2->left) && compareHelper(current1->right, current2->right));
}

//----------------------------------------------------
// overload operator !=: compare two BinTree using == 
// and return false if equal
bool BinTree::operator!=(const BinTree& other) const
{
	return !(*this == other);
}

//----------------------------------------------------
// insert: add an object to the tree by iteratively 
// finding the right spot in the tree and adding it
// return true if the object was added
bool BinTree::insert(NodeData* val)
{
	NodeData* value = val;
	Node* insertNode = new Node();	//create new node to add
	insertNode->data = value;
	if (root == nullptr) { // insert root
		root = insertNode;
		return true;
	}

	Node* current = root;
	Node* previous = nullptr;

	while (current != nullptr) {		//find the correct place to insert
		previous = current;
		if (*insertNode->data < *current->data) {
			current = current->left;
		}
		else if (*insertNode->data > *current->data) {
			current = current->right;
		}
		
		//duplicates are not allowed
		else if (*insertNode->data == *current->data) { 
			delete insertNode;
			insertNode = nullptr;
			return false;
		}
	}

	//insert the data
	if (*insertNode->data < *previous->data) {
		previous->left = insertNode;
		return true;
	}
	if (*insertNode->data > *previous->data) {
		previous->right = insertNode;
		return true;
	}
	return false;
}

//----------------------------------------------------
// retrieve: return the data from the tree using *&
// return true if the value was find
bool BinTree::retrieve(const NodeData& val, NodeData*& returnVal) const
{
	if (isEmpty()) {
		return false;
	}

	Node* current = root;

	while (current != nullptr) {		//go over the tree to find data
		if (*current->data == val) {
			returnVal = current->data;
			return true;
		}
		if (*current->data > val) {
			current = current->left;
		}
		else if (*current->data < val) {
			current = current->right;
		}
	}
	return false;
}

//----------------------------------------------------
// getSibling: get the sibling of a node by 
// recursively going over the tree return true if the 
// value is found and return the value via sibling
bool BinTree::getSibling(const NodeData& input, NodeData& sibling) const
{
	if (input == *root->data || isEmpty()) {
		return false;
	}
	return getSiblingsHelper(input, sibling, root);
}

bool BinTree::getSiblingsHelper(const NodeData& input, NodeData& sibling, const Node* current) const
{
	if (current == nullptr) {
		return false;
	}
	if (current->right == nullptr && current->left == nullptr) { //no siblings
		return false;
	}

	if (current->right != nullptr && *current->right->data == input) { // right has the value
		if (current->left == nullptr) {			// check if left has a value
			return false;
		}
		else {
			sibling = *current->left->data;
			return true;
		}
	}

	if (current->left != nullptr && *current->left->data == input) { //left has the value
		if (current->right == nullptr) {		//check if right has a value
			return false;
		}
		else {
			sibling = *current->right->data;
			return true;
		}
	}

	bool flag = false;
	flag = getSiblingsHelper(input, sibling, current->left);

	//dont check right node if the value is found
	if (flag != true) {						
		flag = getSiblingsHelper(input, sibling, current->right);
	}
	return flag;
}

//----------------------------------------------------
// getParent: get the parent of a node by recursively 
// going over the tree return true if the value is 
// found and return the value via the parent variable
bool BinTree::getParent(const NodeData& input, NodeData& parent) const
{
	if (root == nullptr || *root->data == input) {
		return false;
	}

	bool val = false;
	return getParentHelper(input, parent, root, val);
}

bool BinTree::getParentHelper(const NodeData& input, NodeData& parent, const Node* current, bool& flag) const
{
	if (flag != true) {
		// check for the node after the current 
		// if the value is found then return the current value
		if (current->right == nullptr && current->left == nullptr) {
			return false;
		}
		if (current->right != nullptr && *current->right->data == input) {
			parent = *current->data;
			return true;
		}
		if (current->left != nullptr && *current->left->data == input) {
			parent = *current->data;
			return true;
		}

		// go over the tree to find the input node
		if (current->right != nullptr) {
			flag = getParentHelper(input, parent, current->right, flag);
		}
		if (current->left != nullptr) {
			flag = getParentHelper(input, parent, current->left, flag);
		}
	}
	return flag;
}

//----------------------------------------------------
// deplaySideWays: display a binary tree side way
void BinTree::displaySideways() const
{
	sidewaysHelper(root, 0);
}

//----------------------------------------------------
// bstreeToArray: create an array from a bst
// use the inorder process to add in the array
// Leave the tree empty
void BinTree::bstreeToArray(NodeData* arr[]) {
	int index = 0;
	bstreeToArrayHelper(root, arr, index);
	makeEmpty();
}

void BinTree::bstreeToArrayHelper(Node* current, NodeData* arr[], int& index)
{
	if (current == nullptr) {
		return;
	}

	bstreeToArrayHelper(current->left, arr, index);
	arr[index++] = current->data;
	bstreeToArrayHelper(current->right, arr, index);

	current->data = nullptr;
}

//----------------------------------------------------
// arrayToBSTree: create an bst from an array. 
// Get the size of the array by using a while loop
// add array[mid] until the start is bigger than the end
void BinTree::arrayToBSTree(NodeData* arr[])
{
	if (!isEmpty()) {
		makeEmpty();
	}

	// get size of array
	int size = 0;
	while (arr[size] != nullptr) {
		size++;
	}
	root = arrayToBstHelper(arr, 0, size - 1);
}

BinTree::Node* BinTree::arrayToBstHelper(NodeData* arr[], int start, int end)
{
	if (start > end) { //base case
		return nullptr;
	}

	// get mid and set the root value to arr[mid]
	int mid = (start + end) / 2;
	Node* tempRoot = new Node();
	tempRoot->data = arr[mid];
	arr[mid] = nullptr;

	tempRoot->left = arrayToBstHelper(arr, start, mid - 1);
	tempRoot->right = arrayToBstHelper(arr, mid + 1, end);

	return tempRoot;
}

//----------------------------------------------------
// sidewaysHelper: output the data side ways 
void BinTree::sidewaysHelper(Node* current, int level) const
{
	if (current != nullptr) {
		level++;
		sidewaysHelper(current->right, level);

		// indent for readability, same number of spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "        ";
		}

		cout << *current->data << endl;        // display information of object
		sidewaysHelper(current->left, level);
	}
}

//----------------------------------------------------
// overload operator <<: output the tree inorder
ostream& operator<<(ostream& output, const BinTree& tree)
{
	tree.inorderHelper(tree.root);
	output << endl;

	return output;
}

//----------------------------------------------------
// inorderHelper: output the data inorder
void BinTree::inorderHelper(Node* current) const
{
	if (current == nullptr) {
		return;
	}

	inorderHelper(current->left);
	cout << *current->data << " ";
	inorderHelper(current->right);
}