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

  const auto elt = std::find_if(children.begin(), children.end(),
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

uint32_t Node::search_word(const std::string& word, std::size_t index)
{
  char searched_char = word[index];

  const auto& elt = std::find_if(children.begin(), children.end(),
                                 [searched_char](const auto& elt) {
                                 return elt.letter == searched_char;
                                 });

  if (elt == children.end())
    return 0;

  if (index == word.size() - 1)
    return elt->word_frequence;

  return get_node(elt->son_idx).search_word(word, index + 1);
}

bool Node::is_shorter_or_longer(std::size_t size_word, std::size_t index, int dist)
{
  return (index >= size_word - dist && index <= size_word + dist);
}

std::vector<std::tuple<std::string, uint32_t, int>>
Node::find_word(const std::string& word, int dist, const std::string& finded_word,
                std::size_t index)
{
  static std::vector<std::tuple<std::string, std::uint32_t, int>> words_vec{};
  static std::size_t current_deep = 0;
  char searched_char = word[index];

  // const auto& elt = std::find_if(children.begin(), children.end(),
  // [searched_char](const auto& elt) {
  // return elt.letter == searched_char;
  // });

  if (current_deep++ == word.size() - 1 + dist)
    return words_vec;
  // a good word

  for (std::size_t i = 0; i < children.size() + dist; ++i)
  {
    if (is_shorter_or_longer(word.size(), finded_word.size() + 1, dist)
        && children[i].word_frequence)
      // the finded word is shorter or longer than the given one
    {
      words_vec.emplace_back(std::make_tuple(finded_word + children[i].letter,
                                             static_cast<std::uint32_t>(children[i].word_frequence),
                                             dist));
    }



    if (children[i].letter == searched_char)
    {
      // the finded letter is the good one
      return get_node(children[i].son_idx).find_word(word, dist,
                                                     finded_word + children[i].letter,
                                                     index + 1);
    }
    if (children[i].letter == word[index - 1]
        && finded_word[index - 1] == searched_char)
    {
      // the finded letter and the previous are a swap of the original word
      return get_node(children[i].son_idx).find_word(word, dist,
                                                     finded_word + children[i].letter,
                                                     index + 1);
    }
    else
    {
      return get_node(children[i].son_idx).find_word(word, dist - 1,
                                                     finded_word + children[i].letter,
                                                     index + 1);
    }


  }

  return words_vec;
}

void Node::dump(const std::string& str)
{
  // std::cerr << "children size: " << children.size() << '\n';
  for (std::size_t i = 0; i < children.size(); ++i)
  {
    // std::cerr << "current child index: " << i << '\n';
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

void Node::set_frequence(unsigned int freq, char letter)
{
  for (std::size_t i = 0; i < children.size(); ++i)
    if (children[i].letter == letter)
    {
      children[i].word_frequence = freq;
      return;
    }
}

void Node::add_children(const struct element& elt)
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

const std::vector<Node::element>& Node::get_children()
{
  return children;
}

const std::string& Node::get_word(const std::string& str)
{

  // std::cerr << "children size: " << children.size() << '\n';
  for (std::size_t i = 0; i < children.size(); ++i)
  {
    // std::cerr << "current child index: " << i << '\n';
    return get_node(children[i].son_idx).get_word(str + children[i].letter);
  }

  for (std::size_t i = 0; i < children.size(); ++i)
    if (children[i].word_frequence)
      return str;

  return str;
}

}
