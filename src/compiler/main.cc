#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "trie/node.hh"
#include "trie/nodes.hh"



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
  auto node1 = trie::get_node(trie::add_node());
  node1->insert_word("tastons", 1);
  node1->insert_word("test", 2);
  node1->insert_word("hello", 3);
  node1->insert_word("testons", 1);
  node1->insert_word("hel", 4);
  node1->insert_word("hek", 5);
  node1->dump();
*/

  std::ifstream ifstream(argv[1]);
  std::string word;
  std::string freq;

 // trie::serialize_nodes(argv[2]);
  auto node2 = trie::get_node(trie::add_node());

  // std::string first_letter = "";


  while (ifstream >> word >> freq)
  {
    node2->insert_word(word, std::stoi(freq));
  }

  trie::serialize_nodes(argv[2]);

  // node2.dump("");
 
  // int diff = 0;
//
  // while (ifstream >> word >> freq)
  // {
    // if (diff < 40)
    // {
      // if (word[0] != first_letter[0])
      // {
        // first_letter [0] = word[0];
        // diff++;
      // }
      // // std::cerr << "diff: " << diff << '\n';
      // node2.insert_word(word, std::stoi(freq));
    // }
    // else
    // {
      // // std::cerr << "diff: " << diff << '\n';
      // std::ofstream out;
      // out.open(argv[2], std::ios::app);
      // node2.write_node(out);
      // first_letter = word[0];
      // out.close();
      // node2 = trie::Node{};
      // diff = 0;
    // }
  // }
  // std::ofstream out;
  // out.open(argv[2], std::ios::app);
  // node2.write_node(out);
  // first_letter = word[0];
  // out.close();
  // read(argv[2], node2);
 // node2.print_trie();
 std::cerr << "word: " << word << ", freq: " << freq << '\n';





  //node2.print_trie("");


  return 0;
}
