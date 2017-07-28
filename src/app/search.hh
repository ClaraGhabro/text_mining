#pragma once

#include <string>
#include <vector>
#include "../trie/node.hh"

namespace trie
{
  void searchRecursive(Node node, char letter, std::string word, std::vector<int> previousRow,
                        std::vector<std::string> results, int maxCost);
  std::vector<std::string>& search(Node &node, std::string word, int maxCost);
}
