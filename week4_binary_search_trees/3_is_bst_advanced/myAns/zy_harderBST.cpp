#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTree_helper_towardsLeft(const vector<Node>& tree, int currNodeIndex, std::pair<int, bool> upperLimit, std::pair<int, bool> lowerLimit);

bool IsBinarySearchTree_helper_towardsRight(const vector<Node>& tree, int currNodeIndex, std::pair<int, bool> upperLimit, std::pair<int, bool> lowerLimit) {
  Node currNode = tree[currNodeIndex];
  if (upperLimit.second) {
    if (currNode.key > upperLimit.first) {
      return false;
    }
  }
  if (lowerLimit.second) {
    if (currNode.key < lowerLimit.first) {
      return false;
    }
  }
  bool resLeft = true;
  bool resRight = true;
  if (currNode.left != -1) {
    resLeft = IsBinarySearchTree_helper_towardsLeft(tree, currNode.left, std::pair<int,bool>(currNode.key, true), lowerLimit);
  }
  if (currNode.right != -1) {
    resRight = IsBinarySearchTree_helper_towardsRight(tree, currNode.right, upperLimit, std::pair<int,bool>(currNode.key, true));
  }
  return resLeft && resRight;
}

bool IsBinarySearchTree_helper_towardsLeft(const vector<Node>& tree, int currNodeIndex, std::pair<int, bool> upperLimit, std::pair<int, bool> lowerLimit) {
  Node currNode = tree[currNodeIndex];
  if (upperLimit.second) {
    if (currNode.key >= upperLimit.first) {
      return false;
    }
  }
  if (lowerLimit.second) {
    if (currNode.key < lowerLimit.first) {
      return false;
    }
  }
  bool resLeft = true;
  bool resRight = true;
  if (currNode.left != -1) {
    resLeft = IsBinarySearchTree_helper_towardsLeft(tree, currNode.left, std::pair<int,bool>(currNode.key, true), lowerLimit);
  }
  if (currNode.right != -1) {
    resRight = IsBinarySearchTree_helper_towardsRight(tree, currNode.right, upperLimit, std::pair<int,bool>(currNode.key, true));
  }
  return resLeft && resRight;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  if (tree.size() == 0) return true;

  return IsBinarySearchTree_helper_towardsRight(tree, 0, std::pair<int,bool>(0, false), std::pair<int,bool>(0, false));
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
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
