#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
	int key;
	Node *parent;
	std::vector<Node *> children;
	bool leaf;
	unsigned int height;

	Node() {
		this->parent = NULL;
		leaf = true;
	}

	void setParent(Node *theParent) {
		parent = theParent;
		parent->children.push_back(this);
	}
};


int main_with_large_stack_space() {
	std::ios_base::sync_with_stdio(0);
	int n;
	std::cin >> n;

	std::vector<Node> nodes;
	nodes.resize(n);
	int root;
	for (int child_index = 0; child_index < n; child_index++) {
		int parent_index;
		std::cin >> parent_index;
		if (parent_index >= 0) {
			nodes[child_index].setParent(&nodes[parent_index]);
			nodes[parent_index].leaf = false;
		}
		else {
			root = child_index;
		}
		nodes[child_index].key = child_index;
	}

	// Replace this code with a faster implementation
	int maxHeight = 0;
	/*for (int leaf_index = 0; leaf_index < n; leaf_index++) {
		if (nodes[leaf_index].leaf == false) {
			continue;
		}
		int height = 0;
		for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
			height++;
		maxHeight = std::max(maxHeight, height);
	}*/
	std::queue<Node*> q;
	nodes[root].height = 1;
	q.push(&nodes[root]);
	while (!q.empty()) {
		for (Node* c : q.front()->children) {
			c->height = q.front()->height + 1;
			q.push(c);
		}
		if (q.front()->height > maxHeight) {
			maxHeight = q.front()->height;
		}
		q.pop();
	}

	std::cout << maxHeight << std::endl;
	return 0;
}

int main(int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
	// Allow larger stack space
	const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
	struct rlimit rl;
	int result;

	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		if (rl.rlim_cur < kStackSize)
		{
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0)
			{
				std::cerr << "setrlimit returned result = " << result << std::endl;
			}
		}
	}

#endif
	return main_with_large_stack_space();
}
