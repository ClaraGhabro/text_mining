#include "trie.hh"

Node::Node()
    : children{ nullptr }
    , is_word_end(false)
{
}

void Node::insert_word(const std::string& word, unsigned index)
{
  if (index == word.size())
    return;

  if (children[word[index]] == nullptr)
    children[word[index]] = std::make_unique<Node>();

  children[word[index]]->insert_word(word, index + 1);
  
}

