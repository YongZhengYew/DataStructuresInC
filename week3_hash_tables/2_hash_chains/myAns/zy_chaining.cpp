#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

struct Node {
    string name;
    Node* next;
    Node* prev;

    Node(string newName) : name(newName), next(NULL), prev(NULL) {};

    void pointTo(Node* pointee) {
        next = pointee;
        pointee->prev = this;
    }
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<Node*> chainVec;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

    Node* findChain(string targetString) {
        int hashResult = hash_func(targetString);
        //std::cout << "findChain 1\n";
        Node* currNode = chainVec[hashResult];
        //std::cout << "findChain 2\n";
        if (currNode != NULL) {
            string currName = currNode->name;
            if (currName == targetString) return currNode;

            //std::cout << "findChain 3\n";

            while (currName != targetString) {
                if (currNode->next != NULL) {
                    currNode = currNode->next;
                    currName = currNode->name;
                    //std::cout << "findChain 4\n";
                    if (currName == targetString) return currNode;
                } else {
                    break;
                }
            }
        }

        //std::cout << "findChain END\n";

        return NULL;
    }

    void add(string targetString) {
        int hashResult = hash_func(targetString);
        //std::cout << "adding 1\n";
        Node* searchResult = findChain(targetString);
        //std::cout << "adding 2\n";
        if (searchResult != NULL) {
            //std::cout << "adding 3a\n";
            searchResult->name = targetString;
        } else {
            //std::cout << "adding 3b1\n";
            Node* temp = chainVec[hashResult];
            //std::cout << "adding 3b2\n";
            Node* newNodePtr = new Node(targetString);
            //std::cout << "adding 3b3\n";
            chainVec[hashResult] = newNodePtr;
            //std::cout << "adding 3b4\n";
            if (temp != NULL) {
                newNodePtr->pointTo(temp);
            } else {
                chainVec[hashResult] = newNodePtr;
            }
            
            //std::cout << "adding 3b5\n";
        }
    }

    void del(string targetString) {
        //std::cout << "deling 1\n";
        int hashResult = hash_func(targetString);
        //std::cout << "deling 2\n";
        Node* searchResult = findChain(targetString);
        //std::cout << "deling 3\n";

        if (searchResult != NULL) {
            //std::cout << "deling 4a1\n";
            Node* currPrev = searchResult->prev;
            //std::cout << "deling4a2\n";
            Node* currNext = searchResult->next;
            //std::cout << "deling 4a3\n";
            if (currPrev != NULL) {
                currPrev->next = currNext;
            } else {
                chainVec[hashResult] = NULL;
            }
            //std::cout << "deling 4a4\n";
            if (currNext != NULL) {
                if (currPrev != NULL) {
                    currNext->prev = currPrev;
                } else {
                    currNext->prev = NULL;
                    chainVec[hashResult] = currNext;
                }
            }
            //std::cout << "deling 4a5\n";
            free(searchResult);
            //std::cout << "deling 4a6\n";
        } else {
            //std::cout << "deling 4b1\n";
            // Do nothing
        }
    }

    void printChain(int targetChain) {
        Node* currNode = chainVec[targetChain];
        if (currNode == NULL) {
            std::cout << "\n";
        } else {
            while (currNode != NULL) {
                std::cout << currNode->name << " ";
                if (currNode->next != NULL) {
                    currNode = currNode->next;
                } else {
                    std::cout << "\n";
                    break;
                }
            }
        }
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        chainVec.resize(bucket_count);
        for (auto i : chainVec) {
            i = NULL;
        }
    }

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
            printChain(query.ind);
        } else {
            Node* searchResult = findChain(query.s);
            if (query.type == "find") {
                bool found = searchResult != NULL ? true : false;
                writeSearchResult(found);
            } else if (query.type == "add") {
                add(query.s);
            } else if (query.type == "del") {
                del(query.s);
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

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
