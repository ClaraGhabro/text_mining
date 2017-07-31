#pragma once

#include <string>
#include <vector>
#include "trie/node.hh"

namespace trie
{
/**
 * \brief Calculate the levenshtein distance between word and dico_word
 *
 * \param word the word to correct
 * \param dico_word the word finded in the trie
 * \param results contains the words, there frequence and the distance to the input word
 * \param max_cost maximal distance between ths input word, and word find in the trie
 * \param frequence the frenquency of dico_word
 * \param
 */
void levensthein_dist(const std::string& word,
                     const std::string& dico_word,
                     std::vector<std::tuple<std::string, std::uint32_t, int>> *results,
                     int max_cost,
                     std::uint32_t frequence);

/**
 * \brief got through the trie to find words, and calculate leveshtein distance between them and the input word
 *
 * \param node The root of the trie
 * \param word the word to correct
 * \param results contains the words, there frequence and the distance to the input word
 * \param max_cost maximal distance between ths input word, and word find in the trie
 * \param acc_word the suit of letter composing a word
 */
void search_on_word(const Node& node,
                    const std::string& word,
                    std::vector<std::tuple<std::string, std::uint32_t, int>>* results,
                    int max_cost,
                    const std::string& acc_word = "");

/**
 * \brief launch the function that will search for words in the trie, and that whil calculate distance
 *
 * \param node The root of the trie
 * \param word the word to correct
 * \param max_cost maximal distance between ths input word, and word find in the trie
 */
std::unique_ptr<std::vector<std::tuple<std::string, std::uint32_t, int>>>
search(const Node& node, const std::string& word, int max_cost);
}
