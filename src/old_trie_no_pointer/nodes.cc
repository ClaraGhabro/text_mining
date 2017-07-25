#include "nodes.hh"

#include <cassert>
#include <fstream>
#include <memory>
#include <vector>

namespace trie
{
namespace
{
auto& nodes_get()
{
  static std::vector<std::unique_ptr<Node>> nodes{};
  return nodes;
}
}

std::size_t add_node()
{
  auto& nodes = nodes_get();
  nodes.emplace_back(std::make_unique<Node>());
  if (nodes.empty())
    nodes.reserve(3000000);

  return nodes.size();
}

Node* get_node(std::size_t index)
{
  auto& nodes = nodes_get();
  assert(index <= nodes.size());
  return nodes.at(index - 1).get();
}

void serialize_nodes(const char* file)
{
  auto& nodes = nodes_get();
  std::cerr << nodes.size() << '\n';
  std::ofstream out;
  out.open(file, std::ios::binary);
  for (const auto& node_ptr : nodes)
    node_ptr->write_node(out);
  out.close();
}

Node* deserialize_nodes(const char* file)
{
  std::ifstream in_stream;
  in_stream.open(file, std::ios::binary);

  unsigned int word_freq = 0;
  std::uint8_t children_size = 0;
  char letter = '\0';
  std::size_t index = 0;

  while (in_stream)
  {
    std::size_t node_index = add_node();
    in_stream.read(reinterpret_cast<char*>(&word_freq), sizeof (unsigned int));
    // std::cerr << "word freq: " << word_freq << std::endl;
    in_stream.read(reinterpret_cast<char*>(&children_size), sizeof (std::uint8_t));
    // std::cerr << "chilldren_size: " << static_cast<int>(children_size) << std::endl;

    auto current_node = get_node(node_index);
    current_node->set_frequence(word_freq);

    for (std::size_t i = 0; i < children_size; ++i)
    {
      in_stream.read(reinterpret_cast<char*>(&letter), sizeof (char));
      // std::cerr << "letter: " << letter<< std::endl;
      in_stream.read(reinterpret_cast<char*>(&index), sizeof (std::size_t));
      // std::cerr << "index: " << index << std::endl;
      current_node->add_children(letter, index);
    }
  }

  // node->read_node(in);
  in_stream.close();

  return get_node(1);

}

}
