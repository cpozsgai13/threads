#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
using namespace std;

auto print = [](int i) {
  //cout << i << endl;
};

class ModPrinter {
public:
  ModPrinter(int n):N(n){}

  void run() {
    thread mod30Thread(&ModPrinter::mod30, this);
    thread mod31Thread(&ModPrinter::mod31, this);
    thread mod32Thread(&ModPrinter::mod32, this);

    mod30Thread.join();
    mod31Thread.join();
    mod32Thread.join();
  }

  void mod30() {
    while(true) {
      unique_lock<mutex> lock(m);
      cond.wait(lock, [&](){ return (i >= N) || (0 == i % 3);});
      cout << "mod30 Got signaled - i = " << i << endl;
      if(i >= N) {
        break;
      }
      print(i);
      ++i;
      lock.unlock();
      cond.notify_all();
    }
  }
  void mod31() {
    while(true) {
      unique_lock<mutex> lock(m);
      cond.wait(lock, [&](){ return (i >= N) || (1 == i % 3);});
      cout << "mod31 Got signaled - i = " << i << endl;
      if(i >= N) {
        break;
      }
      print(i);
      ++i;
      lock.unlock();
      cond.notify_all();
    }
  }
  void mod32() {
    while(true) {
      unique_lock<mutex> lock(m);
      cond.wait(lock, [&](){ return (i >= N) || (2 == i % 3);});
      cout << "mod32 Got signaled - i = " << i << endl;
      if(i >= N) {
        break;
      }
      print(i);
      ++i;
      lock.unlock();
      cond.notify_all();
    }
  }
private:
  int i{0};
  int N;
  condition_variable cond;
  mutex m;
};


int main() {
  int N = 15;
  ModPrinter modPrinter(N);
  modPrinter.run();

  return 0;
}
