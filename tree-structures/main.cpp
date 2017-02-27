#include "binary_tree.h"

int main() {
	structures::BinaryTree<int> bt;
	bt.insert(5);
	bt.insert(2);
	bt.insert(3);
	bt.insert(8);
	bt.insert(7);
	bt.print();
}
