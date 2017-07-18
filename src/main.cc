#include <iostream>
#include <fstream>
#include <string>

#include "options/opt_parser.hh"
#include "trie/trie.hh"

int main(int argc, char* argv[]) {
  const std::pair<std::string, std::string> option = options::parse_option(argc, argv);

  if (option.first == "" && option.second == "")
    return -1;

  if (!option.first.compare("help") || !option.first.compare("version"))
    // exit if help or version is asked
    return 0;


  // Dans le cas de TextMiningCompiler, on a forcement la frequence donnée en argument
  //if (option.second.compare(""))
  std::cerr << "frequency: " << option.second << std::endl;

  std::cerr << "dico: " << option.first << std::endl;


  trie::Node node1{};
  node1.insert_word("test", 2);
  node1.insert_word("hello", 3);
  node1.insert_word("testons", 1);
  node1.insert_word("hel", 4);
  node1.insert_word("hek", 5);
  node1.print_trie("");

  std::ifstream ifstream(option.second);

  std::string word;
  std::string freq;

  trie::Node node2{};
  int i = 0;
  while (ifstream >> word >> freq)
  {
    std::cerr << "word: " << word << ", freq: " << freq << '\n';
    i++;
    if (i == 100)
      break;

    node2.insert_word(word, std::stoi(freq));
  }

  node2.print_trie("");


  return 0;
}
