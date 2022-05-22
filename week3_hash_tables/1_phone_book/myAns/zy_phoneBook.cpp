#include <iostream>
#include <vector>
#include <string>
#include <utility>

using std::string;
using std::vector;
using std::cin;
using std::pair;

struct Query {
    string type, name;
    int number;

    Query(string newType = "DEF_NOTYPE", string newName = "DEF_NONAME", int newNumber = -1) : type(newType), name(newName), number(newNumber) {}
};



vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n, Query());
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
    vector<pair<int, string>> contacts(10000000, pair<int, string>(-1, ""));
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            // if we already have contact with such number,
            // we should rewrite contact's name
            contacts[queries[i].number] = pair<int, string>(queries[i].number, queries[i].name);
            // otherwise, just add it
        } else if (queries[i].type == "del") {
            contacts[queries[i].number] = pair<int, string>(-1, "NONAME");
        } else {
            string response = "not found";
            if (contacts[queries[i].number].first != -1) {
                response = contacts[queries[i].number].second;
            }
            result.push_back(response);
        }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
