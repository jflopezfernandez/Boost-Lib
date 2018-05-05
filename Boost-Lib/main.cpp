
#include <Windows.h>
#include <experimental/filesystem>

#include <assert.h>
#include <math.h>
#include <time.h>

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/proto/proto.hpp>
#include <boost/typeof/std/ostream.hpp>

template <int I>
struct placeholder
{ };

boost::proto::terminal<placeholder<0>>::type const _1 = { { } };
boost::proto::terminal<placeholder<1>>::type const _2 = { { } };

boost::proto::terminal<std::ostream&>::type cout_ = { std::cout };

template <typename Expr>
void evaluate(const Expr& expr) {
	boost::proto::default_context context;
	boost::proto::eval(expr, context);
}

struct calculator_context
	: boost::proto::callable_context<calculator_context const> {
	// Values to replace the placeholders
	std::vector<double> args;

	// Define the result type of the calculator.
	// (This makes the calculator_context "callable")
	using result_type = double;

	// Handle the placeholders
	template <int I>
	double operator()(boost::proto::tag::terminal, placeholder<I>) const {
		return this->args[I];
	}
};

int main(int argc, char *argv[]) 
{
	calculator_context ctx;
	ctx.args.emplace_back(45); // The value of _1 is 45
	ctx.args.emplace_back(50); // The value of _2 is 50

	// Create an arithmetic expression and immediately evaluate it
	const auto d = boost::proto::eval((_2 - _1) / _2 * 100, ctx);

	// This prints "10"
	std::cout << "d: " << d << "\n";

	return EXIT_SUCCESS;
}
