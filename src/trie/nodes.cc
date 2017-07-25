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
  static std::vector<std::shared_ptr<Node>> nodes{};
  return nodes;
}
}

std::size_t add_node()
{
  auto& nodes = nodes_get();
  nodes.emplace_back(std::make_shared<Node>());
  return nodes.size();
}

std::shared_ptr<Node> get_node(std::size_t index)
{
  auto& nodes = nodes_get();
  assert(index <= nodes.size());
  return nodes.at(index - 1);
}

void serialize_nodes(const char* file)
{
  std::ofstream out;
  out.open(file, std::ios::app | std::ios::binary);
  auto& nodes = nodes_get();
  for (const auto& node_ptr : nodes)
    node_ptr->write_node(out);
  out.close();
}

void deserialize_nodes(const char* file)
{
  std::ifstream in;
  in.open(file, std::ios::app | std::ios::binary);
  auto node = get_node(add_node());
  node->read_node(in);
  in.close();

}

}
