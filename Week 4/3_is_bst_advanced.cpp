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
	if (tree[index].key <= min || tree[index].key > max) {
		return false;
	}
	return IsBSTutil(tree, tree[index].left, min, tree[index].key - 1) && IsBSTutil(tree, tree[index].right, tree[index].key, max);
}

bool in_order(const vector<Node>& tree, int index, int& prev_value) {
	if (tree[index].left != -1) {
		if (in_order(tree, tree[index].left, prev_value) == false) {
			return false;
		}
		prev_value++;
	}
	if (tree[index].key < prev_value) {
		return false;
	}
	prev_value = tree[index].key;
	if (tree[index].right != -1) {
		if (in_order(tree, tree[index].right, prev_value) == false) {
			return false;
		}
	}
	return true;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
	// Implement correct algorithm here
	if (tree.size() == 0)
		return true;
	//return IsBSTutil(tree, 0, 2147483648, 2147483647);
	int prev_value = INT32_MIN;
	return in_order(tree, 0, prev_value);
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
