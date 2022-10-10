#include <iostream>
#include <algorithm>
#include "suff_tree.hpp"

int main() {
    std::string in_str;
    std::cin >> in_str;
    SuffTree tree;
    tree.Insert(in_str);
    std::string in_substr;
    int i = 1;
    while (std::cin >> in_substr) {
        std::vector<unsigned> ans;
        tree.Find(in_substr, ans);
        std::sort(ans.begin(), ans.end());
        if(!ans.empty())
        {
            std::cout << i << ": ";
            for(int j = 0; j < ans.size(); ++j) {
                std::cout << ans[j] << ' ';
                if (j + 1 < ans.size()){
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        i++;
    }
}