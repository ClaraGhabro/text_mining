#include "search.hh"

//#include "trie/node.hh"
#include "trie/nodes.hh"
#include <algorithm>


namespace trie {

void sort_vect(std::vector<int>& vect)
{
  std::sort(vect.begin(),
            vect.end(),
            [](const auto& elt1, const auto& elt2) {
              return elt1 < elt2;
            });
}

  void searchRecursive(Node& node,
                       char letter,
                       const std::string& word,
                       std::vector<int>& previousRow,
                       std::vector<std::pair<std::string, int>> &results,
                       int maxCost,
                       const std::string& curWord){

    int nbColumn = word.size();
    std::vector<int> currentRow{};
    currentRow.push_back(previousRow[0] + 1);
    for (int i = 0; i < nbColumn; i++){
      int insertCost = currentRow[i - 1] + 1;
      int deleteCost = previousRow[i] + 1;
      int replaceCost = previousRow[i - 1];

      if (word[i - 1] != letter)
        replaceCost += 1;

      currentRow.push_back(std::min(insertCost, std::min(deleteCost, replaceCost)));
    }

    if (currentRow.back() <= maxCost)
      results.push_back(std::make_pair(curWord, currentRow.back()));

    sort_vect(currentRow);
    if (currentRow[0] <= maxCost)
    {
      auto& children = node.getChildren();
      for (unsigned j = 0; j < children.size(); j++)
      {
        searchRecursive(get_node(children[j].son_idx), children[j].letter, word,
                                  currentRow, results, maxCost, curWord + children[j].letter);
      }
    }

  }

  std::vector<std::string>& search(Node &node, const std::string& word, int maxCost){
    std::vector<int> currentRow{};
    for (unsigned i = 0; i < word.size() + 1; i++)
      currentRow[i] = i;
    std::vector<std::pair<std::string, int>> results{};
    auto& children = node.getChildren();
    for (unsigned j = 0; j < children.size(); j++)
    {
      searchRecursive(get_node(children[j].son_idx),
                     children[j].letter,
                     word,
                     currentRow,
                     results,
                     maxCost,
                     children[j].letter);
    }
    return results;
  }
}
