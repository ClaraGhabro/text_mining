#pragma once

#include <boost/program_options.hpp>
#include <utility>

namespace options
{
std::pair<std::string, std::string> parse_option(int args, char* argv[]);
}
