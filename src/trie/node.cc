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
    children.emplace_back(std::make_pair(searched_char, new_index));
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
  for (std::size_t i = 0; i < children.size(); ++i)
  {
    get_node(children[i].second)->dump(str + children[i].first);
  }

  if (word_frequence)
    std::cerr << str << '\n';
}

void Node::write_node(std::ofstream& out_stream) const
{
  /* FIXME:
   * write each elements one by one. Don't forget to specify the size
   * finaly, write frequency */
  std::uint8_t temp = static_cast<std::uint8_t>(children.size());
  out_stream.write(reinterpret_cast<const char*>(&word_frequence), sizeof(word_frequence));
  out_stream.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
  for (const auto& pair : children)
  {
    out_stream.put(pair.first);
    out_stream.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
  }
}

void Node::read_node(std::ifstream& in_stream) const
{
  unsigned int word_freq = 0;
  std::uint8_t children_size = 0;
  char letter = 'c';
  std::size_t index = 0;
  while (in_stream)
  {
    in_stream.read(reinterpret_cast<char*>(&word_freq), sizeof (unsigned int));
    std::cerr << "word freq: " << word_freq << std::endl;
    in_stream.read(reinterpret_cast<char*>(&children_size), sizeof (std::uint8_t));
    std::cerr << "chilldren_size: " << reinterpret_cast<std::uint8_t>(children_size) << std::endl;
    for (std::size_t i = 0; i < children_size; ++i)
    {
      in_stream.read(reinterpret_cast<char*>(&letter), sizeof (char));
      std::cerr << "letter: " << letter<< std::endl;
      in_stream.read(reinterpret_cast<char*>(&index), sizeof (std::size_t));
      std::cerr << "index: " << index << std::endl;
    }
  }
  
  in_stream.read(reinterpret_cast<char*>(&word_freq), sizeof (unsigned int));
  std::cerr << "word freq: " << word_freq << std::endl;
  in_stream.read(reinterpret_cast<char*>(&children_size), sizeof (std::uint8_t));
  std::cerr << "chilldren_size: " << children_size << std::endl;
  in_stream.read(reinterpret_cast<char*>(&letter), sizeof (char));
  std::cerr << "letter: " << letter<< std::endl;
  in_stream.read(reinterpret_cast<char*>(&index), sizeof (std::size_t));
  std::cerr << "index: " << index << std::endl;

}


void Node::sort_node()
{
  // std::sort(children.begin(), children.end(),
  // [](const auto& pair1, const auto& pair2)
  // { return pair1.first < pair2.first; });
}
}
