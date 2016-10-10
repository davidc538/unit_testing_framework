#pragma once

#include <functional>
#include <chrono>
#include <string>
#include <vector>
#include <iostream>

constexpr bool run_tests = true;

struct TestResult
{
	std::string test_name;
	bool passed;
	std::string error_messages;
	unsigned long long nanoseconds;

	inline TestResult(std::string test_name, bool passed, std::string errors, unsigned long long nanoseconds)
	{
		this->test_name = test_name;
		this->passed = passed;
		this->error_messages = errors;
		this->nanoseconds = nanoseconds;
	}
};

class UnitTestSystem
{
private:
	std::vector<TestResult> results;
	std::string module_name;

public:
	inline UnitTestSystem(std::string module_name, std::function<void(UnitTestSystem&)> test_function);
	inline void RunUnitTest(std::string test_name, std::function<bool(std::string&)> test);
};

inline UnitTestSystem::UnitTestSystem(std::string module_name, std::function<void(UnitTestSystem&)> test_function)
{
	if (!run_tests) return;

	this->module_name = module_name;
	test_function(*this);

	std::cout << "Module: " << module_name << std::endl;

	int passed = 0, failed = 0;

	for (const auto& result : results)
	{
		std::cout << "   " << result.test_name << ": " << ((result.passed) ? " passed." : " failed.")
			<< " time(ns): " << std::to_string(result.nanoseconds) << ", error messages: " << result.error_messages << std::endl;

		if (result.passed) passed++;
		else failed++;
	}

	std::cout << "passed: " << passed << ", failed: " << failed << std::endl << std::endl;
}

inline void UnitTestSystem::RunUnitTest(std::string test_name, std::function<bool(std::string&)> test)
{
	std::string errors;
	bool result;

	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

	start = std::chrono::high_resolution_clock::now();

	constexpr bool clock_is_steady = std::chrono::high_resolution_clock::is_steady;

	try
	{
		result = test(errors);
	}
	catch (std::exception& e)
	{
		result = false;
		errors = +e.what();
	}

	end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<long long, std::nano> elapsed_s = end - start;

	auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_s);

	results.push_back(TestResult(test_name, result, errors, time.count()));
}
