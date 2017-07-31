#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "trie/node.hh"
#include "trie/nodes.hh"


/**
 * \brief TextMiningCompiler main
 * has to be run with path_to_word.txt name_of_new_compiled_dico.bin
 * */
int main(int argc, char* argv[]) {
  if (argc != 3)
  {
    fprintf(stderr, "\nsTextMiningCompiler Error: Not enough argument, run with:\n./TextMiningCompiler path_word.txt path_compiled_dico.bin\n\n");
    return -1;
  }
  
  /*
  auto node1 = trie::get_node(trie::add_node());
  node1->insert_word("tastons", 1);
  node1->insert_word("test", 2);
  node1->insert_word("hello", 3);
  node1->insert_word("testons", 1);
  node1->insert_word("hel", 4);
  node1->insert_word("hek", 5);
  node1->dump();
*/
  std::cout << "Size structure: " << sizeof (trie::Node) << std::endl;

  std::ifstream ifstream(argv[1]);
  std::string word;
  std::string freq;

  auto& node2 = trie::get_node(trie::add_node());

  while (ifstream >> word >> freq)
  {
    node2.insert_word(word, std::stoi(freq));
  }

  trie::serialize_nodes(argv[2]);
  std::cerr << "word: " << word << ", freq: " << freq << '\n';
  std::cerr << "word: test, freq: " << node2.search_word("test") << '\n';
  // node2.dump("");

  return 0;
}
