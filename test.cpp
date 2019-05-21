/**
 * Author: parask26
 * This code is to test my AVLTree design.
 * 
 * Command guide:
 * 0 denotes insert
 * 1 denotes remove
 * 2 denotes search
 **/

#include "AVLTree.h"
#include <iostream>

using namespace std;

int main(void) {
	AVLTree<int> tree;
	int command, num;
	while (cin >> command) {
		if (command == 0) {
			cin >> num;
			tree.insert(num);
		} else if (command == 1) {
			cin >> num;
			tree.remove(num);
		} else if (command == 2) {
			cin >> num;
			if (tree.contains(num)) {
				cout << "Found" << endl;
			} else {
				cout << "Not Found" << endl;
			}
		} else {
			cout << "Invalid command. 0 for insert, 1 for remove" << endl;
		}
		tree.printTree();
	}
	return 0;
}
