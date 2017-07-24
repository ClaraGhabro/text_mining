#include "trie.hh"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace trie
{
Node::Node()
    : children{}
{
}

void Node::insert_word(const std::string& word, int frequence, unsigned index)
{
  if (index == word.size())
  {
    word_frequence = frequence;
    return;
  }

  char searched_char = word[index];
  const auto& elt = std::find_if(children.begin(), children.end(),
                                [searched_char](const auto& pair_elt)
               { return pair_elt.first == searched_char; });

  if (elt == children.end())
  {
    children.emplace_back(word[index], std::make_unique<Node>());
    children.back().second->insert_word(word, frequence, index + 1);
  }
  else
    elt->second->insert_word(word, frequence, index + 1);
}

void Node::print_trie(const std::string& str)
{
  sort_node();
  for (std::size_t i = 0; i < children.size(); ++i)
  {
    children[i].second->print_trie(str + children[i].first);
  }

  if (word_frequence)
    std::cerr << str << '\n';
}


void Node::write_node(std::ofstream& out_stream)
{
  out_stream.write(reinterpret_cast<const char*>(this), sizeof (trie::Node));
  for (std::size_t i = 0; i < children.size(); ++i)
  {
      children[i].second->write_node(out_stream);
  }
}

void Node::sort_node()
{
  std::sort(children.begin(), children.end(),
            [](const auto& pair1, const auto& pair2)
            { return pair1.first < pair2.first; });
}


}
