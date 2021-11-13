#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int key;
	int left;
	int right;

	Node() : key(0), left(-1), right(-1) {}
	Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBSTutil(const vector<Node>& tree, int index, int min, int max) {
	if (index == -1) {
		return true;
	}
	if (tree[index].key < min || tree[index].key > max) {
		return false;
	}
	return IsBSTutil(tree, tree[index].left, min, tree[index].key - 1) && IsBSTutil(tree, tree[index].right, tree[index].key + 1, max);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
	// Implement correct algorithm here
	if (tree.size() == 0)
		return true;
	return IsBSTutil(tree, 0, INT32_MIN, INT32_MAX);
}

int main() {
	int nodes;
	cin >> nodes;
	vector<Node> tree;
	for (int i = 0; i < nodes; ++i) {
		int key, left, right;
		cin >> key >> left >> right;
		tree.push_back(Node(key, left, right));
	}
	if (IsBinarySearchTree(tree)) {
		cout << "CORRECT" << endl;
	}
	else {
		cout << "INCORRECT" << endl;
	}
	return 0;
}
