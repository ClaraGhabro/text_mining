#include "opt_parser.hh"
#include <iostream>

#ifndef TEXT_MINING_VERSION
#define TEXT_MINING_VERSION 0.1
#endif



namespace options 
{
  const std::string* parse_option(int argc, char* argv[])
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
      const std::string* help = new std::string("help");
      return help;
    }

    if (vmap.count("version"))
    {
      std::cout << "text_mining VERSION: "
                << TEXT_MINING_VERSION
                << std::endl;
      const std::string* version = new std::string("version");
      return version;
    }

    if (vmap.count("dico"))
    {
      const std::string* path_to_dico = new std::string(vmap["dico"].as<std::string>());

      if (vmap.count("frequency"))
      {
        const std::string* path_to_frequency = new std::string(vmap["frequency"].as<std::string>());
        const std::string dico_freq[] = { *path_to_dico, *path_to_frequency};
        return dico_freq;
      }
      else
        return path_to_dico;
    }

  std::cout << description << std::endl;
  return NULL;
  }

}
