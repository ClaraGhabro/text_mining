#pragma once

#include "node.hh"

namespace trie
{
/**
 * \fn add_node
 *
 * \brief Add a node in the vector containing all nodes
 */
std::size_t add_node();

/**
 * \fn get_node
 *
 * \brief Return a node using a given index.
 *
 * \param index The index of the node to return
 */
Node& get_node(std::size_t index);

/**
 * \fn serialize_node
 *
 * \brief Serialiaze nodes in a file
 *
 * \param file where the nodes will be serialized
 */
void serialize_nodes(const char* file);

/**
 * \f deserialize_node
 *
 * \brief Deserialiaze a file and put its content in a vector of node
 *
 * \param file where the content will be read
 */
Node& deserialize_nodes(const char* file);
}
