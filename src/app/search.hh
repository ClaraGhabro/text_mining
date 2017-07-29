#pragma once

#include <string>
#include <vector>
#include "../trie/node.hh"

namespace trie
{
  void searchRecursive(Node& node,
                       char letter,
                       const std::string& word,
                       std::vector<int>& previousRow,
                       std::vector<std::pair<std::string, int>> &results,
                       int maxCost,
                       const std::string& curWord);

  std::vector<std::string>& search(Node &node, const std::string& word, int maxCost);
}
