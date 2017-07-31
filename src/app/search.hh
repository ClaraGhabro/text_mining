#pragma once

#include <string>
#include <vector>
#include "trie/node.hh"

namespace trie
{
void levensthein_dist(const std::string& word,
                     const std::string& dico_word,
                     std::vector<std::pair<std::string, int>> *results,
                     int max_cost);

void search_on_word(const Node& node,
                    const std::string& word,
                    std::vector<std::pair<std::string, int>>* results,
                    int max_cost, const std::string& acc__word = "");

std::unique_ptr<std::vector<std::pair<std::string, int>>>
search(Node& node, const std::string& word, int max_cost);
}
