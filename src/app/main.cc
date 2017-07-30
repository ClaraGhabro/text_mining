#include "../trie/node.hh"
#include "../trie/nodes.hh"
#include <iostream>
#include <string>
#include "search.hh"

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

    //if (std::stoi(diff) == 0)
    //  node3.search_word(word);

    auto results = trie::search(node3, word, std::stoi(diff));
    if (! results->empty())
      for (size_t i = 0; i < results->size(); i++)
        std::cout << "["
          << results->at(i).first
          << ": "
          << results->at(i).second
          << "]" << std::endl;
    else
      std::cerr << "resultat vide" << std::endl;

    //[{"word":"dimension","freq":6912651,"distance":0}, ... ]
    /*std::uint32_t freq = node3.search_word(word);
      if (freq != 0)
      result += "{\"word\":\"" + word
      + "\",\"freq\":" + std::to_string(freq)
      + ",\"distance\":" + diff + "}";

      else
      {
      auto res = node3.find_word(word, std::stoi(diff));
      for (std::size_t i = 0; i < res.size(); ++i)
      {
      if (std::get<1>(res[i]) != 0)
      result += "{\"word\":\"" + std::get<0>(res[i])
      + "\",\"freq\":" + std::to_string(std::get<1>(res[i]))
      + ",\"distance\":" + std::to_string(std::stoi(diff) - std::get<2>(res[i])) + "}";
      }
      }*/



  }

  //if (!result.empty())
  //  std::cout << "[" << result << "]" << std::endl;
  // node3.dump();
  std::cerr << sizeof (node3) << std::endl;
  //std::cerr << node3.search_word(argv[2]) << std::endl;

  return 0;
}
