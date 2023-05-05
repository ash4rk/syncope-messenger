#include <CommonNetworking/Base.h>

#include <algorithm>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <spdlog/spdlog.h>

void PrintSPDLog() { spdlog::info("Welcome to spdlog!"); }

void MultiplyByThree() {
  using namespace boost::lambda;
  typedef std::istream_iterator<int> in;

  std::for_each(in(std::cin), in(), std::cout << (_1 * 3) << " \n");
}
