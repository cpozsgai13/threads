#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
using namespace std;

auto print = [](int i) {
  cout << i << endl;
};

class EvenOddPrinter {
public:
  EvenOddPrinter(int n):N(n){}

  void run() {
    thread evenThread(&EvenOddPrinter::even, this);
    thread oddThread(&EvenOddPrinter::odd, this);

    evenThread.join();
    oddThread.join();
  }

  void even() {
    while(true) {
      unique_lock<mutex> lock(m);
      cond.wait(lock, [&](){ return (i >= N) || (0 == i % 2);});
      if(i >= N) {
        break;
      }
      print(i);
      ++i;
      lock.unlock();
      cond.notify_one();
    }
  }
  void odd() {
    while(true) {
      unique_lock<mutex> lock(m);
      cond.wait(lock, [&](){ return (i >= N) || (1 == i % 2);});
      if(i >= N) {
        break;
      }
      print(i);
      ++i;
      lock.unlock();
      cond.notify_one();
    }
  }
private:
  int i{0};
  int N;
  condition_variable cond;
  mutex m;
};


int main() {
  int N = 10;
  EvenOddPrinter evenOddPrinter(N);
  evenOddPrinter.run();

  return 0;
}
