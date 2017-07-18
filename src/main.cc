#include <iostream>

#include "options/opt_parser.hh"
#include "trie/trie.hh"

int main(int argc, char* argv[]) {
  const std::pair<std::string, std::string> option = options::parse_option(argc, argv);

  if (option.first == "" && option.second == "")
    return -1;

  if (!option.first.compare("help") || !option.first.compare("version"))
    // exit if help or version is asked
    return 0;

  if (option.second.compare(""))
    std::cerr << "frequency: " << option.second << std::endl;

  std::cerr << "dico: " << option.first << std::endl;


  trie::Node node1{};
  node1.insert_word("test", 0);
  node1.insert_word("hello");
  node1.insert_word("testons", 0);
  node1.insert_word("hel");
  node1.insert_word("hek");
  node1.print_trie("");



  return 0;
}