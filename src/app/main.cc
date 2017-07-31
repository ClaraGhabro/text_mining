#include "../trie/node.hh"
#include "../trie/nodes.hh"
#include <iostream>
#include <string>
#include "search.hh"
#include <algorithm>

/**
 * \brief TextMiningApp main
 */


int strCmp(const std::string str1, const std::string str2)
{
  for (size_t i = 0; i < str1.size(); i++)
  {
    if (i == str2.size())
      return -1;
    if (str2[i] != str1[i])
      return str1[i] > str2[i] ? -1 : 1;
  }
  return str1.size() < str2.size() ? 1 : 0;
}

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

    auto results = trie::search(node3, word, std::stoi(diff));
    if (! results->empty())
    {
      // sort by ascending distance, descending frequence and lexicographique
      std::sort(results->begin(), results->end(),
            [](const auto& elt1, const auto& elt2) {
            return std::get<2>(elt1) < std::get<2>(elt2) ||
                  (std::get<2>(elt1) == std::get<2>(elt2) && std::get<1>(elt1) > std::get<1>(elt2)) ||
                  (std::get<2>(elt1) == std::get<2>(elt2) && std::get<1>(elt1) == std::get<1>(elt2) &&
                  strCmp(std::get<0>(elt1), std::get<0>(elt2)) == 1);
            });

      std::cout << "[";
      unsigned i = 0;
      for (; i < results->size() - 1; ++i)
        std::cout << "{\"word\":\"" << std::get<0>(results->at(i))
                  << "\",\"freq\":" << std::get<1>(results->at(i))
                  << ",\"distance\":" << std::get<2>(results->at(i)) << "},";
      std::cout << "{\"word\":\"" << std::get<0>(results->at(i))
                << "\",\"freq\":" << std::get<1>(results->at(i))
                << ",\"distance\":" << std::get<2>(results->at(i)) << "}]"
                << std::endl;
    }
    else
      std::cerr << "Pas de resultat" << std::endl;

  }
  return 0;
}
