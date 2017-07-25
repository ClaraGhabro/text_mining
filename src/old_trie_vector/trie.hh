#pragma once

#include <vector>
#include <cstdint>
#include <memory>

namespace trie
{
/**
 * \class Node
 * \brief Réepresente a node of the trie
 */
class Node
{
public:

  /**
   * \brief Create a node with no children
   */
  Node();

  /**
   * \brief Insert a word in the trie. If the word is already in the list, or
   * existsts as a subword, don't do anything.
   *
   * \param word the word to insert
   * \param index how many letters are already inserted in the trie, 0 if not specified
   */
  void insert_word(const std::string& word, int frequence, unsigned index = 0);

  /**
   * \brief Display all words in the trie.
   *
   * \param str is empty at the first call, accumulate the letters of the word then
   */
  void print_trie(const std::string& str = "");

  // std::array<std::unique_ptr<Node>, std::size_t> get_children();
  //
  void write_node(std::ofstream& stream);

  /**
   * \brief Sort the child in aphabetic order
   */
  void sort_node();
  

private:
  std::vector<std::pair<char, std::unique_ptr<Node>>> children; /*!< a value is false if the character is not containend in the trie, point to a node is the characher is in the trie >*/
  int word_frequence = 0; /*!< zero if the node is not the end of a word, != 0 if the node represent the end of a word >*/

};
} // namespace trie
