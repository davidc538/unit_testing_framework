#include "UnitTest.hpp"

UnitTestSystem uts1("TestModule1", [](UnitTestSystem& uts)
{
	uts.RunUnitTest("Always Pass", [](std::string& errors)
	{
		return true;
	});

	uts.RunUnitTest("Always Fail", [](std::string& errors)
	{
		errors = "Should always fail.";
		return false;
	});
});

int main(int argc, char** argv)
{
	std::cin.get();
}
