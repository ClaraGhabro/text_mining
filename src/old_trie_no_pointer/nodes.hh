#pragma once

#include "node.hh"

namespace trie
{

std::size_t add_node();

Node* get_node(std::size_t size);

void serialize_nodes(const char* file);

Node* deserialize_nodes(const char* file);
}
