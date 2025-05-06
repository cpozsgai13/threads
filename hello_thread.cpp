#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

auto hello = []() {
  this_thread::sleep_for(chrono::seconds(20));
  cout << "Hello" << endl;
};

int main() {

  thread t(hello);

  t.join();

  return 0;
}
