#include <iostream>
#include <vector>
#include <algorithm>


using std::vector;
using std::cin;
using std::cout;


class Thread {
  public:
    int index;
    long long jobTimeLeft;

    Thread(int newIndex) {
      index = newIndex;
      jobTimeLeft = 0;
    }
};

class JobRecord {
  public:
    int assignedThread;
    long long startTime;

    JobRecord(int newAssignedThread, long long newStartTime) {
      assignedThread = newAssignedThread;
      startTime = newStartTime;
    }
};


class JobQueue {
  private:
    int num_workers_;
    vector<int> jobs_;

    long long currTime = 0;
    int currJobIndex = 0;
    vector<Thread> threadHeap;
    vector<JobRecord> jobRecordVec;

    void WriteResponse() const {
      for (auto record : jobRecordVec) {
        cout << record.assignedThread << " " << record.startTime << "\n";
      }
    }

    
    void ReadData() {
      int m;
      cin >> num_workers_ >> m;

      threadHeap.resize(num_workers_, Thread(0));
      for (int i = 0; i < num_workers_; i++) {
        threadHeap[i] = Thread(i);
      }
      
      // for (int i = 0; i < num_workers_; i++) {
      //   threadHeap.push_back(Thread(i));
      // }

      jobRecordVec.resize(m, JobRecord(0, 0));
      jobs_.resize(m);

      for(int i = 0; i < m; ++i) {
        cin >> jobs_[i];
      }
    }

    int getParentIndex(int childIndex) {
      return (childIndex-1)/2 < 0 ? 0 : (childIndex-1)/2; // integer division intended
    }

    int getLeftChildIndex(int parentIndex) {
      return (parentIndex*2)+1;
    }

    int getRightChildIndex(int parentIndex) {
      return (parentIndex*2)+2;
    }

    bool idleThreadsAvailable() {
      return threadHeap[0].jobTimeLeft == 0;
    }

    bool anyJobsRemaining() {
      return currJobIndex < jobs_.size();
    }

    void siftDownDummy() {
      threadHeap[0].jobTimeLeft = 1;
    }

    void siftDownNonRecursiveWrapper() {
      int targetIndex = 0;
      int temp;
      while (targetIndex != -69) {
        temp = siftDownNonRecursive(targetIndex);
        targetIndex = temp;
      }
    }

    int siftDownNonRecursive(int targetIndex) {
      int leftChildIndex = getLeftChildIndex(targetIndex);
      int rightChildIndex = getRightChildIndex(targetIndex);

      int leftIndex = threadHeap[leftChildIndex].index;
      int rightIndex = threadHeap[rightChildIndex].index;
      int currIndex = threadHeap[targetIndex].index;
      long long leftJobTimeLeft = threadHeap[leftChildIndex].jobTimeLeft;
      long long rightJobTimeLeft = threadHeap[rightChildIndex].jobTimeLeft;
      long long currJobTimeLeft = threadHeap[targetIndex].jobTimeLeft;

      int swapIndex;
      if (rightChildIndex >= threadHeap.size()) {
        if (leftChildIndex >= threadHeap.size()) {
          return -69;
        } else {
          if (leftJobTimeLeft < currJobTimeLeft) {
            swapIndex = leftChildIndex;
          } else if (leftJobTimeLeft == currJobTimeLeft) {
            if (leftIndex < currIndex) {
              swapIndex = leftChildIndex;
            } else {
              return -69;
            }
          } else {
            return -69;
          }
        }
      } else {
        if (leftJobTimeLeft < currJobTimeLeft && rightJobTimeLeft < currJobTimeLeft) {
          if (leftJobTimeLeft != rightJobTimeLeft) {
            swapIndex = leftJobTimeLeft < rightJobTimeLeft ? leftChildIndex : rightChildIndex;
          } else {
            swapIndex = leftIndex < rightIndex ? leftChildIndex : rightChildIndex;
          }
        } else if (leftJobTimeLeft < currJobTimeLeft) {
          swapIndex = leftChildIndex;
        } else if (rightJobTimeLeft < currJobTimeLeft) {
          swapIndex = rightChildIndex;
        } else if (leftJobTimeLeft == currJobTimeLeft && rightJobTimeLeft == currJobTimeLeft) {
          if (leftIndex < currIndex && rightIndex < currIndex) {
            swapIndex = leftIndex < rightIndex ? leftChildIndex : rightChildIndex;
          } else if (leftIndex < currIndex) {
            swapIndex = leftChildIndex;
          } else if (rightIndex < currIndex) {
            swapIndex = rightChildIndex;
          } else {
            return -69;
          }
        } else if (leftJobTimeLeft == currJobTimeLeft) {
          if (leftIndex < currIndex) {
            swapIndex = leftChildIndex;
          } else {
            return -69;
          }
        } else if (rightJobTimeLeft == currJobTimeLeft) {
          if (rightIndex < currIndex) {
            swapIndex = rightChildIndex;
          } else {
            return -69;
          }
        } else {
          return -69;
        }
      }

      Thread temp = threadHeap[targetIndex];
      threadHeap[targetIndex] = threadHeap[swapIndex];
      threadHeap[swapIndex] = temp;

      return swapIndex;
    }

    /*
    void siftDown(int targetIndex) {
      int leftChildIndex = getLeftChildIndex(targetIndex);
      int rightChildIndex = getRightChildIndex(targetIndex);

      //cout << leftChildIndex << " " << rightChildIndex << "\n";

      int leftIndex = threadHeap[leftChildIndex].index;
      int rightIndex = threadHeap[rightChildIndex].index;
      int currIndex = threadHeap[targetIndex].index;
      long long leftJobTimeLeft = threadHeap[leftChildIndex].jobTimeLeft;
      long long rightJobTimeLeft = threadHeap[rightChildIndex].jobTimeLeft;
      long long currJobTimeLeft = threadHeap[targetIndex].jobTimeLeft;

      int swapIndex;
      if (rightChildIndex >= threadHeap.size()) {
        if (leftChildIndex >= threadHeap.size()) {
          return;
        } else {
          if (leftJobTimeLeft < currJobTimeLeft) {
            swapIndex = leftChildIndex;
          } else if (leftJobTimeLeft == currJobTimeLeft) {
            if (leftIndex < currIndex) {
              swapIndex = leftChildIndex;
            } else {
              return;
            }
          } else {
            return;
          }
        }
      } else {
        if (leftJobTimeLeft < currJobTimeLeft && rightJobTimeLeft < currJobTimeLeft) {
          if (leftJobTimeLeft != rightJobTimeLeft) {
            swapIndex = leftJobTimeLeft < rightJobTimeLeft ? leftChildIndex : rightChildIndex;
          } else {
            swapIndex = leftIndex < rightIndex ? leftChildIndex : rightChildIndex;
          }
        } else if (leftJobTimeLeft < currJobTimeLeft) {
          swapIndex = leftChildIndex;
        } else if (rightJobTimeLeft < currJobTimeLeft) {
          swapIndex = rightChildIndex;
        } else if (leftJobTimeLeft == currJobTimeLeft && rightJobTimeLeft == currJobTimeLeft) {
          if (leftIndex < currIndex && rightIndex < currIndex) {
            swapIndex = leftIndex < rightIndex ? leftChildIndex : rightChildIndex;
          } else if (leftIndex < currIndex) {
            swapIndex = leftChildIndex;
          } else if (rightIndex < currIndex) {
            swapIndex = rightChildIndex;
          } else {
            return;
          }
        } else if (leftJobTimeLeft == currJobTimeLeft) {
          if (leftIndex < currIndex) {
            swapIndex = leftChildIndex;
          } else {
            return;
          }
        } else if (rightJobTimeLeft == currJobTimeLeft) {
          if (rightIndex < currIndex) {
            swapIndex = rightChildIndex;
          } else {
            return;
          }
        } else {
          return;
        }
      }

      Thread temp = threadHeap[targetIndex];
      threadHeap[targetIndex] = threadHeap[swapIndex];
      threadHeap[swapIndex] = temp;

      siftDown(swapIndex);
    }
    */

    void assignJob() {
      threadHeap[0].jobTimeLeft = jobs_[currJobIndex];
      jobRecordVec[currJobIndex] = JobRecord(threadHeap[0].index, currTime);
      //jobRecordVec.push_back(JobRecord(threadHeap[0].index, currTime));
      currJobIndex += 1;
    }

    void smartProgressTime() {
      long long minTime = threadHeap[0].jobTimeLeft;
      for (int i = 0; i < threadHeap.size(); i++) {
        if (threadHeap[i].jobTimeLeft < minTime) {
          minTime = threadHeap[i].jobTimeLeft;
        }
      }

      for (int j = 0; j < threadHeap.size(); j++) {
        threadHeap[j].jobTimeLeft -= minTime;
      }

      currTime += minTime;
    }

    void progressTime() {
      for (int i = 0; i < threadHeap.size(); i++) {
        if (threadHeap[i].jobTimeLeft != 0) {
          threadHeap[i].jobTimeLeft -= 1;
        }
      }
      currTime += 1;
    }

    void processJobs() {
      while (anyJobsRemaining()) {
        while(idleThreadsAvailable()) {
          if (!anyJobsRemaining()) break;
          assignJob();
          //siftDownDummy();
          //siftDown(0);
          siftDownNonRecursiveWrapper();
        }
        smartProgressTime();
      }
    }

  public:
    void Solve() {
      ReadData();
      processJobs();
      WriteResponse();
    }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
