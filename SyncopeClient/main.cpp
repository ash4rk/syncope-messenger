#include <iostream>
#include <CommonNetworking/Base.h>

int main() {
  std::cout << "Hello, World! I am client!" << std::endl;
  std::cout << static_cast<int>(MyEnum::One) << std::endl;
  print_spdlog();
  return 0;
}