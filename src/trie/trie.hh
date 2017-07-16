#pragma once

#include <array>
#include <cstdint>
#include <memory>

class Node
{
public:
  Node();
  void insert_word(const std::string& word, unsigned index = 0);
  void print_trie(const std::string& str);

private:
  static constexpr std::size_t kalphabet_size = 128;
  std::array<std::unique_ptr<Node>, kalphabet_size> children;
  bool is_word_end;
};
