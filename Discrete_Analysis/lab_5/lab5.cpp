#include <iostream>
#include "suff_tree.hpp"
#include <algorithm>

int main() {
    std::string in_str;
    std::cin >> in_str;
    SuffTree tree(in_str);
    std::string in_substr;
    int i = 1;
    while (std::cin >> in_substr) {
        std::cout << i << ": ";
        std::vector<unsigned> ans = tree.SubstringSearch(in_substr);
        std::sort(ans.begin(), ans.end());
        for(int j = 0; j < ans.size(); ++j) {
            std::cout << ans[j] << ' ';
            if (j + 1 < ans.size()){
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        i++;
    }
    return 0;
}