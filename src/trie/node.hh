#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <fstream>
#include <iostream>

namespace trie
{
/**
 * \class Node
 * \brief Réepresente a node of the trie
 */
class Node
{
public:
  Node() = default;
  ~Node() = default;
  Node(const Node&) = delete;
  Node(Node&&) noexcept = default;
  Node& operator=(const Node&) = delete;
  Node& operator=(Node&&) noexcept = default;

  /**
   * \brief Insert a word in the trie. If the word is already in the list, or
   * existsts as a subword, don't do anything.
   *
   * \param word the word to insert
   * \param index how many letters are already inserted in the trie, 0 if not
   * specified
   */
  void insert_word(const std::string& word, int frequence, unsigned index = 0);

  bool search_word(const std::string& word, std::size_t index = 0);

  /**
   * \brief Display all words in the trie.
   *
   * \param str is empty at the first call, accumulate the letters of the word
   * then
   */
  void dump(const std::string& str = "");

  void write_node(std::ofstream& out_stream) const;
  void read_node(std::ifstream& in_stream) const;

  void set_frequence(unsigned int freq);
  void add_children(char letter, std::size_t index);

private:
  /**
   * \brief Sort the child in aphabetic order
   */
  void sort_node();

  std::vector<std::pair<char, std::size_t>> children{};
  unsigned int word_frequence = 0; /*!< zero if the node is not the end of a word, != 0 otherwise >*/
};
} // namespace trie
