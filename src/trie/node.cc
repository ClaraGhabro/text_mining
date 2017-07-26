#include "node.hh"

#include "nodes.hh"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace trie
{
void Node::insert_word(const std::string& word, int frequence, unsigned index)
{

  char searched_char = word[index];

  const auto elt = std::find_if(children.begin(),
                                children.end(),
                                [searched_char](const auto& elt) {
                                  return elt.letter == searched_char;
                                });

  if (elt == children.end())
  {
    std::size_t new_index = add_node();
    add_children(searched_char, new_index);
    sort_node();
    if (index == word.size() - 1)
    {
      set_frequence(frequence, searched_char);
      return;
    }
    get_node(new_index).insert_word(word, frequence, index + 1);
  }
  else
  {
    if (index == word.size() - 1)
    {
      set_frequence(frequence, searched_char);
      return;
    }
    get_node(elt->son_idx).insert_word(word, frequence, index + 1);
  }
}

bool Node::search_word(const std::string& word, std::size_t index)
{
  char searched_char = word[index];

  const auto& elt = std::find_if(children.begin(),
                                 children.end(),
                                 [searched_char](const auto& elt) {
                                   return elt.letter == searched_char;
                                 });

  if (elt == children.end())
    return false;

  if (index == word.size())
    return true;

  return get_node(elt->son_idx).search_word(word, index + 1);
}

void Node::dump(const std::string& str)
{
  for (std::size_t i = 0; i < children.size(); ++i)
  {
    get_node(children[i].son_idx).dump(str + children[i].letter);
  }

  for (std::size_t i = 0; i < children.size(); ++i)
    if (children[i].word_frequence)
      std::cerr << str << '\n';
}

void Node::write_node(std::ofstream& out_stream) const
{
  std::uint8_t temp = static_cast<std::uint8_t>(children.size());
  out_stream.write(reinterpret_cast<const char*>(&temp), sizeof (temp));
  for (const auto& elt : children)
    out_stream.write(reinterpret_cast<const char*>(&elt), sizeof (elt));
}

void Node::set_frequence(unsigned int freq, const char letter)
{
  for (std::size_t i = 0; i < children.size(); ++i)
    if (children[i].letter == letter)
    {
      children[i].word_frequence = freq;
      return;
    }
}

void Node::add_children(struct element elt)
{
  children.emplace_back(elt);
  if (children.capacity() > children.size() + 2)
    children.shrink_to_fit();
}

void Node::add_children(char letter, std::uint32_t index, std::uint32_t freq)
{
  children.emplace_back(element{ letter, freq, index });
  if (children.capacity() > children.size() + 2)
    children.shrink_to_fit();
}

void Node::sort_node()
{
  std::sort(children.begin(),
            children.end(),
            [](const auto& elt1, const auto& elt2) {
              return elt1.letter < elt2.letter;
            });
}
}
