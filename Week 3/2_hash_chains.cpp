#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

struct Query {
	string type, s;
	size_t ind;
};

class QueryProcessor {
	int bucket_count;
	// store all strings in one vector
	vector<string> elems;
	size_t hash_func(const string& s) const {
		static const size_t multiplier = 263;
		static const size_t prime = 1000000007;
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
			hash = (hash * multiplier + s[i]) % prime;
		return hash % bucket_count;
	}

public:
	explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {}

	Query readQuery() const {
		Query query;
		cin >> query.type;
		if (query.type != "check")
			cin >> query.s;
		else
			cin >> query.ind;
		return query;
	}

	void writeSearchResult(bool was_found) const {
		std::cout << (was_found ? "yes\n" : "no\n");
	}

	void processQuery(const Query& query) {
		if (query.type == "check") {
			// use reverse order, because we append strings to the end
			for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
				if (hash_func(elems[i]) == query.ind)
					std::cout << elems[i] << " ";
			std::cout << "\n";
		}
		else {
			vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
			if (query.type == "find")
				writeSearchResult(it != elems.end());
			else if (query.type == "add") {
				if (it == elems.end())
					elems.push_back(query.s);
			}
			else if (query.type == "del") {
				if (it != elems.end())
					elems.erase(it);
			}
		}
	}

	void processQueries() {
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
			processQuery(readQuery());
	}
};

unsigned int hash_func(const string& s, unsigned int m) {
	static const size_t multiplier = 263;
	static const size_t prime = 1000000007;
	unsigned long long hash = 0;
	for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
		hash = (hash * multiplier + s[i]) % prime;
	return hash % m;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	unsigned int m;
	cin >> m;
	unsigned int n;
	cin >> n;
	vector<list<string>> elements(m);
	string type, s;
	unsigned int ind;
	for (unsigned int i = 0; i < n; ++i) {
		cin >> type;
		if (type == "add") {
			cin >> s;
			unsigned int index = hash_func(s, m);
			if (find(elements[index].begin(), elements[index].end(), s) == elements[index].end()) {
				elements[index].push_front(s);
			}
		}
		else if (type == "del") {
			cin >> s;
			unsigned int index = hash_func(s, m);
			elements[index].remove(s);
		}
		else if (type == "find") {
			cin >> s;
			unsigned int index = hash_func(s, m);
			if (find(elements[index].begin(), elements[index].end(), s) != elements[index].end()) {
				cout << "yes\n";
			}
			else {
				cout << "no\n";
			}
		}
		else if (type == "check") {
			cin >> ind;
			for (auto it = elements[ind].begin(); it != elements[ind].end(); ++it) {
				cout << *it << ' ';
			}
			cout << '\n';
		}
	}
	//QueryProcessor proc(m);
	//proc.processQueries();
	return 0;
}
