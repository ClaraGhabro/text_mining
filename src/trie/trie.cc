#include "trie.hh"

#include <iostream>

Node::Node()
    : children{ nullptr }
    , is_word_end(false)
{
}

void Node::insert_word(const std::string& word, unsigned index)
{
  if (index == word.size())
  {
    is_word_end = true;
    return;
  }

  if (children[word[index]] == nullptr)
    children[word[index]] = std::make_unique<Node>();

  children[word[index]]->insert_word(word, index + 1);
  
}

void Node::print_trie(const std::string& str)
{
  for (std::size_t i = 0; i < children.size(); ++i)
  {
    if (children[i] != nullptr)
      children[i]->print_trie(str + static_cast<char>(i));
  }

  if (is_word_end)
    std::cout << str << '\n';
}
