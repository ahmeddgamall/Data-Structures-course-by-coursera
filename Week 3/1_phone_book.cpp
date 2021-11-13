#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Query {
	string type, name;
	int number;
};

vector<Query> read_queries() {
	int n;
	cin >> n;
	vector<Query> queries(n);
	for (int i = 0; i < n; ++i) {
		cin >> queries[i].type;
		if (queries[i].type == "add")
			cin >> queries[i].number >> queries[i].name;
		else
			cin >> queries[i].number;
	}
	return queries;
}

void write_responses(const vector<string>& result) {
	for (size_t i = 0; i < result.size(); ++i)
		std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
	vector<string> result;
	// Keep list of all existing (i.e. not deleted yet) contacts.
	vector<Query> contacts;
	for (size_t i = 0; i < queries.size(); ++i)
		if (queries[i].type == "add") {
			bool was_founded = false;
			// if we already have contact with such number,
			// we should rewrite contact's name
			for (size_t j = 0; j < contacts.size(); ++j)
				if (contacts[j].number == queries[i].number) {
					contacts[j].name = queries[i].name;
					was_founded = true;
					break;
				}
			// otherwise, just add it
			if (!was_founded)
				contacts.push_back(queries[i]);
		}
		else if (queries[i].type == "del") {
			for (size_t j = 0; j < contacts.size(); ++j)
				if (contacts[j].number == queries[i].number) {
					contacts.erase(contacts.begin() + j);
					break;
				}
		}
		else {
			string response = "not found";
			for (size_t j = 0; j < contacts.size(); ++j)
				if (contacts[j].number == queries[i].number) {
					response = contacts[j].name;
					break;
				}
			result.push_back(response);
		}
	return result;
}

int main() {
	//write_responses(process_queries(read_queries()));
	int n;
	cin >> n;
	map<int, string> phone_book;
	for (int i = 0; i < n; ++i) {
		int number;
		string name;
		string query;
		cin >> query;
		if (query == "add") {
			cin >> number >> name;
			if (phone_book.find(number) == phone_book.end()) {
				phone_book.insert(pair<int, string>(number, name));
			}
			else {
				phone_book[number] = name;
			}
		}
		else if (query == "del") {
			cin >> number;
			phone_book.erase(number);
		}
		else {
			cin >> number;
			if (phone_book.find(number) == phone_book.end()) {
				cout << "not found\n";
			}
			else {
				cout << phone_book[number] << "\n";
			}
		}
	}
	return 0;
}
