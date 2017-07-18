#include "trie.hh"

#include <iostream>

namespace trie
{
Node::Node()
    : children{ nullptr }
    //, is_word_end(false)
{
}

void Node::insert_word(const std::string& word, int frequence, unsigned index)
{
  if (index == word.size())
  {
    //is_word_end = true;
    word_frequence = frequence;
    return;
  }

  if (children[word[index]] == nullptr)
    children[word[index]] = std::make_unique<Node>();

  children[word[index]]->insert_word(word, frequence, index + 1);
  
}

void Node::print_trie(const std::string& str)
{
  for (std::size_t i = 0; i < children.size(); ++i)
  {
    if (children[i] != nullptr)
      children[i]->print_trie(str + static_cast<char>(i));
  }

  if (word_frequence)
    std::cerr << str << '\n';
}

}
