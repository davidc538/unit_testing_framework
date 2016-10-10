#include "UnitTest.hpp"

UnitTestSystem uts2("TestModule2", [](UnitTestSystem& uts)
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
