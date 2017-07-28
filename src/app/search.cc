

#include "node.hh"
#include <algorithm>


namespace trie {


  void searchRecursive(Node &node, char letter, std::string &word, std::vector<int> &previousRow,
                        std::vector<std::tuple<std::string, int>> &results,
                        int &maxCost, std::string &curWord){

    int nbColumn = word.size();
    std::vector<int> currentRow = new std::vector<int>();
    currentRow.push_back(previousRow[0] + 1);
    for (int i = 0; i < nbColumn; i++){
      int insertCost = currentRow[i - 1] + 1;
      int deleteCost = previousRow[i] + 1;
      int replaceCost = previousRow[i - 1];

      if (word[i - 1] != letter)
        replaceCost += 1

      currentRow.push_back(std::min(insertCost, deleteCost, replaceCost));
    }

    if (currentRow.back() <= maxCost)
      results.push_back(std::make_tuple(curWord, currentRow.back()));

    if (std::min(currentRow) <= maxCost){
      auto& children = node.getChildren();
      for (int j = 0; j < children.size(), j++){
        searchRecursive(get_node(children[j].son_idx), children[j].letter, word,
                                  currentRow, results, maxCost, curWord + children[j].letter)
      }
    }

  }

  std::vector<std::string>& search(Node &node, std::string word, int maxCost){
    std::vector<int> currentRow = new std::vector<int>();
    for (int i = 0; i < word.size() + 1; i++)
      currentRow[i] = i;
    std::vector<std::tuple<std::string, int>> results = new std::vector<int>();
    auto& children = node.getChildren();
    for (int j = 0; j < children.size(), j++){
      searchRecursive(get_node(children[j].son_idx), children[j].letter, word,
                                currentRow, results, maxCost,
                                std::string str(1, children[j].letter));
    }
    return results;
  }
}
