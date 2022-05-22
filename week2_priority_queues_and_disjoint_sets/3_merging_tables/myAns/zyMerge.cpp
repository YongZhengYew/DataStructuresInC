#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		//cout << "SUB 1\n";
		// find parent and compress path
		DisjointSetsElement* currSet = &sets[table];

		int currParent = currSet->parent;
		int res;
		//cout << "SUB 2\n";

		//cout << "TABLE: " << table << " CURRPARENT: " << currParent << "\n";

		if (currParent == table) {
			//cout << "SUB 3a\n";
			res = table;
			
		} else {
			//cout << "SUB 3b\n";
			res = getParent(currParent);
			currSet->parent = res;
		}
		//cout << res << "\n";
		//cout << "SUB 4\n";
		return res;
	}

	void merge(int destination, int source) {
		//cout << "HI 1\n";
		int realDestination = getParent(destination);
		DisjointSetsElement* realDestinationPtr = &sets[realDestination];
		int realSource = getParent(source);
		DisjointSetsElement* realSourcePtr = &sets[realSource];
		//cout << "HI 2\n";
		
		if (realDestinationPtr != realSourcePtr) {
			//cout << "HI 3\n";
			// merge two components
			// use union by rank heuristic
			int realDestinationRank = realDestinationPtr->rank;
			int realSourceRank = realSourcePtr->rank;

			DisjointSetsElement* newRootPtr;
			DisjointSetsElement* otherPtr;
			if (realDestinationRank != realSourceRank) {
				//cout << "HI 4a\n";
				newRootPtr = realDestinationRank > realSourceRank ? realDestinationPtr : realSourcePtr;
				otherPtr = realDestinationRank > realSourceRank ? realSourcePtr : realDestinationPtr;
			} else {
				//cout << "HI 4b\n";
				newRootPtr = realDestinationPtr;
				otherPtr = realSourcePtr;
				newRootPtr->rank += 1;
			}
			//cout << "HI 5\n";
			newRootPtr->size += otherPtr->size;
			otherPtr->size = 0;
			//cout << otherPtr->parent << " " << newRootPtr->parent << "\n";
			otherPtr->parent = newRootPtr->parent;
			//cout << otherPtr->parent << " " << newRootPtr->parent << "\n";
			//cout << "HI 6\n";

			if (newRootPtr->size > max_table_size) {
				max_table_size = newRootPtr->size;
			}

                        // update max_table_size
		}		
	}
};

int main() {
	int n, m;
	//cin >> n >> m;
	n = 100000;
	m = 100000;

	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
                --destination;
                --source;
		
		tables.merge(destination, source);
	        cout << tables.max_table_size << endl;
	}

	return 0;
}
