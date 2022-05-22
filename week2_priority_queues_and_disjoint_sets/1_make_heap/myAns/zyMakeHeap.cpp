#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;
  vector<int> finishedChildVec;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
    

    //data_.resize(100000);

    /*
    vector<int> vec {
    };
    

    
    for (int i: vec) {
      data_.push_back(i);
    }
    */
    
  }

  void printVec(vector<int> vec) {
    cout << "PRINTVEC CALLED" << "\n";
    for (int i: vec) {
      cout << i << "\n";
    }
    cout << "PRINTVEC END" << "\n";
  }

  int getParentIndex(int childIndex) {
    return (childIndex-1)/2; // flooring is intended
  }

  int getLeftChildIndex(int parentIndex) {
    return (parentIndex*2)+1;
  }

  int getRightChildIndex(int parentIndex) {
    return (parentIndex*2)+2;
  }

  void siftDown(int parentIndex) {
    int leftChildIndex = getLeftChildIndex(parentIndex);
    int rightChildIndex = getRightChildIndex(parentIndex);

    int minChildIndex;
    if (rightChildIndex >= data_.size()) {
      if (leftChildIndex >= data_.size()) {
        return;
      } else {
        minChildIndex = leftChildIndex;
      }
    } else {
      minChildIndex = data_[leftChildIndex] <= data_[rightChildIndex] ? leftChildIndex : rightChildIndex; // LEFT is DEFAULT if EQUAL
    }

    if (data_[parentIndex] > data_[minChildIndex]) {
      int temp = data_[minChildIndex];
      data_[minChildIndex] = data_[parentIndex];
      data_[parentIndex] = temp;

      //cout << "hello" << std::endl;

      swaps_.push_back(make_pair(parentIndex, minChildIndex));

      siftDown(minChildIndex);
    }
  }

  /*
  void fixTrio(int childIndex) {
    cout << "CHILDINDEX: " << childIndex << "\n";
    for (int i = finishedChildVec.size()-1; i >= 0; i--) {
      if (childIndex == finishedChildVec[i]) {
        cout << "HA" << "\n";
        return;
      }
    }

    int parentIndex = getParentIndex(childIndex);
    int leftChildIndex = getLeftChildIndex(parentIndex);
    int rightChildIndex = getRightChildIndex(parentIndex);

    int minChildIndex = data_[leftChildIndex] <= data_[rightChildIndex] ? leftChildIndex : rightChildIndex; // LEFT is DEFAULT if EQUAL

    //cout << "PARENT: " << parentIndex << " LEFTC: " << leftChildIndex << " RIGHTC: " << rightChildIndex << " MIN: " << minChildIndex << "\n";
    
    // do the swap
    if (data_[parentIndex] > data_[minChildIndex]) {
      int temp = data_[minChildIndex];
      data_[minChildIndex] = data_[parentIndex];
      data_[parentIndex] = temp;

      //cout << "hello" << std::endl;

      swaps_.push_back(make_pair(parentIndex, minChildIndex));
    }

    finishedChildVec.push_back(rightChildIndex);
    finishedChildVec.push_back(leftChildIndex);
    printVec(finishedChildVec);
  }
  */

  void GenerateSwaps() {
    swaps_.clear();

    for (int i = data_.size()-1; i >= 0; i--) {
      siftDown(i);
      //cout << i << std::endl;
    }
  }

/*
  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
  }
*/

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}