#pragma once

#include <string>
#include <vector>
#include "trie/node.hh"

namespace trie
{
void search_ecursive(Node& node,
                     char letter,
                     const std::string& word,
                     std::vector<int>& previous_row,
                     std::vector<std::pair<std::string, int>> *results,
                     int max_cost,
                     const std::string& cur_word);

std::vector<std::pair<std::string, int>>* search(Node& node,
                                                 const std::string& word,
                                                 int max_cost);
}
