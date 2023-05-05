#include <iostream>

#include <CommonNetworking/Base.h>

int main() {
  std::cout << "Hello, World! I am server!" << std::endl;
  std::cout << static_cast<int>(MyEnum::Two) << std::endl;
  return 0;
}
