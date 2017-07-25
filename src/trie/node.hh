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
class Node final
{
public:
  Node() = default;
  ~Node() = default;
  Node(const Node&) = delete;
  Node(Node&&) noexcept = default;
  Node& operator=(const Node&) = delete;
  Node& operator=(Node&&) noexcept = default;

  struct element
  {
    char letter : 8;
    std::uint32_t word_frequence : 24;
    std::uint32_t son_idx : 32;
  };
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

  void set_frequence(unsigned int freq, const char letter);
  void add_children(char letter, std::uint32_t index, std::uint32_t freq = 0);
  void add_children(struct element elt);

private:
  /**
   * \brief Sort the child in aphabetic order
   */
  void sort_node();


  std::vector<element> children{};
};
} // namespace trie
