#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

class ThreadGuard {
  thread& t;

public:
  explicit ThreadGuard(thread& t_): t(t_){
  }

  ~ThreadGuard() {
    if(t.joinable()) {
      t.join();
    }
  }

  ThreadGuard(const ThreadGuard&) = delete;
  ThreadGuard& operator=(const ThreadGuard&) = delete;
};

struct func {
  int& i;
  func(int& v):i(v){}
  void operator()() {
    for(int i = 0; i < 1000; ++i) {
      this_thread::sleep_for(chrono::seconds(1));
      ++i;
    }
  }

};

int main() {
  int local_value = 0;

  func Func(local_value);

  thread t(Func);
  ThreadGuard guard(t);
  
  this_thread::sleep_for(chrono::seconds(2));

  return 0;
}
