#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

auto f1 = []() {
  this_thread::sleep_for(chrono::seconds(3));
  cout << "f1 complete" << endl;
};

auto f2 = []() {
  this_thread::sleep_for(chrono::seconds(5));
  cout << "f2 complete" << endl;
};

class BackgroundTask {
public:
  void operator()() const {
    f1();
    f2();
  }

};

int main() {

  //  Doesn't work - C++ most vexing parse.
  //  This can be interpreted by the compiler as a function
  //  declaration not a constructor.
  //thread t(BackgroundTask());

  //  However you can do this.
  thread t((BackgroundTask()));

  //  Or this:
  //BackgroundTask task;
  //thread t(task);

  t.join();

  return 0;
}
