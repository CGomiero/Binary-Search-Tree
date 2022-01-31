
// presumably bintree.h includes nodedata.h so the include is not needed here
	#include "bintree.h"
	#include <fstream>
	#include <iostream>
	using namespace std;
	
	const int ARRAYSIZE = 100;
	
	//global function prototypes
	void buildTree(BinTree&, ifstream&); // build the tree using given data file
	void initArray(NodeData* []);        // initialize an array elements to nullptr
	
	int main() {
	    // create file object infile and open it
	    // for testing, call your data file something appropriate, e.g., data2.txt
	    ifstream infile("data2.txt");
	    if (!infile) {
	        cout << "File could not be opened." << endl;
	        return 1;
	    }
	
	    // the NodeData class must have a constructor that takes a string
	    NodeData notND("not");
	    NodeData andND("and");
	    NodeData sssND("sss");
	    NodeData eND("e");
	    NodeData mND("m");
	    NodeData tND("t");
	
	    BinTree T, T2, dup;
	    NodeData* ndArray[ARRAYSIZE];
	    initArray(ndArray);
	    cout << "Initial data:" << endl << "  ";
	    buildTree(T, infile);              // builds and displays initial data
	    cout << endl;
	    BinTree first(T);                  // test copy constructor
	    dup = dup = T;                     // test operator=, self-assignment
	    while (!infile.eof()) {
	        cout << "Tree Inorder:" << endl << T;             // operator<< does endl
	        T.displaySideways();
	
	        // test retrieve 
	        NodeData* p;                    // pointer of retrieved object
	        bool found;                     // whether or not object was found in tree
	        found = T.retrieve(andND, p);
	        cout << "Retrieve --> and:  " << (found ? "found" : "not found") << endl;
	        found = T.retrieve(notND, p);
	        cout << "Retrieve --> not:  " << (found ? "found" : "not found") << endl;
	        found = T.retrieve(sssND, p);
	        cout << "Retrieve --> sss:  " << (found ? "found" : "not found") << endl;
	
	        // test getSibling and getParent
	        NodeData nd;                    // copy of either sibling or parent
	        NodeData notFound("notFound");
	        bool success;                   // whether or not sibling/parent exists
	        success = T.getSibling(andND, nd);
	        cout << "Sibling of and:  " << (success ? nd : notFound) << endl;
	        success = T.getSibling(notND, nd);
	        cout << "Sibling of not:  " << (success ? nd : notFound) << endl;
	        success = T.getSibling(sssND, nd);
	        cout << "Sibling of sss:  " << (success ? nd : notFound) << endl;
	
	        success = T.getParent(andND, nd);
	        cout << "Parent of and:  " << (success ? nd : notFound) << endl;
	        success = T.getParent(notND, nd);
	        cout << "Parent of not:  " << (success ? nd : notFound) << endl;
	        success = T.getParent(sssND, nd);
	        cout << "Parent of sss:  " << (success ? nd : notFound) << endl;
	
	        // test ==, and != 
	        T2 = T;
	        cout << "T == T2?     " << (T == T2 ? "equal" : "not equal") << endl;
	        cout << "T != first?  " << (T != first ? "not equal" : "equal") << endl;
	        cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;
	
	        dup = T;
	        // somewhat test bstreeToArray and arrayToBSTree
	        T.bstreeToArray(ndArray);
	        T.arrayToBSTree(ndArray);
	        T.displaySideways();
	
	        cout << "---------------------------------------------------------------"
	            << endl;
	        cout << "Initial data:" << endl << "  ";
	
	        initArray(ndArray);        // empty out the array to start fresh
	        T.makeEmpty();             // empty out the tree so another can be built
	        buildTree(T, infile);
	        cout << endl;
	    }
	
	    return 0;
	}
	
	/*----------------------------------------------------------------------------
	 buildTree*/
	
	/* To build a tree, read strings from a line, terminating with "$$" .
	 Since there is some work to do before the actual insert that is specific to 
	 the client problem (tree class does not know about the data that it holds), 
	 building a tree is not a member function.  It's a global function. */
	
	void buildTree(BinTree& t, ifstream& infile) {
	    string s;
	
	    for (;;) {
	        infile >> s;
	        cout << s << ' ';
	        if (s == "$$") {                      // at end of one line
	            break;
	        }
	
	        // no more lines of data, must attempt to read the line so the
	        // end-of-file character is read, triggering eof() to be true
	        if (infile.eof()) {
	            break;
	        }
	
	        // in an object-oriented program, change to setData() for reading 
	        NodeData* ptr = new NodeData(s);
	        bool success = t.insert(ptr);
	        if (!success) {
	            delete ptr;                       // duplicate case, not inserted 
	            ptr = nullptr;
	        }
	    }
	}
	
	//----------------------------------------------------------------------------
	 //initArray 
	 //initialize the array of NodeData* to hold nullptr 
	
	void initArray(NodeData* ndArray[]) {
	    for (int i = 0; i < ARRAYSIZE; i++) {
	        ndArray[i] = nullptr;
	    }
	}
