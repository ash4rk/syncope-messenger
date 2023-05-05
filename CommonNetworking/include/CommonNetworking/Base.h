#pragma once

#include <spdlog/spdlog.h>

enum class MyEnum {
	One,
	Two,
	Three	
};

void print_spdlog() { spdlog::info("Welcome to spdlog!"); }

