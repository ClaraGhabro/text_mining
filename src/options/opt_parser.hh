#pragma once

#include <boost/program_options.hpp>

namespace options 
{
  const std::string* parse_option(int args, char* argv[]);
}
