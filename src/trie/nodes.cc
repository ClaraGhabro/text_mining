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
    nodes.reserve(8000000);

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

  std::uint8_t children_size = 0;
  trie::Node::element elt ;

  while (in_stream)
  {
    std::size_t node_index = add_node();
    in_stream.read(reinterpret_cast<char*>(&children_size), sizeof (std::uint8_t));
    // std::cerr << "chilldren_size: " << static_cast<int>(children_size) << std::endl;

    auto current_node = get_node(node_index);

    for (std::size_t i = 0; i < children_size; ++i)
    {
      in_stream.read(reinterpret_cast<char*>(&elt), sizeof (elt));
      // std::cerr << "letter: " << letter<< std::endl;
      current_node->add_children(elt);
    }
  }

  // node->read_node(in);
  in_stream.close();

  return get_node(1);

}

}
