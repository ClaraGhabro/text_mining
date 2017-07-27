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
  
  auto& node3 = trie::deserialize_nodes(argv[1]);
  std::string reading;
  std::string diff;
  std::string word;
  std::string result{};

  while (std::cin >> reading)
  {
    std::cin >> diff >> word;
    if (reading.empty())
      break;

    std::cerr << "reading: " << reading
              << ", diff: " << diff
              << ", word: " << word << std::endl;

    if (std::stoi(diff) == 0)
      node3.search_word(word);

//[{"word":"dimension","freq":6912651,"distance":0}, ... ]
    std::uint32_t freq = node3.search_word(word);
    if (freq != 0)
      result += "{\"word\":\"" + word
              + "\",\"freq\":" + std::to_string(freq)
              + ",\"distance\":" + diff + "}";

    else
    {
      auto res = node3.find_word(word, std::stoi(diff));
      for (std::size_t i = 0; i < res.size(); ++i)
      {
        if (res[i].second != 0)
          result += "{\"word\":\"" + res[i].first
                  + "\",\"freq\":" + std::to_string(res[i].second)
                  + ",\"distance\":" + diff + "}";
      }
    }

  }
  
  if (!result.empty())
    std::cout << "[" << result << "]" << std::endl;
  // node3.dump();
  std::cerr << sizeof (node3) << std::endl;
  //std::cerr << node3.search_word(argv[2]) << std::endl;

  return 0;
}
