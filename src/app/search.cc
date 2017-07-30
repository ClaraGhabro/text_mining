#include "search.hh"

#include "trie/nodes.hh"
#include <algorithm>


namespace trie {

namespace
{
void sort_vect(std::vector<int>& vect)
{
  std::sort(vect.begin(), vect.end(), [](const auto& elt1, const auto& elt2) {
    return elt1 < elt2;
    });
}
}

void search_recursive(const Node& node,
                     char letter,
                     const std::string& word,
                     const std::vector<int>& previousRow,
                     std::vector<std::pair<std::string, int>>* results,
                     int maxCost,
                     const std::string& curWord)
{

  const int nbColumn = word.size();
  std::vector<int> currentRow{};
  currentRow.emplace_back(previousRow[0] + 1);

  for (int i = 1; i < nbColumn; i++)
  {
    int insertCost = currentRow[i - 1] + 1;
    int deleteCost = previousRow[i] + 1;
    int replaceCost = previousRow[i - 1];

    if (word[i - 1] != letter)
      replaceCost += 1;

    currentRow.emplace_back(
            std::min(insertCost, std::min(deleteCost, replaceCost)));
  }

  if (currentRow.back() <= maxCost)
  {
    std::cerr << "add data in result" << std::endl;
    results->push_back(std::make_pair(curWord, currentRow.back()));
  }

  sort_vect(currentRow);
  if (currentRow[0] <= maxCost)
  {
    const auto& children = node.get_children();
    for (const auto& child : children)
    {
      search_recursive(get_node(child.son_idx),
                      child.letter,
                      word,
                      currentRow,
                      results,
                      maxCost,
                      curWord + child.letter);
    }
  }

}

std::unique_ptr<std::vector<std::pair<std::string, int>>>
search(Node &node, const std::string& word, int maxCost)
{

  std::vector<int> currentRow(word.size());
  for (unsigned i = 0; i < word.size() + 1; i++)
    currentRow[i] = i;

  auto results = std::make_unique<std::vector<std::pair<std::string, int >>>();
  const auto& children = node.get_children();

  for (const auto& child: children)
  {
    std::string curWord = std::string(1, child.letter);
    search_recursive(get_node(child.son_idx),
                    child.letter,
                    word,
                    currentRow,
                    results.get(),
                    maxCost,
                    curWord);
  }
  return results;
}

}
