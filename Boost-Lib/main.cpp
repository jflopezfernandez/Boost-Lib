
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/chrono.hpp>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>


int main()
{
	boost::optional<std::string> opt = boost::make_optional<std::string>("yes");

	std::cout << "Did it work? " << opt.get() << "\n";
}
