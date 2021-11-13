#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class TreeOrders {
	int n;
	vector <int> key;
	vector <int> left;
	vector <int> right;

public:
	void read() {
		cin >> n;
		key.resize(n);
		left.resize(n);
		right.resize(n);
		for (int i = 0; i < n; i++) {
			cin >> key[i] >> left[i] >> right[i];
		}
	}


	void in_order(int index, vector<int>& result) {
		//vector<int> result;
		// Finish the implementation
		// You may need to add a new recursive method to do that
		if (left[index] != -1) {
			/*vector<int> result_left;
			in_order(left[index], result_left);
			for (int i = 0; i < result_left.size(); ++i) {
				result.push_back(result_left[i]);
			}
			result.push_back(key[index]);*/
			in_order(left[index], result);
		}

		result.push_back(key[index]);

		if (right[index] != -1) {
			/*vector<int> result_right;
			in_order(right[index], result_right);
			for (int i = 0; i < result_right.size(); ++i) {
				result.push_back(result_right[i]);
			}*/
			in_order(right[index], result);
		}
		//return result;
	}

	void pre_order(int index, vector<int>& result) {
		//vector<int> result;
		// Finish the implementation
		// You may need to add a new recursive method to do that
		result.push_back(key[index]);
		if (left[index] != -1) {
			/*vector<int> result_left;
			pre_order(left[index], result_left);
			for (int i = 0; i < result_left.size(); ++i) {
				result.push_back(result_left[i]);
			}*/
			pre_order(left[index], result);
		}
		if (right[index] != -1) {
			/*vector<int> result_right;
			pre_order(right[index], result_right);
			for (int i = 0; i < result_right.size(); ++i) {
				result.push_back(result_right[i]);
			}*/
			pre_order(right[index], result);
		}
		//return result;
	}

	void post_order(int index, vector<int>& result) {
		//vector<int> result;
		// Finish the implementation
		// You may need to add a new recursive method to do that
		if (left[index] != -1) {
			/*vector<int> result_left;
			post_order(left[index], result_left);
			for (int i = 0; i < result_left.size(); ++i) {
				result.push_back(result_left[i]);
			}*/
			post_order(left[index], result);
		}
		if (right[index] != -1) {
			/*vector<int> result_right;
			post_order(right[index], result_right);
			for (int i = 0; i < result_right.size(); ++i) {
				result.push_back(result_right[i]);
			}*/
			post_order(right[index], result);
		}
		result.push_back(key[index]);
		//return result;
	}
};

void print(vector <int> a) {
	for (size_t i = 0; i < a.size(); i++) {
		if (i > 0) {
			cout << ' ';
		}
		cout << a[i];
	}
	cout << '\n';
}

int main_with_large_stack_space() {
	ios_base::sync_with_stdio(0);
	TreeOrders t;
	t.read();
	
	vector<int> result_in;
	t.in_order(0, result_in);
	print(result_in);

	vector<int> result_pre;
	t.pre_order(0, result_pre);
	print(result_pre);
	
	vector<int> result_post;
	t.post_order(0, result_post);
	print(result_post);
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

