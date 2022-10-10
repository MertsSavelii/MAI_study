#include <iostream>
#include <algorithm>
#include "suff_tree_linear.hpp"

int main() {
    std::string in_str;
    std::cin >> in_str;
    SuffixTree tree(in_str);
    //tree.Insert(in_str);
    std::string in_substr;
    int i = 1;
    while (std::cin >> in_substr) {
        std::vector<int> ans;
        tree.FindSubStr(in_substr, ans);
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