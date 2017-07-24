#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "trie/trie.hh"



// void write_node(const std::string& file_name, const trie::Node& node)
// {
  // std::ofstream out;
  // out.open(file_name, std::ios::binary);
  // for (size_t i = 0; i < node.get_children.size(); ++i)
  // {
   //
    // out.write(reinterpret_cast<const char*>(&node), sizeof(trie::Node));
  // }
  // out.close();
// }

void read(const std::string& file_name, trie::Node& node)
{
  std::ifstream in;
  in.open(file_name, std::ios::binary);
  in.read(reinterpret_cast<char*>(&node), sizeof (trie::Node));
  in.close();
}



/**
 * \brief TextMiningCompiler main
 * has to be run with path_to_word.txt name_of_new_compiled_dico.bin
 * */
int main(int argc, char* argv[]) {
  if (argc != 3)
  {
    fprintf(stderr, "\nError: Not enough argument, run with:\n./TextMiningCompiler path_word.txt path_compiled_dico.bin\n\n");
    return -1;
  }

/*
  trie::Node node1{};
  node1.insert_word("test", 2);
  node1.insert_word("hello", 3);
  node1.insert_word("testons", 1);
  node1.insert_word("hel", 4);
  node1.insert_word("hek", 5);
  node1.print_trie("");
*/

  std::ifstream ifstream(argv[1]);

  std::string word;
  std::string freq;

  trie::Node node2{};

  std::string first_letter = "";

  while (ifstream >> word >> freq)
  {
    if (word[0] == first_letter[0])
      node2.insert_word(word, std::stoi(freq));
    else
    {
      std::ofstream out;
      out.open(argv[2], std::ios::app);
      node2.write_node(out);
      first_letter = word[0];
      out.close();
      //TODO: remise a zero du trie
      node2 = trie::Node{};
    }
  }
  //read(argv[2], node2);
 // node2.print_trie();
  std::cerr << "word: " << word << ", freq: " << freq << '\n';

  //node2.print_trie("");


  return 0;
}
