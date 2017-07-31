#include "search.hh"

#include "trie/nodes.hh"
#include <algorithm>


namespace trie {

// namespace
// {
// void sort_vect(std::vector<int>& vect)
// {
  // std::sort(vect.begin(), vect.end(), [](const auto& elt1, const auto& elt2) {
    // return elt1 < elt2;
    // });
// }
// }

void levenshtein_dist(const std::string& word,
                      const std::string& dico_word,
                      std::vector<std::tuple<std::string, std::uint32_t, int>>* results,
                      int max_cost,
                      std::uint32_t frequence
                     )
{

  const int nb_column = word.size() + 1;
  const int nb_row = dico_word.size() + 1;

  std::vector<int> current_row{};
  current_row.emplace_back(0);
  for (auto i = 1; i < nb_column; ++i)
    current_row.emplace_back(current_row.at(i - 1) + 1);

  for (auto row = 1; row < nb_row; ++row)
  {
    auto prev_row = current_row;
    current_row.clear();
    current_row.emplace_back(prev_row.at(0) + 1);

    for (auto col = 1; col < nb_column; ++col)
    {
      int insert_cost = current_row.at(col - 1) + 1;
      int delete_cost = prev_row.at(col) + 1;
      int replace_cost = 0;

      // std::cerr << "current word letter:      " << word[col - 1] << '\n';
      // std::cerr << "current dico word letter: " << dico_word[row - 1] << '\n';
      if (word[col - 1] != dico_word[row - 1])
      {
        replace_cost = prev_row.at(col - 1) + 1;
        // std::cerr << "replace cost if diff: " << replace_cost << '\n';
      }
      else if (word[col - 1] == dico_word[row] && word[col] == dico_word[row - 1])
        replace_cost = prev_row.at(col - 1) + 1;
      else
      {
        replace_cost = prev_row.at(col - 1);
        // std::cerr << "replace cost if same: " << replace_cost << '\n';
      }

      current_row.emplace_back(
          std::min(insert_cost, std::min(delete_cost, replace_cost)));
      // if (current_row.back() > max_cost)
        // return;
    }
  }

  if (current_row.back() <= max_cost)
  {
    // std::cerr << "frequence of finded word: " << frequence << '\n';
    results->emplace_back(std::make_tuple(dico_word, frequence, current_row.back()));
  }


}


void search_on_word(const Node& node,
                    const std::string& word,
                    std::vector<std::tuple<std::string, std::uint32_t, int>>* results,
                    int max_cost,
                    const std::string& acc_word)
{
  for (const auto& child : node.get_children())
  {
    if (word.size() + max_cost == acc_word.size())
      return;

    if (child.word_frequence != 0)
    {
      // std::cerr << "current word: " << acc_word + child.letter << '\n';
     // auto& root_node = get_node(1);
     // std::uint32_t freq_return = root_node.search_word(acc_word + child.letter);
     // if (freq_return)
        // std::cerr << "frequence of current word: " << acc_word + child.letter
                  // << " " << child.word_frequence << '\n';
        // std::cerr << "return frequence du search: " << freq_return << '\n';
        levenshtein_dist(word, acc_word + child.letter, results, max_cost,
                         child.word_frequence);
    }

    search_on_word(node, word, results, max_cost, acc_word + child.letter);
  }


}

std::unique_ptr<std::vector<std::tuple<std::string, std::uint32_t, int>>>
search(Node &node, const std::string& word, int max_cost)
{
  auto results = std::make_unique<std::vector<std::tuple<std::string, std::uint32_t, int >>>();
  
  
  search_on_word(node, word, results.get(), max_cost);
  
  return results;
}

}
