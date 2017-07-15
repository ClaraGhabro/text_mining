#include "opt_parser.hh"
#include <iostream>

#ifndef TEXT_MINING_VERSION
#define TEXT_MINING_VERSION 0.1
#endif



namespace options
{
std::pair<std::string, std::string> parse_option(int argc, char* argv[])
  {
    namespace opt = boost::program_options;

    opt::options_description description{ "Options list" };

    auto add = description.add_options();
    add("help,h", "Show usage");
    add("version,v", "Display current version of the project");
    add("frequency,f", opt::value<std::string>(), "Specify the file of words + frequencies");
    add("dico,d", opt::value<std::string>(), "Specify the compiled dictionnary to use");

    const auto parse_result = opt::parse_command_line(argc, argv, description);

    opt::variables_map vmap{};
    opt::store(parse_result, vmap);
    opt::notify(vmap);

    if (vmap.count("help"))
    {
      std::cout << description << std::endl;
      return std::make_pair("help", "");
    }

    if (vmap.count("version"))
    {
      std::cout << "text_mining VERSION: "
                << TEXT_MINING_VERSION
                << std::endl;
      return std::make_pair("version", "");
    }

    if (vmap.count("dico"))
    {
      if (vmap.count("frequency"))
      {
        return std::make_pair(vmap["dico"].as<std::string>(), vmap["frequency"].as<std::string>());
      }
      else
        return std::make_pair(vmap["dico"].as<std::string>(), "");
    }

  std::cout << description << std::endl;
  return std::make_pair("", "");
  }

}
