#pragma once

#include <boost/program_options.hpp>
#include <utility>

namespace options
{
/**
 * \brief parse options given in command line
 *
 * \param args number of arguments
 * \param argv pgiven parameters
 */
std::pair<std::string, std::string> parse_option(int args, char* argv[]);
}
