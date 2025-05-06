#include <thread>
#include <iostream>

using namespace std;


class FooBar {
private:
    int N;
    mutex mut;
    condition_variable cond;
    int index;  //  0 = foo, 1 = bar, 2 = baz
public:
  void print() {
  }
  void foo(function<void()> p) {
    for (int i = 0; i < n; i++) {
      print("foo");
    }
  }

  void bar() {
    for (int i = 0; i < n; i++) {
      print("bar");
    }
  }

  void baz() {
  }
}

int main() {
   int n = 3;
}
