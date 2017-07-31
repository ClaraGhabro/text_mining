#include "search.hh"

#include "trie/nodes.hh"
#include <algorithm>
#include <numeric>


namespace trie
{

void levenshtein_dist(const std::string& word,
                      const std::string& dico_word,
                      std::vector<std::tuple<std::string, std::uint32_t, int>>* results,
                      int max_cost,
                      std::uint32_t frequence
                     )
{

  const int nb_column = word.size() + 1;
  const int nb_row = dico_word.size() + 1;

  std::vector<int> current_row(nb_column);
  std::iota(current_row.begin(), current_row.end(), 0);

  for (auto row = 1; row < nb_row; ++row)
  {
    auto prev_row = current_row;
    current_row.clear();
    current_row.emplace_back(prev_row.at(0) + 1);

    for (auto col = 1; col < nb_column; ++col)
    {
      const int insert_cost = current_row.at(col - 1) + 1;
      const int delete_cost = prev_row.at(col) + 1;
      int replace_cost = 0;

      // std::cerr << "current word letter:      " << word[col - 1] << '\n';
      // std::cerr << "current dico word letter: " << dico_word[row - 1] << '\n';
      bool diff_letters = word[col - 1] != dico_word[row - 1];
      bool inversed_letters = (word[col - 1] == dico_word[row]
                              && word[col] == dico_word[row - 1]
                              && word[col] != word[col - 1]);

      if (diff_letters || inversed_letters)
        replace_cost = prev_row.at(col - 1) + 1;
      else
        replace_cost = prev_row.at(col - 1);

      current_row.emplace_back(
          std::min(insert_cost, std::min(delete_cost, replace_cost)));
      // if (current_row.back() > max_cost)
        // return;
    }
  }

  if (current_row.back() <= max_cost)
  {
    results->emplace_back(std::make_tuple(dico_word, frequence, current_row.back()));
  }
}

void search_on_word(const Node& node,
                    const std::string& word,
                    std::vector<std::tuple<std::string, std::uint32_t, int>>* results,
                    int max_cost,
                    const std::string& acc_word)
{
  if (word.size() + max_cost < acc_word.size())
    return;

  for (const auto& child : node.get_children())
  {
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
                       //freq_return);
     if (results->size() == 1 && max_cost == 0)
       return;
    }

    // search_on_word(node, word, results, max_cost, acc_word + child.letter);
    search_on_word(get_node(child.son_idx), word, results, max_cost, acc_word + child.letter);
  }


}

std::unique_ptr<std::vector<std::tuple<std::string, std::uint32_t, int>>>
search(const Node &node, const std::string& word, int max_cost)
{
  auto results = std::make_unique<std::vector<std::tuple<std::string, std::uint32_t, int >>>();
  
  
  search_on_word(node, word, results.get(), max_cost);
  
  return results;
}

}
