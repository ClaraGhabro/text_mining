#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <fstream>
#include <iostream>

namespace trie
{
/**
 * \class Node node.hh
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

  /**
   * \struct element node.hh
   *
   * \brief Bitfield structure that contains a letter, a word frequence, that
   * can be empty, and an index. It describe the children of a node. The index
   * is the position of this child in the vector containing all the nodes.
   */
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

  /**
   * \brief Search if a word is in the trie.
   *
   * \param word the word to search
   * \param index which letter of the word is being searched
   */
  uint32_t search_word(const std::string& word, std::size_t index = 0);

  /**
   * \brief Display all words in the trie.
   *
   * \param str is empty at the first call, accumulate the letters of the word
   * then
   */
  void dump(const std::string& str = "");

  /**
   * \brief Serialize the data contained in the current node
   *
   * \param out_stream the open stream where the function will write the datas
   */
  void write_node(std::ofstream& out_stream) const;

  /**
   * \brief Set the frequency of a word on the edge to its last node, using its
   * last letter.
   *
   * \param freq the word frequency
   * \param letter the last letter of the word
   */
  void set_frequence(unsigned int freq, const char letter);

  /**
   * \brief Add a children to the current node using its letter, its index in
   * the vector and its frequency
   *
   * \param letter the letter to insert
   * \param index the index of the node in the vector
   * \param freq frequency of the inserted word
   */
  void add_children(char letter, std::uint32_t index, std::uint32_t freq = 0);

  /**
   * \brief Add a children to the current node using struct element
   *
   * \param elt structure containing the letter, the index and the frequency of
   * the word to insert
   */
  void add_children(struct element elt);

private:
  /**
   * \brief Sort the child in aphabetic order
   */
  void sort_node();

  std::vector<element> children{}; /*!< Vector containing the children of the current node*/
};
} // namespace trie
