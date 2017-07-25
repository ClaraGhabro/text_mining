#include "node.hh"

#include "nodes.hh"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace trie
{
void Node::insert_word(const std::string& word, int frequence, unsigned index)
{
  if (index == word.size())
  {
    word_frequence = frequence;
    return;
  }

  char searched_char = word[index];

  const auto elt = std::find_if(children.begin(),
                                children.end(),
                                [searched_char](const auto& pair_elt) {
                                  return pair_elt.first == searched_char;
                                });

  if (elt == children.end())
  {
    std::size_t new_index = add_node();
    add_children(searched_char, new_index);
    sort_node();
    get_node(new_index)->insert_word(word, frequence, index + 1);
  }
  else
    get_node(elt->second)->insert_word(word, frequence, index + 1);
}

bool Node::search_word(const std::string& word, std::size_t index)
{
  char searched_char = word[index];

  const auto& elt = std::find_if(children.begin(),
                                 children.end(),
                                 [searched_char](const auto& pair_elt) {
                                   return pair_elt.first == searched_char;
                                 });

  if (elt == children.end())
    return false;

  if (index == word.size())
    return true;

  return get_node(elt->second)->search_word(word, index + 1);
}

void Node::dump(const std::string& str)
{
  // for (std::size_t i = 0; i < children.size(); ++i)
  // {
    // get_node(children[i].second)->dump(str + children[i].first);
  // }
//
  // if (word_frequence)
    // std::cerr << str << '\n';
}

void Node::write_node(std::ofstream& out_stream) const
{
  // std::uint8_t temp = static_cast<std::uint8_t>(children.size());
  // out_stream.write(reinterpret_cast<const char*>(&word_frequence),
                   // sizeof(word_frequence));
  // out_stream.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
  // for (const auto& pair : children)
  // {
    // out_stream.put(pair.first);
    // out_stream.write(reinterpret_cast<const char*>(&pair.second),
                     // sizeof(pair.second));
  // }
}

void Node::set_frequence(unsigned int freq)
{
  // word_frequence = freq;
}

void Node::add_children(char letter, std::size_t index)
{
  children.emplace_back(std::make_pair(letter, index));
  if (children.capacity() > children.size() + 2)
    children.shrink_to_fit();
}

// std::size_t Node::size_node(std::size_t size)
// {
// for (std::size_t i = 0; i < children.size(); ++i)
// {
// return get_node(children[i].second)->size_node(size + sizeof(this));
// }
//
//
// }

void Node::sort_node()
{
  std::sort(children.begin(),
            children.end(),
            [](const auto& pair1, const auto& pair2) {
              return pair1.first < pair2.first;
            });
}
}
