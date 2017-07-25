#include "trie/node.hh"
#include "trie/nodes.hh"

/**
 * \brief TextMiningApp main
 */

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "\nsTextMiningApp Error: Not enough argument, run with:\n./TextMiningApp path_compiled_dico.bin\n\n");
    return -1;
  }

  auto node3 = trie::deserialize_nodes(argv[1]);
  // node3->dump();
  std::cerr << "size: " << sizeof (node3) << std::endl;

  return 0;
}
