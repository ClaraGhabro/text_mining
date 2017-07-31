#include "../trie/node.hh"
#include "../trie/nodes.hh"
#include <iostream>
#include <string>
#include "search.hh"
#include <algorithm>

/**
 * \brief TextMiningApp main
 */


int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "\nsTextMiningApp Error: Not enough argument, run with:\n");
    fprintf(stderr, "./TextMiningApp path_compiled_dico.bin\n\n");
    return -1;
  }
  auto& node3 = trie::deserialize_nodes(argv[1]);

  std::string reading;
  std::string diff;
  std::string word;
  //std::string result{};

  while (std::cin >> reading)
  {
    if (reading.empty())
      break;
    std::cin >> diff >> word;

    std::cerr << "reading: " << reading
              << ", diff: " << diff
              << ", word: " << word << std::endl;

    // node3.dump();
    // std::cerr << node3.search_word("test") << '\n';
    auto results = trie::search(node3, word, std::stoi(diff));
    if (! results->empty())
    {
      // sort by ascending distance
      std::sort(results->begin(), results->end(),
            [](const auto& elt1, const auto& elt2) {
            return std::get<2>(elt1) < std::get<2>(elt2);
            });

      // sort by descending frequence
      std::sort(results->begin(), results->end(),
            [](const auto& elt1, const auto& elt2) {
            return std::get<1>(elt1) > std::get<1>(elt2);
            });

      std::cout << "[";
      unsigned i = 0;
      for (; i < results->size() - 1; ++i)
        std::cout << "{\"word\":\"" << std::get<0>(results->at(i))
                  << "\",\"freq\":" << std::get<1>(results->at(i))
                  << "\",distance\":" << std::get<2>(results->at(i)) << "},";
      std::cout << "{\"word\":\"" << std::get<0>(results->at(i))
                << "\",\"freq\":" << std::get<1>(results->at(i))
                << "\",distance\":" << std::get<2>(results->at(i)) << "}]"
                << std::endl;
    }
    else
      std::cerr << "resultat vide" << std::endl;

  }
  return 0;
}
